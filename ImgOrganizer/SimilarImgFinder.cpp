#include "SimilarImgFinder.h"
#include "ImgMatchFinderBase.h"

void SimilarImgFinder::makeMatchGroups()
{
	for (const auto& x : m_matches)
	{
		std::vector<std::string> group;
		for (auto& img : x.second.second)
			group.push_back(img.second.c_str());
		
		addMatchGroup(group);
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


void SimilarImgFinder::makeListOfSimilarImages()
{  
    // 1. creating list of digests (key) paired with the image itself (imgValue)
    for (auto &img_path_pair : ImgFileScanner())
	{
        // 1.1 getting the algorithm's output
        cv::Mat imgValue = *img_path_pair.first; // getting the image
		
        cv::Mat imgHash;

        m_algo->compute(imgValue, imgHash);

       // 1.2 creating a digest key from the output
        auto* ptr = imgHash.data;

        std::string key;

        for (uint16_t i = 0; i < KEY_SIZE; ++i, ++ptr)
            key += *ptr;

        // 1.3 adding key to list of keys
        auto it = m_matches.find(key);

		if (it == m_matches.end())
            m_matches.emplace(key, HashValue(imgHash, std::list<ImgInfo>()));


        m_matches.at(key).second.push_back(ImgInfo(imgValue , *img_path_pair.second));
		
	}

	
    // 2. reducing list by splicing the list where the key values have enough similar points
	for (auto it = m_matches.begin(); it != m_matches.end(); ++it)
	{
        bool first = true;
        for (auto next = it; next != m_matches.end(); ++next)
		{
            // ( skipping first key )
			if (first)
			{
				first = false;
				continue;
			}

            // 2.1 getting number of similar points
			cv::Mat hash1(it->second.first);
			cv::Mat hash2(next->second.first);

            auto matches = m_algo->compare(hash1, hash2);


            // 2.2 if there are enough similarities splicing the list
            if (matches <= SIMILARITY_DELTA || OrbMatcher().numberOfMatches(it->second.first, next->second.first) > SIMILARITY_DELTA)
			{
				next->second.second.splice(next->second.second.end(), it->second.second);
				m_matches.erase(it++);
			}
		}
	}

}
