#pragma once
#include<iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include <vector>
#include <memory>
#include <unordered_set>
#include <ctime>
#include <future>
#include <mutex>
#include "COLOR.h"
#include <iterator>
#include "MyUtils.h"

/* *********** Img File Scanner **********
 * Recursive image file finder
 *
 * this Class is scans the filesystem for images
 *
 * and saves them in a database for later iteration.
 *
 * ************************************** */

namespace fs = std::filesystem;
using ImgInfo = std::pair<cv::Ptr<const cv::Mat>, std::unique_ptr<std::wstring>> ;
using IMG_DataBase = std::vector<ImgInfo>;
static std::atomic_bool constant_false = false;   // helpful for default atomic bool.

class ImgFileScanner
{

public:

    static void scan(std::wstring path = L"C:\\", std::atomic_bool & = constant_false);  ///< The main scanning function - saves the images in database for later use
    static int getNumberOfImages(std::wstring path = L"C:\\", std::atomic_bool & = constant_false);  ///< Returns the number of images in the path (a dry run).

    // functions for iterating on the images in the database
    auto end(){        return ImgFileScanner::IMG_DB().end();}
    auto begin(){	   return ImgFileScanner::IMG_DB().begin();}
    static auto size() {	   return ImgFileScanner::IMG_DB().size(); }


private:  
    friend void addImgToDB(const fs::directory_entry& entry);  ///< adding to database
    static int _scan(std::wstring path = L"C:\\", std::atomic_bool & = constant_false , bool dry = false);  ///< internal scan overload
    static IMG_DataBase &IMG_DB();  ///< secure access to database

};

