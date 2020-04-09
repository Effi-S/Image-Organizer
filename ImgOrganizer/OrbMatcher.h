#pragma once
#include <opencv2/opencv.hpp>
#include <vector>

class OrbMatcher
{
public:
	void execute();

private:
	void sort(std::vector<cv::DMatch>& matches);
};

