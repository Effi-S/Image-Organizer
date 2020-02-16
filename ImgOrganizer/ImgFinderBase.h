#pragma once
#include <vector>
#include <string>
#include <mutex>

class ImgFinderBase
{
public:
	virtual void makeGroups() = 0;
	std::vector<std::vector<std::string>> getGroups();	
	bool isDone() { return m_done; }
	uint32_t numOfImages() { return m_num_of_images; }

protected:
	void doneAddingGroups() { m_done = false; }
	void addGroup(std::vector<std::string>& group);
	void imgAdded() { m_num_of_images++; }
private:
	uint32_t m_num_of_images = 0;
	std::mutex m_mutex;	
	bool m_done = false; 
	std::vector<std::vector<std::string>> m_stringGroups;
};

