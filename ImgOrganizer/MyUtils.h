#pragma once
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <fstream>
#include <filesystem>

#ifndef MAKELINUX
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#else
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#endif

const int MAX_IMG_SIZE = 1000;
namespace MyUtils
{
        static cv::Mat unicodeImgRead(const std::wstring &name, cv::ImreadModes mode = cv::ImreadModes::IMREAD_COLOR)
	{
        // Open Unicode file with binary stream into file descriptor
#ifdef MAKELINUX
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    auto name2 = converter.to_bytes(name);
	std::ifstream fd(name2, std::iostream::binary);
#else
		std::ifstream fd(name, std::iostream::binary);
#endif

		// Getting img size from buffer 
		std::filebuf* pbuf = fd.rdbuf();
		size_t size = pbuf->pubseekoff(0, fd.end, fd.in);
		pbuf->pubseekpos(0, fd.in);

		// Putting image fileinto a vector unsigned char vector
		std::vector<uchar> buffer(size);
		pbuf->sgetn((char*)buffer.data(), size);

		// Decode the vector into the cv Matrix
		cv::Mat img = cv::imdecode(buffer, mode);

		// opencv removes noise when converting to different types
		if (!img.empty())
		{
			static std::mutex mutex;
			std::lock_guard<std::mutex> lk(mutex);

			std::string tmp = "tmp.jpg";

			cv::imwrite(tmp, img);
			img = cv::imread(tmp, mode);
			

		}
		// make smaller if img too big
		bool row_big = img.rows > MAX_IMG_SIZE;
		bool col_big = img.cols > MAX_IMG_SIZE;
		if (row_big || col_big)
		{
			int row = (row_big) ? MAX_IMG_SIZE : img.rows;
			int col = (col_big) ? MAX_IMG_SIZE : img.cols;
			cv::Mat dst(MAX_IMG_SIZE, MAX_IMG_SIZE, CV_8U);
			cv::resize(img, dst, cv::Size(MAX_IMG_SIZE, MAX_IMG_SIZE));
			return std::move(dst);
		}
		
		return std::move(img);
	}
	static std::string getPath(const std::string& target)
	{
            for(auto root: std::vector<std::string>{".", "../", "../../"})
                for (const auto & x : std::filesystem::recursive_directory_iterator(root,
                        std::filesystem::directory_options::skip_permission_denied))
                {
                        if (x.path().filename() == std::filesystem::path(target).filename())
                                return std::filesystem::absolute(x.path()).string();
                }

		std::cerr << "Couldn't find path to: " << target << std::endl;
		return target;
	}
	//static cv::Mat DFT(cv::Mat & original)
 //   {
	//	// convert to floats 
	//	cv::Mat originalFloat;
	//	original.convertTo(originalFloat, CV_32FC1, 1.0 / 255.0);
 //       
	//	cv::Mat originalComplax[2] = { originalFloat, cv::Mat::zeros(originalFloat.size(), CV_32FC1 )};//for holding complex and real values seperately.
	//	
	//	cv::Mat dftReady;
	//	cv::merge(originalComplax, 2, dftReady);

	//	cv::Mat dftOfOriginal;
	//	
	//	cv::dft(dftReady, dftOfOriginal, cv::DFT_COMPLEX_OUTPUT);
 //   
	//	return dftOfOriginal;
	//}
 //   static cv::Mat IDFT(cv::Mat& orig) {
 //       //calculating the idft
 //       cv::Mat inverseTransform;
 //       cv::dft(orig, inverseTransform, cv::DFT_INVERSE | cv::DFT_REAL_OUTPUT | cv::DFT_SCALE);

 //       return inverseTransform;
 //   }
};

