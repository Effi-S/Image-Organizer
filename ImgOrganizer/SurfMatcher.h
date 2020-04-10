#pragma once
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/xfeatures2d.hpp"
#include <iostream>
class SurfMatcher
{
public:
	void execute(const cv::Ptr<cv::Feature2D>&);
};

