#include "SurfMatcher.h"

void SurfMatcher::execute(const cv::Ptr<cv::Feature2D>  & detector)
{

    std::cout << "running : " << typeid(detector).name() << std::endl;
    cv::Mat img1 = cv::imread("../testing/tests/rotation-0-5/18.jpg", cv::IMREAD_GRAYSCALE);
    cv::Mat img2 = cv::imread("../testing/tests/rotation-0-5/dd18.jpg", cv::IMREAD_GRAYSCALE);
    if (img1.empty() || img2.empty())
    {
        std::cout<< "Could not open or find the image!\n" << std::endl;        
        return ;
    }
    //-- Step 1: Detect the keypoints using SURF Detector, compute the descriptors
      
    std::vector<cv::KeyPoint> keypoints1, keypoints2;
    cv::Mat descriptors1, descriptors2;
    detector->detectAndCompute(img1, cv::noArray(), keypoints1, descriptors1);
    detector->detectAndCompute(img2, cv::noArray(), keypoints2, descriptors2);
    //-- Step 2: Matching descriptor vectors with a FLANN based matcher
    // Since SURF is a floating-point descriptor NORM_L2 is used
    cv::Ptr<cv::DescriptorMatcher> matcher = cv::DescriptorMatcher::create(cv::DescriptorMatcher::FLANNBASED);
    std::vector< std::vector<cv::DMatch> > knn_matches;
    matcher->knnMatch(descriptors1, descriptors2, knn_matches, 2);
    //-- Filter matches using the Lowe's ratio test
    const float ratio_thresh = 0.7f;
    std::vector<cv::DMatch> good_matches;
    for (size_t i = 0; i < knn_matches.size(); i++)
    {
        if (knn_matches[i][0].distance < ratio_thresh * knn_matches[i][1].distance)
        {
            good_matches.push_back(knn_matches[i][0]);
        }
    }
    //-- Draw matches
    cv::Mat img_matches;
    drawMatches(img1, keypoints1, img2, keypoints2, good_matches, img_matches, cv::Scalar::all(-1),
        cv::Scalar::all(-1), std::vector<char>(), cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
    //-- Show detected matches
    cv::imshow("Good Matches", img_matches);
    cv::waitKey();

}
