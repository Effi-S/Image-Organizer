#include "ImgMatchFinderBase.h"

std::vector<std::vector<std::wstring>> ImgMatchFinderBase::getMatchGroups()
{
    std::lock_guard<std::mutex> lk(m_mutex);
    return std::move(m_matchGroups);
}

//returns the number of images the algorithm has seen already
uint32_t ImgMatchFinderBase::numberOfImagesFound()
{
    std::lock_guard<std::mutex> lk(m_mutex);
    size_t size =0 ;
    for(auto & x: m_matchGroups)
        size+= x.size();
    return uint32_t(size);
}

uint32_t ImgMatchFinderBase::numberOfGroupsFound()
{
    std::lock_guard<std::mutex> lk(m_mutex);
    return uint32_t(m_matchGroups.size());
}


void ImgMatchFinderBase::addMatchGroup(std::vector<std::wstring>& group)
{
    std::lock_guard<std::mutex> lk(m_mutex);
    m_matchGroups.push_back(group);
}
