#include "Parser.h"
char* Parser::getArg(const std::string& option)
{
	char** end = _begin + _size;
	char** itr = std::find(_begin, end, option);
	if (itr != end && ++itr != end)
		return *itr;
	return 0;
}

bool Parser::argExists(const std::string& option)
{
	char** end = _begin + _size;
	return std::find(_begin, end, option) != end;
}
bool Parser::_valid_args() {
	for (int i = 1; i < _size; ++i)
	{
		auto arg = _begin[i];
		if (i==1 && std::filesystem::exists(arg))
			continue;
		else if (_args.find(arg) == _args.end()
			&& !std::filesystem::is_directory(std::filesystem::path(_begin[i])))
		{
			std::cout <<"\033[31m" /*terminal red*/ << "Unexpected Argument: "
				<<"\033[0m" /*terminal reset*/ << _begin[i] << std::endl;
			return false;
		} 
		else if (_storing_args.find(arg) != _storing_args.end()) {
			i++;
		}
	}
	return true;
}

Parser::Parser(int argc, char** argv)
	:_size(argc), _begin(argv)
{
	if (argExists("-h") || argExists("--help") || !_valid_args()) {

		std::cout << "Usage:\t./ImageOrganizer.exe <directory>" << std::endl 
				 <<"Options:\t -s [--similar]  -b [--bit-exact] -f [--face]"
			     << " --search" << "  --people-count" << std::endl;
		std::cout << "Options usage: " << std::endl
			<< "\t-s [--similar] \t       Find images that are similar." << std::endl
			<< "\t-b [--bit-exact]'\t     Find images that are almost identical. (faster than -s)" << std::endl
			<< "\t--search <image file>\t Serach for similar images to <image file>." << std::endl
			<< "\t--people-count <num> \t Serach for images with num people in them." << std::endl
			<< "\t--face\t			    Search for a particular person." << std::endl;
		std::cout << "\tOptional for face:" << std::endl;
				std::cout << "\t\t'--add-new-label'  train a new label" << std::endl
						  << "\t\t'--search-label'  search for a label" << std::endl
						  << "\t\t'--train-new-model' retrains model from scratch." << std::endl;
		exit(0);
	}
}

std::string Parser::get_path() {

	for (int i = 1; i < _size; ++i)
		if (std::filesystem::is_directory(std::filesystem::path(_begin[i])))
		{
			std::cout << "Searching path: " << _begin[i] << std::endl;
			return _begin[i];
		}
	/*if (std::filesystem::is_directory(std::filesystem::path("../testing/tests/"))) {
		return std::filesystem::absolute("../testing/tests/").string();
	}
	if (std::filesystem::is_directory("../../../testing/tests/"))
		return std::filesystem::absolute("../../../testing/tests/").string();*/
	return ".";
}
