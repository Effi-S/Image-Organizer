#include "OrbMatcher.h"

const cv::Ptr<cv::ORB> OrbMatcher::m_orb = cv::ORB::create();


double OrbMatcher::matcheScoreFromImages( cv::Mat img1, cv::Mat  img2, const bool draw )
{   
    ws.open("temp.txt", std::ofstream::app);
    auto type1 = img1.type();
    auto type2 = img2.type();

    // Prevent cv::batchDistance assertion errors
    if (type1 != type2) {
        ws << "type1 != type2" <<std::endl;
        return 0;
    } else if (img1.cols != img2.cols) {
        ws << "img1.cols = " << img1.cols << " img2.cols= " << img2.cols << std::endl;
        return 0;
    }
    else if (type1 != CV_32F && type1 != CV_8U)
        if (!convertTypes(img1, img2, type1))
                return 0; 
     // -- 

    std::vector<cv::KeyPoint> keyPoints, keyPoints2;
    cv::Mat descriptors, descriptors2;

    m_orb->detectAndCompute(img1, cv::noArray(), keyPoints, descriptors);
    m_orb->detectAndCompute(img2, cv::noArray(), keyPoints2, descriptors2);

    std::vector< std::vector<cv::DMatch> > knn_matches;

    m_matcher->knnMatch(descriptors, descriptors2, knn_matches, 2);

    //-- Filter matches using the Lowe's ratio test

    std::vector<cv::DMatch> good_matches;

    for (const auto & x : knn_matches)
        if (x[0].distance < ratio_thresh * x[1].distance)
            good_matches.push_back(x[0]);


    //-- Draw matches
    if (draw)
    {
        cv::Mat img_matches;

        cv::drawMatches(img1, keyPoints, img2, keyPoints2, good_matches, img_matches, cv::Scalar::all(-1),
                        cv::Scalar::all(-1), std::vector<char>(), cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
        cv::imshow("Good Matches", img_matches);

        cv::waitKey();
    }
    return  double(good_matches.size()) / double(knn_matches.size());
}

cv::Mat OrbMatcher::createDescriptor(cv::Mat& mat)
{
    std::vector<cv::KeyPoint> keyPoints;
    cv::Mat descriptors;
    m_orb->detectAndCompute(mat, cv::noArray(), keyPoints, descriptors);
    
    return descriptors;
}

double OrbMatcher::matchScoreFromdescriptors(cv::Mat& desc1, cv::Mat& desc2)
{
    if(!ws.is_open())
        ws.open("temp.txt", std::ofstream::app);

    auto type1 = desc1.type();
    auto type2 = desc2.type();
    // Prevent cv::batchDistance assertion errors
    if (type1 != type2 ||  desc1.cols != desc2.cols) {
        return 0;
    }
    else if (type1 != CV_32F && type1 != CV_8U)
        if (!convertTypes(desc1, desc2, type1))
            return 0;
    // 

    //-- Triming matches based on trimming distance
       
    std::vector< std::vector<cv::DMatch> > knn_matches;

    m_matcher->knnMatch(desc1, desc2, knn_matches, 2);

    //-- Filter matches using the Lowe's ratio test

    std::vector<cv::DMatch> good_matches;

    for (const auto& x : knn_matches)
        if (x[0].distance < ratio_thresh * x[1].distance)
            good_matches.push_back(x[0]);

    ws << "SIZE:" << double(good_matches.size()) / double(knn_matches.size());
    return  double(good_matches.size()) / double(knn_matches.size());
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

std::string OrbMatcher::type2str(int type)
{
    std::string str;

    uchar depth = type & CV_MAT_DEPTH_MASK;
    uchar chans = 1 + (type >> CV_CN_SHIFT);

    switch (depth) {
    case CV_8U:  str = "8U"; break;
    case CV_8S:  str = "8S"; break;
    case CV_16U: str = "16U"; break;
    case CV_16S: str = "16S"; break;
    case CV_32S: str = "32S"; break;
    case CV_32F: str = "32F"; break;
    case CV_64F: str = "64F"; break;
    default:     str = "User"; break;
    }

    str += "C";
    str += (chans + '0');

    return str;
}

bool OrbMatcher::convertTypes(cv::Mat& m1, cv::Mat& m2, int type)
{
    uchar depth = type & CV_MAT_DEPTH_MASK;
    if (type ==  CV_8UC2 || type == CV_8UC3 || type == CV_8UC4) {
        cv::Mat tmp; 
        m1.convertTo(tmp, CV_32F); 
        m1 = tmp; 
        m2.convertTo(tmp, CV_32F); 
        m2 = tmp;
        /*ws << "converted: " << type << " to " << m1.type() << " " << m2.type() << std::endl;*/
        return true;
    
    } else 
         ws << "TYPE: " << type << " CV_8UC3= " << CV_8UC3 << std::endl;

    return false;
}
