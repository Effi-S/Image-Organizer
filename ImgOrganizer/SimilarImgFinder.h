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
 * digests outputted by openCV's block_mean_hash(0) algorithm
 *
 * If the block_mean_hash(0) is suspiciously similar an ORB matcher determines 
 * whether there is a similarity or not .
 *
 ******************************** */

class SimilarImgFinder : public ImgMatchFinderBase
{
    const int KEY_SIZE = 42;  ///< the hash digest size
    const double SIMILARITY_DELTA = 16;  ///< block_mean_hash(0) threshhold for clear match.
    const double SECONDARY_SIMILARITY_DELTA = 30; ///< block_mean_hash(0) threshhold of suspition.
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

    std::unordered_map<HashKey, HashValue > m_matches; ///< a map from a key to list of images.
    std::unordered_map<HashKey, cv::Mat> m_orb_descriptors; ///< hold ORB descriptors of images.

    cv::Ptr<cv::img_hash::ImgHashBase> m_algo= cv::img_hash::BlockMeanHash::create(0); ///< the algorithm to run
    OrbMatcher m_orb = OrbMatcher(); /// <orb object.
    
};

