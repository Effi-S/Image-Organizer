#include "scanhandler.h"
#include <QThread>


std::map<int, std::pair<MyStandardItemModel *, std::function<ImgMatchFinderBase *()> >> ScanHandler::_algoData;

ScanHandler::ScanHandler()
{

}

void ScanHandler::registerAlgo(int type, QAbstractItemModel * mod,
                               std::function<ImgMatchFinderBase *()>  func)
{
    auto model = static_cast<MyStandardItemModel *>(mod);
    if(!mod){
            std::cerr << "WRONG MODEL TYPE!" <<std::endl;
            return;
            }
    _algoData.emplace(type, std::make_pair(model, func));

}

void ScanHandler::setBar(QProgressBar *bar)
{
   connect(this , &ScanHandler::setRange, bar, &QProgressBar::setRange);
   connect(this , &ScanHandler::setValue, bar, &QProgressBar::setValue);
   connect(this , &ScanHandler::setFormat, bar, &QProgressBar::setFormat);

}

ScanHandler::~ScanHandler()
{


}

void ScanHandler::stop()
{

//    t1.reset(nullptr);
//    t2.reset(nullptr);

}


void ScanHandler::run()
{

    std::cout<< numfu.valid() << " " << scanfu.valid() << " " << updatefu.valid() <<std::endl;

    emit setFormat("Loading...");

    auto root_copy = m_root;

    scanfu = std::future(std::async([&](){ImgFileScanner::scan(m_root);}));

    numfu = std::future<int>(std::async(&ImgFileScanner::getNumberOfImages, root_copy));

    int num_of_images = numfu.get();
    emit setRange(0, num_of_images);
    emit setFormat("Reading images: %v/%m");

    for(int val=0; val < num_of_images; QThread::msleep(200)){
        val = ImgFileScanner::size();
        emit setValue(val);
    }
    scanfu.get();

    emit setFormat("Finding matches: %v/%m");

    static std::mutex mu;
    std::lock_guard<std::mutex> lk(mu);

    ImgMatchFinderBase * algo = _algoData[m_algoType].second();

    algo->makeMatchGroups();
    emit setRange(0, algo->numberOfGroupsFound());
    emit setFormat("Adding match groups: %v/%m");


    int found = 0;
    AddingImgThread addImgThread(_algoData[m_algoType].first);
    for(const auto & x: algo->getMatchGroups()){
        QThread::msleep(200);
        addImgThread.addStringList(x);
        emit setValue(++found);

    }
    delete algo;

}

void ScanHandler::setRoot(QString s)
{
    m_root = s.toStdString();
}

void ScanHandler::setAlgo(int i)
{
    m_algoType = i;
}


