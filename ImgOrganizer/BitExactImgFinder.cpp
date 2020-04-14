#include "BitExactImgFinder.h"


void BitExactImgFinder::makeMatchGroups()
{
	for (const auto& x : m_matches)
	{
        std::vector<std::wstring> group;
		for (auto& img : x.second)
            group.push_back(img.second->c_str());
       addMatchGroup(group);
	}
}

// Creates map of digests (key) paired with the image itself (imgValue)
void BitExactImgFinder::makeImageMap()
{
	m_algo = cv::img_hash::BlockMeanHash::create(0);


    ImgFileScanner scanner;
    for (const auto& x : scanner)
	{
        // 1. getting the algorithm's output
		cv::Mat im = *(x.first);
		cv::Mat imHash;

        m_algo->compute(im, imHash);

        // 2. creating a digest key from the output
        auto* ptr = imHash.data;

        std::string key;

        for (uint16_t i = 0; i < KEY_SIZE; ++i, ++ptr)
            key += *ptr;

        // 3. adding key to list of keys
        auto it = m_matches.find(key);

		if (it == m_matches.end())
            m_matches.emplace(key, std::vector<ImgInfo>());

        m_matches.at(key).push_back(ImgInfo(im, x.second.get()));
	}
}
