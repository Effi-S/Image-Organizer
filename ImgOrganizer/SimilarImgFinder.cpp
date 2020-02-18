#include "SimilarImgFinder.h"
#include "ImgFinderBase.h"

void SimilarImgFinder::makeGroups()
{
	for (const auto& x : m_matches)
	{
		std::vector<std::string> group;
		for (auto& img : x.second.second)
			group.push_back(img.second.c_str());
		addGroup(group);
	}
	
}

//	for (const auto& x : m_matches)
//	{
//		if (x.second.second.size() < 2)continue;
//		std::string wind1 = "pic1window";
		
//		std::string temp = "a";
//		std::vector<std::string> windows;
//		int limit = 0;
//		for (auto& img : x.second.second)
//		{
//			limit++;
//			if (limit >= 10)break;
//			windows.push_back(temp);
//			cv::namedWindow(temp, cv::WINDOW_GUI_EXPANDED);
//            cv::imshow(temp, img.first);
//			temp += "a";
//		}
//		cv::waitKey(0);
//		for (auto window : windows)
//			cv::destroyWindow(window);

//	}


void SimilarImgFinder::makeSet()
{  
	//creating list 
    for (auto &x : ImgScanner())
	{
		cv::Mat im = *x.first;
		cv::Mat imHash;

		try {
			m_algo->compute(im, imHash);
		}
		catch (std::exception & e)
		{
			std::cout << "error: in SimilarFinder: " << e.what() << std::endl;
			continue;
		}


		auto* p = imHash.data;


		std::string k;

		for (uint16_t i = 0; i < BITS; ++i, ++p)
			k += *p;

		auto it = m_matches.find(k);

		if (it == m_matches.end())
            m_matches.emplace( k, HashValue(imHash, std::list<ImgInfo>()));


        m_matches.at(k).second.push_back(ImgInfo( im , *x.second));
	}

	if (m_matches.size() <= 1)return;
	
//reducing list where neccessary
	for (auto it = m_matches.begin(); it != m_matches.end(); ++it)
	{
		bool first = true;
		for (auto next = it; next != m_matches.end(); ++next)
		{
			if (first)
			{
				first = false;
				continue;
			}
			cv::Mat hash1(it->second.first);
			cv::Mat hash2(next->second.first);

			auto matches = m_algo->compare(hash1, hash2);
            if (matches <= 30)
			{
				next->second.second.splice(next->second.second.end(), it->second.second);
				m_matches.erase(it++);
			}
		}
	}

}
