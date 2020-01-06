﻿#include "ImgScanner.h"


void addImgToDB( const std::filesystem::directory_entry& entry)
{	
	
ImgScanner::IMG_DB().push_back(std::make_pair(cv::Ptr<cv::Mat>(
		std::make_shared<cv::Mat>(cv::imread(entry.path().string()))),
		std::make_shared<std::string>(entry.path().string())));

	
}


void ImgScanner::scan(const std::wstring& path)
{
	typedef std::basic_ofstream<std::string::value_type> myFstream;
    myFstream file("C:/Users/effi/Desktop/temp/t.txt", std::ios_base::app);

	std::clock_t start(std::clock());
    file << "\n\n\n\n"<<GREEN << "Starting Run time:"<<RESET<<double(start)<<std::endl;

	uint img_count = 0;
	uint faild_count = 0;

    IMG_DB().empty();

	std::unordered_set<std::string> extension_set({ ".png", ".jpg", ".jpeg", "bmp" });

	for (const auto& entry : fs::recursive_directory_iterator(path, fs::directory_options::skip_permission_denied))
	{
		std::string extension = entry.path().extension().string();
		if (extension_set.find(extension) != extension_set.end())
		{
			try {
                std::async(&addImgToDB, entry);
				//addImgToDB(entry);

				file <<BOLDYELLOW<<"#"<<img_count<<": "<< entry.path().string() <<RESET<< std::endl;
				img_count++;
			}
			catch (cv::Exception & e)
			{
				file << RED <<"cv error:"<< e.what() << RESET << std::endl;
				faild_count++;
				break;
			}
			catch (...) {
				file << RED << "unknown error"<< RESET << std::endl;
				faild_count++;
			}
		}
		
	}

	file <<GREEN<< "\nNumber Of images Found:" << img_count << std::endl
		<< "Time it took: " << (double)std::clock() - start <<std::endl << "Number of fails:" << faild_count;
}


IMG_DataBase& ImgScanner::IMG_DB()
{
    static std::mutex imgMutex;
    std::lock_guard<std::mutex> lk(imgMutex);

	static IMG_DataBase _DB;
    return _DB;
}




