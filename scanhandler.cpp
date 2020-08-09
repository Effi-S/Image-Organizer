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
//    m_stop_scan = true;
//    numfu.get();
//    scanfu.get();
//    updatefu.get();
}

void ScanHandler::stop()
{
    emit setFormat("Aborting scan.. this may take a while..");
    m_stop_scan = true;

}


void ScanHandler::run()
{
    std::clock_t start =std::clock();
    emit setFormat("Loading...");

    auto root_copy = m_root;

    scanfu = std::future(std::async([&](){ ImgFileScanner::scan(m_root, std::ref(m_stop_scan)); }));

    numfu = std::future<int>(std::async( &ImgFileScanner::getNumberOfImages , root_copy, std::ref(m_stop_scan)));

    int num_of_images = numfu.get();

    emit setRange(0, num_of_images);
    emit setFormat("Reading images: %v/%m ");

    for(int val=0 ; !m_stop_scan && val < num_of_images; QThread::msleep(100)){
        val = ImgFileScanner::size();
        emit setValue(val);
    }
    scanfu.get();

    emit setFormat("Calculating Matches.. ");  //TODO add more info.
    emit setRange(0,0);

    static std::mutex mu;
    std::lock_guard<std::mutex> lk(mu);

    ImgMatchFinderBase * algo = _algoData[m_algoType].second();

    algo->makeMatchGroups();
    emit setRange(0, algo->numberOfGroupsFound());
    emit setFormat("Adding match groups: %v/%m ");


    int found = 0;
    AddingImgThread addImgThread(_algoData[m_algoType].first);
    for(const auto & x: algo->getMatchGroups()){
        if(m_stop_scan) break;
        QThread::msleep(300);
        addImgThread.addStringList(x);
        emit setValue(++found);

    }
    delete algo;

    m_stop_scan = false;
    std::clock_t time = std::clock() - start;
    emit setFormat(QString("Done scan ") + time);
}

void ScanHandler::setRoot(QString s)
{
    m_root = s.toStdWString();
}

void ScanHandler::setAlgo(int i)
{

    m_algoType = i;
}


