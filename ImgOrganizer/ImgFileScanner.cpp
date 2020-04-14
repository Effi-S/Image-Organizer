#include "ImgFileScanner.h"


void addImgToDB( const std::filesystem::directory_entry& entry)
{	
  

	static std::mutex mutex;
	std::lock_guard<std::mutex> lk(mutex);
	cv::Mat img = MyUtils::unicodeImgRead(entry.path().wstring());
	std::wstring path = entry.path().wstring();
	std::replace(path.begin() , path.end(), '\\', '/');  // necessary for windows paths to work properly

	if(!img.empty())
		ImgFileScanner::IMG_DB().push_back(std::make_pair(*new cv::Ptr<cv::Mat>(
	std::make_shared<cv::Mat>(img)),
	std::make_unique<std::wstring>(path)));
}

void ImgFileScanner::scan(std::string path)
{
	int tmp = _scan(path);
}

int ImgFileScanner::getNumberOfImages(std::string path)
{
	return _scan(path, true);
}

// The main scanning algorithm
// Recursively iterates over the path given into path
//
int ImgFileScanner::_scan(std::string path, bool dry)
{
    // typedef std::basic_ofstream<std::string::value_type> myFstream;
    // myFstream file("C:/Users/effi/Desktop/temp/t.txt", std::ios_base::app); // for logging time

	std::clock_t start(std::clock());


	uint img_count = 0;
	uint failed_count = 0;

    IMG_DB().clear();


    std::unordered_set<std::string> extension_set({ ".png", ".jpg", ".jpeg", ".bmp" });

	for (const auto& entry : fs::recursive_directory_iterator(path, fs::directory_options::skip_permission_denied))
	{
		std::string extension = entry.path().extension().string();
		if (extension_set.find(extension) != extension_set.end())
		{
			try
			{
				if(!dry)
					std::async(&addImgToDB, entry);
                img_count++;
			}
			catch (cv::Exception & e)
			{
				std::cout << RED << "cv error:" << e.what() << RESET << std::endl;
				failed_count++;
				break;
			}
			catch (std::exception& e) {
				// mostly unicode errors 
				std::cout << RED << "imread error for file " << entry.path().c_str() << "\n " << RESET << std::endl;
				std::cout << ORANGE << "imread error:" << e.what() << " " << RESET << std::endl;
				failed_count++;
			}
			catch (...)
			{
				//just in case libpng/cv send strange errors
				std::cout << RED << "unknown error" << RESET << std::endl;
				failed_count++;
			}
		}
	}
    std::cout <<GREEN<< "\nNumber Of images Found:" << img_count << std::endl << "Time it took: " << double(std::clock()) - start  <<"Number of fails:" <<RED<< failed_count<<std::endl <<RESET<<std::endl;
    return img_count ;
}

IMG_DataBase& ImgFileScanner::IMG_DB()
{
    static std::mutex imgMutex;
    std::lock_guard<std::mutex> lk(imgMutex);

	static IMG_DataBase _DB;
    return _DB;
}





