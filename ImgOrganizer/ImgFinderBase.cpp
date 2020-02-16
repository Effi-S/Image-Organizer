#include "ImgFinderBase.h"

std::vector<std::vector<std::string>> ImgFinderBase::getGroups()
{
	std::lock_guard<std::mutex> lk(m_mutex);
	return std::move(m_stringGroups);
}

void ImgFinderBase::addGroup(std::vector<std::string>& group)
{
	std::lock_guard<std::mutex> lk(m_mutex);
	m_stringGroups.push_back(group);
    m_num_of_images+=group.size();
}
