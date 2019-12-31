#include "ImgScanner.h"
#include "BitExactImgFinder.h"
#include "SimilarImgFinder.h"

#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define ORANGE  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */


#define BIT_EXACT 1
#define SIMILAR 0


int main(){	
	//scanning for images
	std::clock_t start(std::clock());
	std::cout <<ORANGE<< "Scanning... " << RESET << std::endl;

	ImgScanner::scan(L"C:\\Users\\effi");
	
	std::cout <<GREEN<< "Time reading images scan took: " << RESET << double(std::clock()) - start << std::endl;


#if BIT_EXACT  
	std::cout << ORANGE << "Computing Bit exact... " <<RESET<< std::endl;

	start = std::clock_t(std::clock());

	BitExactImgFinder comp;

	std::cout << GREEN << "Time BitExactImgFinder took: " << RESET << double(std::clock()) - start<<std::endl;

	comp.show();

#endif // BIT_EXACT

#if SIMILAR  

	std::cout << ORANGE << "Computing Similar finder... " << RESET << std::endl;

	start = std::clock_t(std::clock());

	SimilarImgFinder comp2;

	std::cout <<GREEN<< "Time SimilarImgFinder took: "<<RESET << double(std::clock()) - start << std::endl;

	comp2.show();

#endif

	return 0;
}


