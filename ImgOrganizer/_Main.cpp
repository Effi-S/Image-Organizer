
#include <string>
#include "Parser.h"
#include "ImgFileScanner.h"
#include "BitExactImgFinder.h"
#include "ImgSearch.h"
#include "SimilarImgFinder.h"
#include "ImgMatchFinderBase.h"
#include "OrbMatcher.h"
#include "SurfMatcher.h"
#include "FaceDetection/FaceDetector.h"
#include "FaceDetection/FacesCropped.h"

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


class Parser;
std::wstring run_algo(ImgMatchFinderBase* comp);

int main(int argc, char** argv) {
	Parser args(argc, argv);
	
	std::string path =  args.get_path();
	if (!std::filesystem::is_directory(path)) {

		std::cerr << RED << "Path " << path << " Doesn't exist or isn't a Directory" << std::endl;
		return -1;
	}
	
	//scanning for images	
	std::clock_t start(std::clock());

	std::cout << ORANGE << "Scanning " << path << "... " << RESET << std::endl;
	ImgFileScanner::scan(path);
	std::cout << GREEN << "Time reading images scan took: " << RESET << double(std::clock()) - start << std::endl;
	std::cout << GREEN << "Found: " << RESET << ImgFileScanner::size() << std::endl;

	auto  out_file = std::wofstream(path + "_exact_output.txt", std::wofstream::app);
	
	if (args.argExists("-b") || args.argExists("--bit-exact") || argc == 1) {
		
		std::cout << "Output file: " << path + "exact_output.txt" << std::endl;

		std::cout << ORANGE << "Computing Bit exact... " << RESET << std::endl;

		start = std::clock_t(std::clock());

		out_file << run_algo(new BitExactImgFinder);

	} 
	if (args.argExists("-s") || args.argExists("--similar") || argc == 1) {

		out_file = std::wofstream(path + "_similar_output.txt", std::wofstream::app);

		std::cout << "Output file: " << path + "similar_output.txt" << std::endl;

		std::cout << ORANGE << "Computing Similar finder... " << RESET << std::endl;

		start = std::clock_t(std::clock());

		out_file << run_algo(new SimilarImgFinder).c_str() << std::endl;

	}
	if (args.argExists("-f") || args.argExists("--face")) {
		
		std::unique_ptr<FaceDetector> face_detector=nullptr; // = FaceDetector::loadFromYAML();
		
		if (args.argExists("--train-new-model"))
		{
			std::cout << BOLDMAGENTA <<" >>> Creating New Face detector <<<" <<RESET << std::endl;
			face_detector = std::make_unique<FaceDetector>(FaceDetector::creatNew());
			face_detector->save();
		}
			
		if (args.argExists("--search-label")) {
			if(face_detector == nullptr)
				face_detector = std::make_unique<FaceDetector>(FaceDetector::loadFromYAML());

			auto label = 1; //args.getArg("--search-label");
			
			std::wstringstream cls;
			cls << label;
			std::wstring wLabel = cls.str();

			face_detector->searchFor(wLabel/*, true*/);
		}
		if (args.argExists("--add-new-label"))
		{
			if (face_detector == nullptr)
				face_detector = std::make_unique<FaceDetector>(FaceDetector::loadFromYAML());

			std::cout << "\nExisting labels: " << std::endl;
			for(auto x: face_detector->getUserLabels())
				std::wcout << x << std::endl;

			FacesCropped cropper;
			auto faces = cropper.readfromWebCam();
			std::cout << "Pleaese input new label: " << std::endl;
			std::wstring newLabel;
			std::wcin >> newLabel;

			face_detector->addTrainingSet(faces, newLabel);

			std::cout << "New labels: " << std::endl;
			for (auto x : face_detector->getUserLabels())
				std::wcout << x << std::endl;
		}
	} 
	if (args.argExists("--search")) {
		ImgSearch searcher;

			std::string searchPath = args.getArg("--search");

			auto img_path = std::filesystem::path(searchPath);
			
			if (!std::wifstream(img_path.c_str()).good())
				std::wcout << RED << L"Path " << img_path << L"Doesn't exist" << std::endl;
			else {
				searcher.searchFor(img_path.wstring());
				std::string temp = "a";
				std::vector<std::string> windows;

				for (auto group : searcher.getMatchGroups())
					for (auto img_name : group)
					{
						std::wcout << "Found: " << img_name << std::endl;
						cv::Mat img = MyUtils::unicodeImgRead(img_name);
						cv::namedWindow(temp, cv::WINDOW_GUI_EXPANDED);
						cv::imshow(temp, img);
						temp += "a";
					}
				cv::waitKey(0);
				for (auto window : windows)
					cv::destroyWindow(window);
			}
	}
	if (args.argExists("--people-count")) {
		int num = std::stoi(args.getArg("--people-count"));
		std::cout << ORANGE <<"Searching for Images with: " << GREEN << num << ORANGE << " People" << RESET << std::endl;
		FacesCropped cropper;

		for (auto& img_path_pair : ImgFileScanner())
			if (cropper.numberOfFaces(*img_path_pair.first) == num)
			{
				std::wstring img_name(*img_path_pair.second);
				cv::Mat img = MyUtils::unicodeImgRead(img_name);
				cv::namedWindow("find num", cv::WINDOW_GUI_EXPANDED);
				cv::imshow("find num", img);
				cv::waitKey(0);
			}
	}

	return(0);
}
std::wstring run_algo(ImgMatchFinderBase* comp)
{
	std::wstring output;
	comp->makeMatchGroups();

	int g = 0;
	for (auto i : comp->getMatchGroups())
	{
		if (i.size() > 1)
		{
			g++;
			std::cout << BLUE << "group #" << g << ":" << GREEN << std::endl << RESET;
			for (auto x : i)
			{
				output += L" " + x + L"\n";
				std::wcout << L"	" << x << std::endl;
			}
			output += L"\n\n";
		}
	}
	return output;
}

