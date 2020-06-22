#include "FaceDetector.h"
#include "../ImgFileScanner.h"
#include <iostream>


FaceDetector::FaceDetector(const std::string& yml)
{
    std::clock_t start(std::clock());
    try {
        std::cout << "Loading model from: " << yml << "..." << std::endl;
        m_model->read(yml);
        std::cout << "...Done Loading model! Time: " << std::clock() - start << std::endl;

    }
    catch (cv::Exception & e) {
        std::cout << "CV ERROR:" << e.msg << std::endl;
    }
    catch (std::exception & e)
    {
        std::cout << "STD ERROR:" << e.what() << std::endl;
    }
}

FaceDetector::FaceDetector(const std::string& csv, const std::string& root_dir)
    : m_training_labels_csv(csv) {
    std::clock_t start(std::clock());
        std::vector<cv::Mat> images;
        std::cout << "Reading from CSV file: " << m_training_labels_csv <<"..."<< std::endl;
        
        std::vector<int> labels;
        read_csv(images, labels);  // Read in the data from csv
        
        
        
        std::cout << "Done Reading CSV, found "<<labels.size() << " Labels" << std::endl <<"Training Model.. "<<std::endl;
        try {
            m_model->train(images, labels);
        }
        catch (cv::Exception & e)
        {
            std::cout << "ERROR : " << e.msg << std::endl;
            exit(1);
        }

         std::cout << "...Done Training new model! Time: " << std::clock() - start << std::endl;
};

void FaceDetector::addTrainingSet(std::vector<cv::Mat> images, std::wstring label, std::string saveTo)
{
    // (i) - create directory
    
    auto label_path = std::filesystem::path().append(saveTo).append(label);

    std::filesystem::create_directory(label_path);

    // (ii) - convert images to grayscale and add to directory
   
        int num = 0;
        for (auto& x : images)
        {
            try {
                cv::Mat img =x ;
               
                // convert to gray scale
               if(img.depth() > 0)
                    cv::cvtColor(x, img, cv::ColorConversionCodes::COLOR_BGR2GRAY);

               // write image in directory 
                std::string filename = label_path.string() + "/" + std::to_string(num) + ".jpg";

                std::replace(filename.begin(), filename.end(), '\\', '/');

                cv::imwrite(filename, img);  // writ img to directory
            }
            catch (cv::Exception& e) {
                std::cout << e.msg << std::endl;
            }
        }
        
    // (iii) updateing the model:

        addUserLabel(label); // update local label map
        
        int lbl = this->m_userLabels.at(label);  

        std::vector<int> labels;
        for (const auto& x : images)
            labels.push_back(lbl);

        m_model->update(images, labels);
}

///< searches for and returns all images with label
std::vector<std::wstring> FaceDetector::searchFor(std::wstring label, bool draw) 
{    std::clock_t start(std::clock());
    std::wcout << L"Searching For: "<< label  <<std::endl;

    std::vector<std::wstring> foundImages;
    ImgFileScanner scanner;

    // getting integer of label
    auto it = m_userLabels.find(label);
    if (it == m_userLabels.end())
        return std::vector<std::wstring>{L"Bad Label"}; // returning if label doesn't exist 

    int targetLabel = it->second; // the integer to find

    // searching for images that match
    for (const auto& x : ImgFileScanner())
    {
        try {
            cv::Mat img; 

            if (x.first->empty())continue;

            cv::cvtColor(*x.first, img, cv::ColorConversionCodes::COLOR_BGR2GRAY);  // converting to grayscale image

            int predictedLabel = m_model->predict(img);
            if (predictedLabel == targetLabel) {
                foundImages.push_back(*x.second);
                if (draw)
                {
                    cv::imshow(std::to_string(predictedLabel), *x.first);
                    cv::waitKey(0);
                }
            }
        }
        catch (cv::Exception& e){
            std::wcout << *x.second << std::endl << e.what() << std::endl;
        }     
    }
    std::cout << "...Done Searching! Time: " << std::clock() - start << " Found: "<<foundImages.size() << std::endl;
    return foundImages;
}

void FaceDetector::save(std::string yml)
{
    m_model->write(yml);
}

std::vector<std::wstring> FaceDetector::getUserLabels(std::string path)
{
    std::vector<std::wstring> labels;
    for (auto x : _getUserLabelMap())
        labels.push_back(x.first);
    return labels;
}

void FaceDetector::read_csv(std::vector<cv::Mat>& images, std::vector<int>& labels) {

    std::wifstream file(m_training_labels_csv.c_str(), std::wifstream::in, std::wifstream::binary);
    file.imbue(std::locale("he_IL.UTF8"));

    std::vector<std::wstring> successfull, failed;
    std::wstring line, path, classlabel;
    
    while (std::getline(file, line)) {
        std::wstringstream liness(line);
        std::getline(liness, path, separator);
        std::getline(liness, classlabel);
        if (!path.empty() && !classlabel.empty()) {
            
                // --  check if image exists 
                if (!std::filesystem::exists(path)) {
                    auto save = path;
                    path = L"../../" + path;
                    if (!std::filesystem::exists(path)){
                        failed.push_back(save);
                        continue;
                    }      
                }
                // -- read image
                auto d = MyUtils::unicodeImgRead(path, cv::IMREAD_GRAYSCALE);
                if (d.dims == 0)
                    failed.push_back(path);
                else {
                    std::replace(path.begin(), path.end(), L'\\', L'/');
                    images.push_back(d);
                    addUserLabel(classlabel);
                    labels.push_back(m_userLabels.at(classlabel));
                    successfull.push_back(path);
                }
            
        }
    }  
    for (auto& x : failed)
        std::wcout <<L"Failed to read: "<< x << std::endl;
    std::wcout << L"Successfully read: " << successfull.size() << " failed to read: " << failed.size() << L"\n";
}

std::unordered_map<std::wstring, int> FaceDetector::_getUserLabelMap()
{
    std::unordered_map<std::wstring, int> lblMap;
    // getting user labels from file
    std::wifstream file(USER_LABELS, std::wifstream::in, std::wifstream::binary);
    file.imbue(std::locale("he_IL.UTF8"));

    std::wstring line, name, number;
    while (std::getline(file, line)) {
        std::wstringstream liness(line);
        std::getline(liness, name, separator);
        std::getline(liness, number);
        int num =  std::stoi(number);
        lblMap.emplace(name, num);
    }
    
    return lblMap;
}
void FaceDetector::addUserLabel(const std::wstring& lbl)
{
    if (m_userLabels.find(lbl) == m_userLabels.end())
    {
        //adding to local map
        int num = m_userLabels.size() + 1;
        m_userLabels.emplace(lbl, num);

        //adding to file
        std::wofstream woFile(USER_LABELS, std::wofstream::app | std::wofstream::binary);
        woFile.imbue(std::locale("he_IL.UTF8"));
        woFile << lbl << separator << num << std::endl;
    }
}

