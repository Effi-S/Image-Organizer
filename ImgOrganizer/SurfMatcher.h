#pragma once
#include <iostream>
#ifndef MAKELINUX
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/xfeatures2d.hpp"
#else
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/features2d.hpp>
// #include <opencv2/xfeatures2d.hpp>
#endif
class SurfMatcher
{
public:
	void execute(const cv::Ptr<cv::Feature2D>&);
};

