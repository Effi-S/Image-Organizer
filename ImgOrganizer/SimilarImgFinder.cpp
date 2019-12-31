#include "SimilarImgFinder.h"


void SimilarImgFinder::show()
{
	for (const auto& x : m_matches)
	{
		if (x.second.second.size() < 2)continue;
		std::string wind1 = "pic1window";
		
		std::string temp = "a";
		std::vector<std::string> windows;
		int limit = 0;
		for (auto& img : x.second.second)
		{
			limit++;
			if (limit >= 10)break;
			windows.push_back(temp);
			cv::namedWindow(temp, cv::WINDOW_GUI_EXPANDED);
			cv::imshow(temp, img);
			temp += "a";
		}
		cv::waitKey(0);
		for (auto window : windows)
			cv::destroyWindow(window);

	}
}

void SimilarImgFinder::makeSet()
{
	

	for (auto& x : ImgScanner::IMG_DB())
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
			m_matches.emplace( k, HashValue(imHash, std::list<cv::Mat>()));

		m_matches.at(k).second.push_back(*x.first);
	}

	if (m_matches.size() <= 1)return;
	
	auto next = m_matches.begin();
	next++;
	for (auto it = m_matches.begin(); next != m_matches.end() ;++next)
	{
		cv::Mat hash1(it->second.first);
		cv::Mat hash2(next->second.first);

		auto matches = m_algo->compare(hash1,hash2);
		if (matches <= 35)
		{			
			next->second.second.splice(next->second.second.end(), it->second.second);
			m_matches.erase(it++);  
		}
		else		
			++it;
		
	}

}
