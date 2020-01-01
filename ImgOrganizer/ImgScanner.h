#pragma once
#include<iostream>
#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include <vector>
#include <memory>
#include <unordered_set>
#include <ctime>
#include <opencv2/opencv.hpp>
#include <future>
#include <mutex>

namespace fs = std::filesystem;
using IMG_DataBase = std::vector<std::pair<cv::Ptr<const cv::Mat>, std::string>>; 

class ImgScanner
{
public:
	
	static void scan(const std::wstring& path = L"C:\\");

	static IMG_DataBase &IMG_DB();
	
	
	friend void addImgToDB( const std::filesystem::directory_entry& entry);

private:
	ImgScanner(const std::wstring & path = L"C:\\");
	

};

