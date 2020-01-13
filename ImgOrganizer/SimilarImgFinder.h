#pragma once
#include <map>
#include <opencv2/opencv.hpp>
#include<opencv2/img_hash/block_mean_hash.hpp>
#include <opencv2/img_hash/phash.hpp>
#include <opencv2/img_hash/color_moment_hash.hpp>
#include "ImgScanner.h"

class SimilarImgFinder
{
	const int BITS = 42;

    using ImgInfo = std::pair<cv::Mat, std::string>;
	using HashKey = std::string;
    using HashValue = std::pair<cv::Mat, std::list<ImgInfo>>;

public:
	SimilarImgFinder() { makeSet(); }
	void show();
private:

	void makeSet();

	std::map<HashKey, HashValue > m_matches;

	cv::Ptr<cv::img_hash::ImgHashBase> m_algo = cv::img_hash::BlockMeanHash::create(0);
};

