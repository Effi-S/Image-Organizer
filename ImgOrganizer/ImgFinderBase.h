#pragma once
#include <vector>
#include <string>
#include <mutex>

class ImgFinderBase
{
public:
	virtual void makeGroups() = 0;
	std::vector<std::vector<std::string>> getGroups();	

	uint32_t numOfImages() { return m_num_of_images; }

protected:
	void addGroup(std::vector<std::string>& group);

private:
	uint32_t m_num_of_images = 0;
	std::mutex m_mutex;	

	std::vector<std::vector<std::string>> m_stringGroups;
};

