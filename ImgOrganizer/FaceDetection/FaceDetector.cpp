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
    if (!std::filesystem::is_directory(saveTo))
        std::filesystem::create_directories(saveTo);

    auto label_path = std::filesystem::path().append(saveTo).append(label);

    std::filesystem::create_directory(label_path);

    // (ii) - convert images to grayscale and add to directory
    std::vector<cv::Mat> gray_images;
        int num = 0;
        for (auto& x : images)
        {
            try {
                cv::Mat img =x ;
               
                // convert to gray scale

                cv::cvtColor(x, img, cv::ColorConversionCodes::COLOR_BGR2GRAY);

               // write image in directory 
                std::string filename = label_path.string() + "/" + std::to_string(++num) + ".jpg";

                std::replace(filename.begin(), filename.end(), '\\', '/');

                cv::imwrite(filename, img);  // writ img to directory
                gray_images.push_back(img);
            }
            catch (cv::Exception& e) {
                std::cout << e.msg << std::endl;
            } catch(std::exception & e){
                std::cout <<e.what() <<std::endl;
            }
        }
        
    // (iii) updateing the model:

        addUserLabel(label); // update local label map
        
        int lbl = this->m_userLabels.at(label);  

        std::vector<int> labels;
        for (const auto& x :gray_images)
            labels.push_back(lbl);

        try {
            m_model->update(gray_images, labels);
        } catch (std::exception & e) {
            std::cerr <<"Update ERROR:\n" << e.what() <<std::endl;
        }

}

///< searches for and returns all images with label
std::vector<std::wstring> FaceDetector::searchFor(std::wstring label, bool draw) 
{    std::clock_t start(std::clock());
   
    std::vector<std::wstring> foundImages;

     auto labelMap =(m_userLabels.size() == 0)? _getUserLabelMap(): m_userLabels;

     // getting integer of label
    auto it = labelMap.find(label);

     if (it == labelMap.end())
        return std::vector<std::wstring>{L"Bad Label"};  // returning if label doesn't exist

    int targetLabel = it->second;  // the integer to corresponding to label find
    std::wcout << L"Searching For: " << label <<" " <<targetLabel<< std::endl;
    // searching for images that match

    for (const auto& x : ImgFileScanner())
    {   
            cv::Mat im, face;

            if (x.first->empty())continue;
        
            cv::cvtColor(*x.first, face, cv::ColorConversionCodes::COLOR_BGR2GRAY);  // converting to grayscale image
            if(im.channels() >1)
                continue;

//           face = m_cropper.cropOutFace(im, true);

            if(face.empty())
                continue;

            int predictedLabel = -1;
            double confidence = 0.0;
            
            try {  m_model->predict(face, predictedLabel, confidence); }
            catch (std::exception & e) {
                std::cout << e.what() << std::endl;
                continue; 
            }
            std::cout << "predicted label:" << predictedLabel <<std::endl;
            if (predictedLabel == targetLabel) {
                foundImages.push_back(*x.second);
                std::wcout << *x.second <<L" c:" <<confidence <<std::endl;   
            }
            if (draw) {
                cv::imshow(std::to_string(predictedLabel), *x.first);
                cv::waitKey(0);
                cv::destroyWindow(std::to_string(predictedLabel));
            }
    }
    std::cout << "...Done Searching! Time: " << std::clock() - start << " Found: "<<foundImages.size() << std::endl;
    return foundImages;
}

void FaceDetector::save(std::string yml)
{
    std::cout << "Saving model to: " <<yml<< std::endl;
    m_model->write(yml);
}

std::vector<std::wstring> FaceDetector::getUserLabels(std::string path)
{

    std::vector<std::wstring> labels;
    for (auto x : FaceDetector::_getUserLabelMap())
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

