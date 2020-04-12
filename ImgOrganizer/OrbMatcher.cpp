#include "OrbMatcher.h"

const cv::Ptr<cv::ORB> OrbMatcher::m_orb = cv::ORB::create();

int OrbMatcher::numberOfMatches( cv::Mat img1 , cv::Mat  img2 ,const bool draw )
{
	std::vector<cv::KeyPoint> keyPoints, keyPoints2;
	cv::Mat descriptors, descriptors2;
	if(img1.rows > 500 || img1.rows < 50)
	img1.resize(500);
	if (img2.rows > 500 || img2.rows < 50)
	img2.resize(500);
	try{
		m_orb->detectAndCompute(img1, cv::noArray(), keyPoints, descriptors);
		m_orb->detectAndCompute(img2, cv::noArray(), keyPoints2, descriptors2);
	}
	catch (cv::Exception& e)
	{
		std::cout << "descriptor error:" << e.what() << std::endl;
		cv::Mat img_matches;
		std::vector<cv::DMatch> good_matches;
		cv::drawMatches(img1, keyPoints, img2, keyPoints2, good_matches, img_matches, cv::Scalar::all(-1),
			cv::Scalar::all(-1), std::vector<char>(), cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
		cv::imshow("Good Matches", img_matches);

		cv::waitKey();

	}
	

	cv::Ptr<cv::DescriptorMatcher> matcher = cv::BFMatcher::create(cv::DescriptorMatcher::BRUTEFORCE);
	std::vector< std::vector<cv::DMatch> > knn_matches;
	
	matcher->knnMatch(descriptors, descriptors2, knn_matches, 2);

	//-- Filter matches using the Lowe's ratio test
	const float ratio_thresh = 0.5f;
	std::vector<cv::DMatch> good_matches;

	for (const auto & x : knn_matches)
		if (x[0].distance < ratio_thresh * x[1].distance)	
			good_matches.push_back(x[0]);
		
	std::vector<cv::DMatch> matches;
	matcher->match(descriptors, descriptors2, matches);
	
	//-- Triming matches based on trimming distance
	/*int size = 0;
	for (auto& x : matches)
		if (x.distance < TRIMMING_DIST)
			size++;*/

	/*for (int i = 0; (i < matches.size() && matches[i].distance < TRIMMING_DIST); ++i);
	std::vector<cv::DMatch> matchesTrim(matches.begin(), matches.begin() + i);*/
	
	
	//-- Draw matches
	if (draw)
	{
		cv::Mat img_matches;

		cv::drawMatches(img1, keyPoints, img2, keyPoints2, good_matches, img_matches, cv::Scalar::all(-1),
			cv::Scalar::all(-1), std::vector<char>(), cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
		cv::imshow("Good Matches", img_matches);

		cv::waitKey();
	}
	

	return good_matches.size();
}

// sorting matches based on size 
void OrbMatcher::sort(std::vector<cv::DMatch>& matches)
{
	for (auto i = 0; i < matches.size(); ++i)
		for (auto j = 0; j < matches.size() - 1; ++j)
			if (matches[j].distance > matches[j + 1].distance)
			{
				auto temp = matches[j];
				matches[j] = matches[j + 1];
				matches[j + 1] = temp;
			}
}
