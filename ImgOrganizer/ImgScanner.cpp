#include "ImgScanner.h"

std::mutex imgMutex;

void addImgToDB( const std::filesystem::directory_entry& entry)
{
	std::lock_guard<std::mutex> lk(imgMutex);
	ImgScanner::IMG_DB().push_back(std::make_pair(cv::Ptr<cv::Mat>(
		std::make_shared<cv::Mat>(cv::imread(entry.path().string()))),entry.path().string()));
}


void ImgScanner::scan(const std::wstring& path)
{
	/*typedef std::basic_ofstream<std::string::value_type> myFstream;
    myFstream file("C:/Users/effi/Desktop/temp/t.txt", std::ios_base::app);

	std::clock_t start(std::clock());
    file << "\n\n\n\nStarting Run:\n";*/

	uint img_count = 0;
	uint faild_count = 0;

	std::unordered_set<std::string> extension_set({ ".png", ".jpg", ".jpeg", "bmp" });

	for (const auto& entry : fs::recursive_directory_iterator(path, fs::directory_options::skip_permission_denied))
	{
		std::string extension = entry.path().extension().string();
		if (extension_set.find(extension) != extension_set.end())
		{
			try {
				std::future<void>(std::async(&addImgToDB,  entry));

				/*file << entry.path().string() << std::endl;*/
				img_count++;
			}
			catch (...) {
				faild_count++;
			}
		}
	}

	/*file << "\nNumber Of images Found:" << img_count << std::endl
		<< "Time it took: " << (double)std::clock() - start<<std::endl << "Number of fails: 
		<<failed_count;*/
}

IMG_DataBase& ImgScanner::IMG_DB()
{
	static IMG_DataBase _DB;
	return _DB;
}





