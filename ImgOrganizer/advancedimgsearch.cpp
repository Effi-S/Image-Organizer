#include "advancedimgsearch.h"

std::map<std::string, std::function<AdvancedImgSearch::retType()>>  AdvancedImgSearch::m_functions;
FaceDetector FaceFunctor::m_face_detector = FaceDetector::loadFromYAML();

void AdvancedImgSearch::setNumberOfPeople(const int num)
{
    FaceNumberFunctor f(num);
    m_functions["num_of_people"] = f;
}


void AdvancedImgSearch::setFacesToFind(const std::vector<std::wstring> toFind)
{
    FaceFunctor f(toFind);
     m_functions["face_to_find"] = f;
}

void AdvancedImgSearch::setSearchFile(const std::wstring toFind)
{
    SearchFunctor f(toFind);
     m_functions["search_file"] = f;
}

AdvancedImgSearch::AdvancedImgSearch()
{
    retType found;

    // -- running all functions and getting their images found
        for(const auto & function: m_functions)
            for(const auto x: function.second())
                found.push_back(x);

     // -- removing duplicates.
       std::sort(found.begin(), found.end());
       auto last = std::unique(found.begin(), found.end());
       found.erase(last, found.end());

       for(auto x : found)
           m_matches.push_back(x);


   std::cout <<"Found: " << found.size() <<" images." <<std::endl;

   for(auto & x: m_matches)
       std::wcout << L"Found: " <<x <<std::endl;

}

void AdvancedImgSearch::makeMatchGroups()
{
    for(auto &x :m_matches)
    {
        std::vector<std::wstring> w = {x};
        this->addMatchGroup(w);
    }

}
