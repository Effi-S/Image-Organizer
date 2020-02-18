#pragma once
#include "ImgScanner.h"
#include <string>
#include <opencv2/img_hash/block_mean_hash.hpp>
class ImgSearch
{
	const int BITS = 42;
	
	using MatchVector = std::vector< std::string, std::vector<std::string>>;
public:
	void searchFor(const std::string& querry)
	{
		cv::Mat qHash;
		cv::Mat img = cv::imread(querry);
		m_algo->compute(img, qHash);

		for (auto& x : ImgScanner())
		{
			cv::Mat xHash;
			cv::Mat img = cv::imread(*(x.second));
			m_algo->compute(img, xHash);

			auto sim = m_algo->compare(qHash, xHash);
			if (sim <= 12)
				m_matches.push_back(*(x.second));
		}

		std::string temp = "a";
		std::vector<std::string> windows;
		for (auto x : m_matches)
		{
			cv::namedWindow(temp, cv::WINDOW_GUI_EXPANDED);
			cv::imshow(temp, cv::imread(x));
			temp += "a";
		}
		cv::waitKey(0);
		for (auto window : windows)
			cv::destroyWindow(window);
	}

private:
	cv::Ptr<cv::img_hash::ImgHashBase> m_algo = cv::img_hash::BlockMeanHash::create(0);
	std::vector<std::string> m_matches;

};

