#pragma once
#include <opencv2/opencv.hpp>
#include <vector>

class OrbMatcher
{
	float TRIMMING_DIST = 500.f; ///< a filter distances for matches. only matches coser than this are consindered macthes.
public:
	int numberOfMatches( cv::Mat  ,  cv::Mat , const bool draw=false);

private:
	void sort(std::vector<cv::DMatch>& matches);
	static const cv::Ptr<cv::ORB> m_orb; 
};

