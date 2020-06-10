
#include <string>
#include "ImgFileScanner.h"
#include "BitExactImgFinder.h"
#include "ImgSearch.h"
#include "SimilarImgFinder.h"
#include "ImgMatchFinderBase.h"
#include "OrbMatcher.h"
#include "SurfMatcher.h"

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
				output += L" " +  x + L"\n";
				std::wcout << L"	" << x << std::endl;
			}
			output += L"\n\n";
		}
	}
	return output;
}
char* getArg(char** begin, int size, const std::string& option)
{
	char** end = begin + size;
	char** itr = std::find(begin, end, option);
	if (itr != end && ++itr != end)
		return *itr;

	return 0;
}

bool argExists(char** begin, int size, const std::string& option)
{
	char** end = begin + size;
	return std::find(begin, end, option) != end;
}
bool valid_args(char** begin,  int size) {

	std::set<std::string> args = { "-s" , "--similar" ,"-b", "--bit-exact", "-f", "--face", "-s", "--search" };
	
	for (int i = 1; i < size; ++i)
		if(args.find(begin[i]) == args.end() 
			&& !std::filesystem::is_directory(std::filesystem::path(begin[i])))
		{
				std::cout << RED << "Unexpected Argument: " << RESET << begin[i] << std::endl;
				return false;
		}
	
	return true;
}
std::string get_path(char** begin, int size) {

	for (int i = 1; i < size; ++i)
		if (std::filesystem::is_directory(std::filesystem::path(begin[i])))
			return begin[i];

	return "../testing/tests/";
}

int main(int argc, char** argv) {
	
	if (argExists(argv, argc, "-h") || argExists(argv, argc, "--help") || !valid_args(argv, argc)) {
		std::cout << "usage: <filname> options: -s [--similar]  -b [--bit-exact] -f [--face] " << std::endl;
		return (0);
	} 
	
	std::string path = get_path(argv, argc);  
	
	//scanning for images
	std::clock_t start(std::clock());
	std::cout << ORANGE << "Scanning... " << RESET << std::endl;
	ImgFileScanner::scan(path);
	std::cout << GREEN << "Time reading images scan took: " << RESET << double(std::clock()) - start << std::endl;
	std::cout << GREEN << "Found: " << RESET << ImgFileScanner::size() << std::endl;

	auto  out_file = std::wofstream(path + "_exact_output.txt", std::wofstream::app);
	
	if (argExists(argv, argc, "-b") || argExists(argv, argc, "--bit-exact") || argc == 1) {
		
		std::cout << "Output file: " << path + "exact_output.txt" << std::endl;

		std::cout << ORANGE << "Computing Bit exact... " << RESET << std::endl;

		start = std::clock_t(std::clock());

		out_file << run_algo(new BitExactImgFinder);

	} 
	if (argExists(argv, argc, "-s") || argExists(argv, argc, "--similar") || argc == 1) {

		out_file = std::wofstream(path + "_similar_output.txt", std::wofstream::app);

		std::cout << "Output file: " << path + "similar_output.txt" << std::endl;

		std::cout << ORANGE << "Computing Similar finder... " << RESET << std::endl;

		start = std::clock_t(std::clock());

		out_file << run_algo(new SimilarImgFinder).c_str() << std::endl;

	}
	if (argExists(argv, argc, "-f") || argExists(argv, argc, "-face")) {

	} 
	if (argExists(argv, argc, "--search") || argExists(argv,argc, "-s")) {
		ImgSearch searcher;
		char choice = 'y';
		do {
			std::cout << ORANGE << "Enter img Path : ";
			std::string searchPath;

			std::cin >> searchPath;
			searcher.searchFor(searchPath);
			/*	std::cout << "  " << searchPath << std::endl;
				for (auto x : searcher.searchFor(searchPath))
					std::cout << RED << x << std::endl;*/
			std::cout << "Continue? y/n:" << RESET;
			std::cin >> choice;
		} while (choice != 'n');
	}

	return(0);
}
