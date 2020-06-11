#include "OrbMatcher.h"

const cv::Ptr<cv::ORB> OrbMatcher::m_orb = cv::ORB::create();

double OrbMatcher::matcheScore( cv::Mat img1, cv::Mat  img2, const bool draw )
{

    if(img2.type() != img1.type() ||
            img1.cols != img2.cols ||
            (img1.type() != CV_32F && img1.type() != CV_8U))  // to prevent cv::batchDistance assertion errors
        return 0;


    std::vector<cv::KeyPoint> keyPoints, keyPoints2;
    cv::Mat descriptors, descriptors2;


    m_orb->detectAndCompute(img1, cv::noArray(), keyPoints, descriptors);
    m_orb->detectAndCompute(img2, cv::noArray(), keyPoints2, descriptors2);


    cv::Ptr<cv::DescriptorMatcher> matcher = cv::BFMatcher::create(cv::DescriptorMatcher::BRUTEFORCE);
    std::vector< std::vector<cv::DMatch> > knn_matches;

    matcher->knnMatch(descriptors, descriptors2, knn_matches, 2);

    //-- Filter matches using the Lowe's ratio test
    const float ratio_thresh = 0.89f;
    std::vector<cv::DMatch> good_matches;

    for (const auto & x : knn_matches)
        if (x[0].distance < ratio_thresh * x[1].distance)
            good_matches.push_back(x[0]);

    //-- Triming matches based on trimming distance
    //	std::vector<cv::DMatch> matches;
    //	matcher->match(descriptors, descriptors2, matches);

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
        return  double(good_matches.size()) / double(knn_matches.size());
    }

    return 0;
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
