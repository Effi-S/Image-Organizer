#include "OrbMatcher.h"

void OrbMatcher::execute()
{
	cv::Ptr<cv::ORB> orb = cv::ORB::create();
	cv::Mat img1 = cv::imread("../testing/tests/rotation-0-5/18.jpg", cv::IMREAD_GRAYSCALE);
		cv::Mat img2 = cv::imread("../testing/tests/rotation-0-5/dd18.jpg", cv::IMREAD_GRAYSCALE);
	std::vector<cv::KeyPoint> keyPoints, keyPoints2;
	cv::Mat descriptors, descriptors2;

	orb->detectAndCompute(img1, cv::noArray(), keyPoints, descriptors);
	orb->detectAndCompute(img2, cv::noArray(), keyPoints2, descriptors2);

	cv::Ptr<cv::BFMatcher> matcher = cv::BFMatcher::create(cv::DescriptorMatcher::BRUTEFORCE);

	std::vector<cv::DMatch> matches;
	matcher->match(descriptors, descriptors2, matches);

	sort(matches);
	int size;
	float dist = 500.f;
	for (size = 0; (size < matches.size() && matches[size].distance < dist); ++size);
	std::vector<cv::DMatch> matchesTrim(matches.begin(), matches.begin() + size);
	//-- Draw matches
	cv::Mat img_matches;
	cv::drawMatches(img1, keyPoints, img2, keyPoints2, matchesTrim, img_matches, cv::Scalar::all(-1),
		cv::Scalar::all(-1), std::vector<char>(), cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
	//-- Show detected matches
	cv::imshow("Good Matches", img_matches);

	cv::waitKey();

}

void OrbMatcher::sort(std::vector<cv::DMatch>& matches)
{
	for (auto i = 0; i < matches.size(); ++i)		for (auto j = 0; j < matches.size() - 1; ++j)			if (matches[j].distance > matches[j + 1].distance)			{				auto temp = matches[j];				matches[j] = matches[j + 1];				matches[j + 1] = temp;			}
}
