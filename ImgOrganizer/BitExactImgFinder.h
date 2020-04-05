#pragma once
#include "ImgMatchFinderBase.h"
#include <unordered_map>
#include <opencv2/opencv.hpp>
#include <opencv2/img_hash/block_mean_hash.hpp>
#include "ImgFileScanner.h"
#include "COLOR.h"

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
    const int KEY_SIZE = 42;  ///< the hash digest size

	using HashKey = std::string;
	using ImgInfo = std::pair<cv::Mat, std::unique_ptr<std::string>>;
    using MatchMap = std::unordered_map<HashKey, std::vector<ImgInfo>>;

public:

    BitExactImgFinder() { makeImageMap();}
    ~BitExactImgFinder () override = default;

    void makeMatchGroups() override; 
private:
	
    void makeImageMap(); ///< initializing the map 
	
    MatchMap m_matches; ///< a map from a key to list of images

    cv::Ptr<cv::img_hash::ImgHashBase> m_algo; ///< the algorithm to run

};

