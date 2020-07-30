#pragma once
#include <opencv2/opencv.hpp>
#include <vector>
/******************
* Using ORB- Oriented FAST and Rotated Brief.
* get descriptors from images.
* and find a match score of these descriptors.
********************/
class OrbMatcher
{
	const float ratio_thresh = 0.89f; ///< Lows Ratio for ORB.
	float TRIMMING_DIST = 500.f; ///< A filter distances for matches. only matches coser than this are consindered macthes.
	std::ofstream ws;
public:
    double matcheScoreFromImages( cv::Mat ,  cv::Mat , const bool draw=false); /// < get match score from images using dnn. Very slow. 
	cv::Mat createDescriptor(cv::Mat & mat);  ///< get an ORB descriptor from a cv::Mat.
	double matchScoreFromdescriptors(cv::Mat& desc1, cv::Mat& desc2); /// < get match score from image descriptors using trimming distance.

private:
	void sort(std::vector<cv::DMatch>& matches);
	std::string type2str(int type); ///< for debugging, utility for finding Mat type.
	bool convertTypes(cv::Mat&, cv::Mat&, int type); ///< convert 2 descriptors to detectable types.
	static const cv::Ptr<cv::ORB> m_orb; ///< ORB itself.
	cv::Ptr<cv::DescriptorMatcher> m_matcher = cv::BFMatcher::create(cv::DescriptorMatcher::BRUTEFORCE); ///< brute force matcher for slow.
};

