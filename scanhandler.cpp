#include "scanhandler.h"
#include <QThread>
ScanHandler::ScanHandler()
{

}

void ScanHandler::registerAlgo(int type, QAbstractItemModel *mod, std::function<ImgMatchFinderBase *()> func)
{
    auto model = static_cast<MyStandardItemModel * >(mod);
    if(!mod){
            std::cout << "WRONG MODEL TYPE!" <<std::endl;
            exit(-1);
            }
    _algoData.emplace(type, std::make_pair(model, func));

}

void ScanHandler::setBar(QProgressBar *bar)
{
//    bar->setRange(0, 0);
//    std::cout << " outer: " << QThread::currentThreadId() << std::endl;

}

/**  While it is neccessary to use QThread to free the GUI
 * and use signals and slots mechanism
 * I preffered to use std::thread because for me ore reliable
 * than QThread or QtConcurrent options.
**/
void ScanHandler::run()
{
    ImgMatchFinderBase * algo;
    std::clock_t start(std::clock());


    int num_of_images;
    std::thread t2([&](){num_of_images = ImgFileScanner::getNumberOfImages();});

    std::thread t1([&](){ImgFileScanner::scan(m_root.toStdString());   });
    t2.join();
    std::cout << "Number of images = "<<num_of_images <<"Time:" <<double(std::clock()) - start<<std::endl;
    t1.join();
    t1 = std::thread([&](){algo = _algoData[m_algo].second(); algo->makeMatchGroups();});
    t1.join();
    t1 = std::thread([&](){AddingImgThread addImgThread(_algoData[m_algo].first);
                for(const auto & x: algo->getMatchGroups())
                    addImgThread.addStringList(x);
        });
    t1.join();

    std::cout << "Done with thread: " << QThread::currentThreadId() << " ";
    std::cout << "root: " <<m_root.toStdString() << " ";
    std::cout << "Algo: " <<m_algo <<std::endl;

    std::cout << "DoneTime:" <<double(std::clock()) - start<<std::endl;

}

void ScanHandler::setRoot(QString s)
{
    m_root = s;
}

void ScanHandler::setAlgo(int i)
{
    m_algo = i;
}


