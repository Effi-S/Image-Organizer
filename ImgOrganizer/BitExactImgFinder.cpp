#include "BitExactImgFinder.h"

void BitExactImgFinder::show()
{
	for (const auto& x : m_matches)
	{
        std::vector<std::string> group;
		for (auto& img : x.second)
            group.push_back(img.second->c_str());
        m_stringGroups.push_back(group);
	}
}

void BitExactImgFinder::makeSet()
{
	m_algo = cv::img_hash::BlockMeanHash::create(0);

    ImgScanner scanner;
    for (const auto& x : scanner)
	{
		cv::Mat im = *(x.first);
		cv::Mat imHash;

		try {
			m_algo->compute(im, imHash);
		}
		catch (...)
		{
			continue;
		}
		auto* p = imHash.data;

		std::string k;

		for (uint16_t i = 0; i < BITS; ++i, ++p)
			k += *p;

		auto it = m_matches.find(k);

		if (it == m_matches.end())
			m_matches.emplace(k, std::vector<ImgInfo>());

		m_matches.at(k).push_back(ImgInfo(im, x.second));
	}
}
