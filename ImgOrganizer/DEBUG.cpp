#include "ImgFileScanner.h"
#include "BitExactImgFinder.h"
#include "ImgSearch.h"
#include "SimilarImgFinder.h"
#include "ImgMatchFinderBase.h"
#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define ORANGE  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */


#define BIT_EXACT 1
#define SIMILAR 1
#define SEARCH 0


int main(int argc, char** argv){	

	//scanning for images
	std::clock_t start(std::clock());
	std::cout <<ORANGE<< "Scanning... " << RESET << std::endl;

	std::string path = (argc > 1) ? argv[1] : "C:\\Users\\effi\\Desktop";
	
	ImgFileScanner::scan(path);

	path.append("output.txt");
	std::cout << path <<std::endl;

	typedef std::basic_ofstream<std::string::value_type> myFstream;
	myFstream out_file(path, std::ios_base::app);
	
	std::cout <<GREEN<< "Time reading images scan took: " << RESET << double(std::clock()) - start << std::endl;
	std::cout << GREEN << "Found: " << RESET << ImgFileScanner::size() << std::endl;


#if BIT_EXACT  
	std::cout << ORANGE << "Computing Bit exact... " <<RESET<< std::endl;

	start = std::clock_t(std::clock());

	ImgMatchFinderBase * comp = new BitExactImgFinder;

	//out_file << GREEN << "Time BitExactImgFinder took: " << RESET << double(std::clock()) - start<<std::endl;

	comp->makeMatchGroups();
	
	int g = 0;
	for (auto i : comp->getMatchGroups())
	{
		if (i.size() > 1)
		{
			g++;
			std::cout << BLUE << "group #" << g << ":" << GREEN << std::endl;
			for (auto x : i)
			{	
				out_file << x << std::endl;
				std::cout << "	" << x << std::endl;
			}
			std::cout << RESET << std::endl;
			out_file <<  std::endl;
		}
	}
				

#endif // BIT_EXACT

#if SIMILAR  

	std::cout << ORANGE << "Computing Similar finder... " << RESET << std::endl;

	start = std::clock_t(std::clock());

	ImgMatchFinderBase* comp2 = new SimilarImgFinder;

	//out_file <<GREEN<< "Time SimilarImgFinder took: "<<RESET << double(std::clock()) - start << std::endl;

	comp2->getMatchGroups();

	int g2 = 0;
	for (auto i : comp2->getMatchGroups())
	{
		if (i.size() > 1)
		{
			g2++;
			std::cout << BLUE << "group #" << g2 << ":" << GREEN << std::endl;

			for (auto x : i)
			{
				out_file << x << std::endl;
				std::cout << "	" << x << std::endl;
			}
			std::cout << RESET << std::endl;
			out_file << std::endl;
		}	
	}

#endif
#if SEARCH
	ImgSearch searcher;
	char choice = 'y';
	do{
	std::cout << ORANGE << "Enter img Path : ";
	std::string searchPath;
	
	std::cin >> searchPath;
	searcher.searchFor(searchPath);
	/*	std::cout << "  " << searchPath << std::endl;
		for (auto x : searcher.searchFor(searchPath))
			std::cout << RED << x << std::endl;*/
		std::cout << "Continue? y/n:" <<RESET;
		std::cin >> choice;
	} while (choice != 'n');
#endif

	return 0;
}




//#include <iostream>
//#include <vector>
//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/features2d.hpp>
//
//#include <filesystem>
//
//void sort_matches_increasing(std::vector< cv::DMatch > & matches)
//{
//	for (int i = 0; i < matches.size(); i++)
//	{
//		for (int j = 0; j < matches.size() - 1; j++)
//		{
//			if (matches[j].distance > matches[j + 1].distance)
//			{
//				auto temp = matches[j];
//				matches[j] = matches[j + 1];
//				matches[j + 1] = temp;
//			}
//		}
//	}
//}
//int main()
//{
//	/* Base Image -> Searching For. */
//	/* Locate Image -> Searching In. */
//	std::string search_filename = "C:\\Users\\effi\\Desktop\\testing\\proj_tests\\base_images\\1.jpg";
//	std::string search_dir = "C:\\Users\\effi\\Desktop\\testing\\proj_tests\\base_images";
//
//	// Check if file exists.
//	if (!std::filesystem::exists(search_filename))
//	{
//		std::cout << "ERROR! File not found." << std::endl << search_filename << std::endl;
//		std::cin.get();
//		exit(1);
//	}
//
//	if (!std::filesystem::exists(search_dir))
//	{
//		std::cout << "ERROR! File not found." << std::endl << search_dir << std::endl;
//		std::cin.get();
//		exit(1);
//	}
//
//	// Load Base and Locate image
//	cv::Mat base_image = cv::imread(search_filename, cv::IMREAD_GRAYSCALE);
//	cv::Mat locate_image = cv::imread(search_dir, cv::IMREAD_GRAYSCALE);
//
//	// Initiate ORB Detector Class within pointer.
//	cv::Ptr<cv::FeatureDetector> detector = cv::ORB::create();
//
//	// Finding key points.
//	std::vector< cv::KeyPoint > keypoints_base_image;
//	std::vector< cv::KeyPoint > keypoints_locate_image;
//
//	// Find keypoints.
//	detector->detect(base_image, keypoints_base_image);
//	detector->detect(locate_image, keypoints_locate_image);
//
//	detector.release();
//
//	// Find descriptors.
//
//	cv::Mat descriptors_base_image;
//	cv::Mat descriptors_locate_image;
//
//	cv::Ptr<cv::DescriptorExtractor> extractor = cv::ORB::create();
//
//	extractor->compute(base_image, keypoints_base_image, descriptors_base_image);
//	extractor->compute(locate_image, keypoints_locate_image, descriptors_locate_image);
//
//	extractor.release();
//
//	// Create Brute-Force Matcher. Other Algorithms are 'non-free'.
//	cv::BFMatcher brue_force_matcher = cv::BFMatcher(cv::NORM_HAMMING, true);
//
//	// Vector where matches will be stored.
//	std::vector< cv::DMatch > matches;
//
//	// Find matches and store in matches vector.
//	brue_force_matcher.match((const cv::OutputArray)descriptors_base_image, (const cv::OutputArray)descriptors_locate_image, matches);
//
//	// Sort them in order of their distance. The less distance, the better.
//	sort_matches_increasing(matches);
//
//	if (matches.size() > 10)
//	{
//		matches.resize(10);
//	}
//
//	// Draw the first 10 matches
//	cv::Mat output_image;
//
//	std::cout << "Keypoints Base Size:" << keypoints_base_image.size() << std::endl
//		<< "Keypoints Locate Size:" << keypoints_locate_image.size() << std::endl
//		<< "Matches Size:" << matches.size() << std::endl;
//
//	std::cout << "First " << matches.size() << " Match Distance's:" << std::endl;
//	for (int i = 0; i < matches.size(); i++)
//	{
//		std::cout << matches[i].distance << ", ";
//	}
//	std::cout << std::endl;
//
//	cv::drawMatches(
//		base_image, keypoints_base_image,
//		locate_image, keypoints_locate_image,
//		matches,
//		output_image);
//
//	cv::imshow("Matches", output_image);
//
//	cv::waitKey(0);
//
//	return 0;
//}
