#pragma once
#include <map>
#include "ImgMatchFinderBase.h"
#include "OrbMatcher.h"

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
    const int SIMILARITY_DELTA = 30;  ///< the number of similar values that are considered a match
    const double ORB_DELTA = 0.6; ///< percent for orb that is considered a match
    using ImgInfo = std::pair<cv::Mat, std::wstring>;
    using HashKey = std::string;
    using HashValue = std::pair<cv::Mat, std::list<ImgInfo>>;

public:

    SimilarImgFinder() { makeListOfSimilarImages(); }
    void makeMatchGroups() override;
     ~SimilarImgFinder() override = default;

private:

    void makeListOfSimilarImages(); ///< initializing the list

    std::unordered_map<HashKey, HashValue > m_matches; ///< a map from a key to list of images

    cv::Ptr<cv::img_hash::ImgHashBase> m_algo = cv::img_hash::BlockMeanHash::create(0); ///< the algorithm to run
    
};

