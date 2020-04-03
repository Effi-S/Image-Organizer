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

/************ Img File Scanner **********
 * Recursive image file finder
 *
 * this Class is scans the filesystem for images
 *
 * and saves them in a database for later iteration.
 *
 * ************************************** */

namespace fs = std::filesystem;
using ImgInfo = std::pair<cv::Ptr<const cv::Mat>, std::unique_ptr<std::string>> ;
using IMG_DataBase = std::vector<ImgInfo>;

class ImgFileScanner
{
public:
    static void scan(std::string path = "C:\\");  ///< The main scanning function - saves the images in database for later use
    static int getNumberOfImages(std::string path = "C:\\");  ///< Returns the number of images in the path (a dry run).

    // functions for iterating on the images in the database
    auto end(){        return ImgFileScanner::IMG_DB().end();}
    auto begin(){	   return ImgFileScanner::IMG_DB().begin();}
    static auto size() {	   return ImgFileScanner::IMG_DB().size(); }


private:  
    friend void addImgToDB(const std::filesystem::directory_entry& entry);  ///< adding to database
    static int _scan(std::string path = "C:\\", bool dry = false);  ///< internal scan overload
    static IMG_DataBase &IMG_DB();  ///< secure access to database

};

