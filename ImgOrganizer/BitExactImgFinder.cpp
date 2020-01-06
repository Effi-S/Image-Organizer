#include "BitExactImgFinder.h"

void BitExactImgFinder::show()
{
	for (const auto& x : m_matches)
	{
		if (x.second.size() < 2)continue;
		std::string wind1 = "pic1window";

		std::string temp = "-";
		std::vector<std::string> windows;
		for (auto& img : x.second)
		{
			windows.push_back(temp);
			cv::namedWindow(temp, cv::WINDOW_GUI_EXPANDED);
			cv::imshow(temp, img.first);
			temp += "-";
		}
		cv::waitKey(0);
		for (auto window : windows)
			cv::destroyWindow(window);
	}
}

void BitExactImgFinder::makeSet()
{
	m_algo = cv::img_hash::PHash::create();

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
