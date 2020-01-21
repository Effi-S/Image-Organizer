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
#include "COLOR.h"
#include <iterator>


namespace fs = std::filesystem;
using ImgInfo = std::pair<cv::Ptr<const cv::Mat>, std::shared_ptr<std::string>> ;
using IMG_DataBase = std::vector<ImgInfo>;
const int MAX_ENTRIES = 20000;

class ImgScanner
{

public:
	static void scan(std::string path = "C:\\");

    auto end(){
        return ImgScanner::IMG_DB().end();
    }
     auto begin(){
        return ImgScanner::IMG_DB().begin();
    }

	friend void addImgToDB( const std::filesystem::directory_entry& entry);

private:  
    static IMG_DataBase &IMG_DB();

};

