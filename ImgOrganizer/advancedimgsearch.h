#pragma once
#include <vector>
#include <tuple>
#include "ImgMatchFinderBase.h"
#include "ImgFileScanner.h"
#include "FaceDetection/FaceDetector.h"
#include "FaceDetection/FacesCropped.h"
#include "ImgSearch.h"

class AdvancedImgSearch : public  ImgMatchFinderBase
{
    using retType = std::vector<std::wstring>;
public:

    static void setNumberOfPeople(const int num);
    static void setFacesToFind(const std::vector<std::wstring> toFind);
    static void setSearchFile(const std::wstring toFind);
    AdvancedImgSearch();
    void makeMatchGroups() override;
    ~AdvancedImgSearch() override = default;
private:
    std::vector<std::wstring> m_matches;
    static std::map<std::string, std::function<retType()>>  m_functions;

};

// ---------   functors --------------
class FaceFunctor{
public:
    FaceFunctor(std::vector<std::wstring> wVec ): msearchfor(wVec){}
    std::vector<std::wstring> operator()(){
        std::vector<std::wstring> found;
        std::cout << "size: " <<msearchfor.size()<<std::endl;
        for(auto w: msearchfor)
        {

            for(auto x: m_face_detector.searchFor(w))
                if(x != L"Bad Label"){
                    found.push_back(x);
                    std::wcout << "found label: " <<x <<std::endl;
                }

            else
                  std::wcout << L"NOT found -- Bad Label "<<std::endl;
        }


        return found;
    }
 private:
    static FaceDetector m_face_detector;
    std::vector<std::wstring> msearchfor;
};

class SearchFunctor{
public:
    SearchFunctor(std::wstring w):m_file(w){}
    std::vector<std::wstring> operator()(){
       ImgSearch searcher;
       searcher.searchFor(m_file);
       std::vector<std::wstring> ret;

       for(auto group: searcher.getMatchGroups())
           for(auto x: group)
               ret.push_back(x);
       return ret;
    }
private:
    std::wstring m_file;
};

class FaceNumberFunctor{
public:
    FaceNumberFunctor(int num):m_num(num){}
    std::vector<std::wstring> operator()(){
        FacesCropped cropper;
        std::vector<std::wstring> ret;

        for (auto &img_path_pair : ImgFileScanner())
            if(cropper.numberOfFaces(*img_path_pair.first) == m_num)
                ret.push_back(std::wstring(*img_path_pair.second));

        return ret;
    }
    private:
    int m_num;
};

//-----------  ------------ ------------
