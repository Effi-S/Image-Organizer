#pragma once
#include <unordered_map>
#include <opencv2/opencv.hpp>
//#include <opencv2/img_hash/average_hash.hpp>
//#include <opencv2/img_hash/phash.hpp>
#include <opencv2/img_hash/block_mean_hash.hpp>
#include "ImgScanner.h"
#include "COLOR.h"

class BitExactImgFinder
{
	const int BITS = 16;
	using HashKey = std::string;
	using ImgInfo = std::pair<cv::Mat, std::shared_ptr<std::string>>;
    using MatchMap = std::unordered_map<HashKey, std::vector<ImgInfo>>;

public:
    BitExactImgFinder() { makeSet();}
    std::vector<std::vector<std::string>> getGroups(){return m_stringGroups;}
    void show();
private:
	
	void makeSet();
	
	MatchMap m_matches;

	cv::Ptr<cv::img_hash::ImgHashBase> m_algo;

    std::vector<std::vector<std::string>> m_stringGroups;

};

