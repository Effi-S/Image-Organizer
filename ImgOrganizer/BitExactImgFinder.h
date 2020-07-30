#pragma once
#include <unordered_map>
#include "ImgMatchFinderBase.h"

/***********************
 * Exactly matching Image Finder
 *
 * Derrived from ImgMatchFinderBase
 *
 * This class iterates over the Images found by
 *
 * ImgFileScanner and creates a matches of Images that have
 *
 * The exact same digest outputted by
 *
 * openCV's block_mean_hash(0) algorithm
 *
 * ********************** */


class BitExactImgFinder : public ImgMatchFinderBase
{
    const int KEY_SIZE = 32;  ///< the hash digest size

	using HashKey = std::string;
    using ImgInfo = std::pair<cv::Mat, std::wstring>;
    using MatchMap = std::unordered_map<HashKey, std::vector<ImgInfo>>;

public:

    BitExactImgFinder() { makeImageMap();}
    void makeMatchGroups() override; 
    ~BitExactImgFinder() override = default;

private:
	
    void makeImageMap(); ///< initializing the map 
	
    MatchMap m_matches; ///< a map from a key to list of images

    cv::Ptr<cv::img_hash::ImgHashBase> m_algo = cv::img_hash::BlockMeanHash::create(0); ///< the algorithm to run

};

