#pragma once
#include <map>
#include "ImgMatchFinderBase.h"

//#include <opencv2/img_hash/color_moment_hash.hpp>
#include "ImgFileScanner.h"

/********************************
 * Similar Image Finding class
 *
 * Derrived from ImgMatchFinderBase
 *
 * This class iterates over the Images found by
 *
 * ImgFileScanner and creates a matches of Images that have
 *
 * digests outputted by openCV's block_mean_hash(1) algorithm
 *
 ******************************** */

class SimilarImgFinder : public ImgMatchFinderBase
{
    const int KEY_SIZE = 32;  ///< the hash digest size
    const int SIMILARITY_DELTA = 12;  ///< the number of similar values that are considered a match

    using ImgInfo = std::pair<cv::Mat, std::string>;
    using HashKey = std::string;
    using HashValue = std::pair<cv::Mat, std::list<ImgInfo>>;

    ~SimilarImgFinder() override = default;

public:

    SimilarImgFinder() { makeListOfSimilarImages(); }
    void makeMatchGroups() override;

private:

    void makeListOfSimilarImages();

    std::unordered_map<HashKey, HashValue > m_matches; ///< a map from a key to list of images

    cv::Ptr<cv::img_hash::ImgHashBase> m_algo = cv::img_hash::BlockMeanHash::create(0); ///< the algorithm to run
    
};

