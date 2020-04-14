#pragma once
#include "ImgFileScanner.h"
#include "ImgMatchFinderBase.h"
#include <string>
#include <opencv2/img_hash/block_mean_hash.hpp>
class ImgSearch : public ImgMatchFinderBase
{
	const int BITS = 42;
	
public:
	void searchFor(const std::string& querry)
	{
		std::vector<std::wstring> matches;
		cv::Mat qHash;
		cv::Mat img = cv::imread(querry);
		m_algo->compute(img, qHash);

		for (auto& x : ImgFileScanner())
		{
			cv::Mat xHash;
			cv::Mat img = MyUtils::unicodeImgRead(*(x.second));
			m_algo->compute(img, xHash);

			auto sim = m_algo->compare(qHash, xHash);
			if (sim <= 12)
				matches.push_back(*(x.second));
		}

		std::string temp = "a";
		std::vector<std::string> windows;
		for (auto x : matches)
		{
			cv::namedWindow(temp, cv::WINDOW_GUI_EXPANDED);
			cv::imshow(temp, MyUtils::unicodeImgRead(x));
			temp += "a";
		}
		cv::waitKey(0);
		for (auto window : windows)
			cv::destroyWindow(window);
		ImgMatchFinderBase::addMatchGroup(matches);
	}
    void makeMatchGroups() override {};
private:
	cv::Ptr<cv::img_hash::ImgHashBase> m_algo = cv::img_hash::BlockMeanHash::create(0);
	

};

