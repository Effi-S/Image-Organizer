#pragma once

#include <opencv2/opencv.hpp>
#include <fstream>
#include <filesystem>

namespace MyUtils
{
	static cv::Mat unicodeImgRead(const std::wstring& name, cv::ImreadModes mode = cv::ImreadModes::IMREAD_COLOR)
	{

		// Open Unicode file with  binary stream into file descriptor
		std::ifstream fd(name, std::iostream::binary);

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
			auto tmp = "tmp.jpg";
			cv::imwrite(tmp, img);
			img = cv::imread(tmp, mode);
		}

		return std::move(img);

	}
	static std::string getPath(const std::string& target)
	{
		for (const auto & x : std::filesystem::recursive_directory_iterator("../", 
			std::filesystem::directory_options::skip_permission_denied))
		{
			if (x.path().filename() == std::filesystem::path(target).filename())
				return std::filesystem::absolute(x.path()).string();
		}
		std::cerr << "Couldn't find path to: " << target << std::endl;
		return target;
	}
};

