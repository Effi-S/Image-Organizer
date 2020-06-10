#include "ImgFileScanner.h"

//< !!!!!!!!!!!!!!!! TODO: Remove try catch blocks !!!!!!!!!!!!!!!!!

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
	std::clock_t start(std::clock());

	uint img_count = 0;

	uint failed_count = 0;

    IMG_DB().clear();

std::unordered_set<std::wstring> extension_set({ L".png", L".jpg", L".jpeg", L".bmp" });

std::future<void> future;


	for (const auto& entry : fs::recursive_directory_iterator(path, fs::directory_options::skip_permission_denied))
    {
    try {
        std::wstring extension = entry.path().extension().wstring();

		if (extension_set.find(extension) != extension_set.end())
		{
			try
			{
				if(!dry)
                    future = std::future(std::async(&addImgToDB, entry));

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

      } catch (std::exception & e) {
        std::cout <<RED "\n >>>>>>> ERROR <<<<<<\n " << e.what()
        << "\n >>>>>>>>>><<<<<<<<<<<" << RESET << std::endl;
        }
	}

    if(future.valid())
			future.wait();

    std::cout << GREEN << "\nNumber Of images Found: " << BLUE << img_count << std::endl
             <<"Time it took: " << RESET << double(std::clock()) - start << GREEN
             <<" Number of fails:" << RED << failed_count<< std::endl <<RESET <<std::endl;

	return img_count ;
}

IMG_DataBase& ImgFileScanner::IMG_DB()
{
    static std::mutex imgMutex;
    std::lock_guard<std::mutex> lk(imgMutex);

	static IMG_DataBase _DB;
    return _DB;
}





