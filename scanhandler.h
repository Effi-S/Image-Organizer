#ifndef SCANHANDLER_H
#define SCANHANDLER_H
#include <QProgressBar>
#include "MyStandardItemModel.h"
#include "ImgOrganizer/ImgMatchFinderBase.h"
#include "ImgOrganizer/ImgFileScanner.h"
#include <QtConcurrent/QtConcurrentRun>
#include <QThread>
#include <QFuture>
#include "addimgthread.h"
#include "ImgOrganizer/BitExactImgFinder.h"
#include <thread>
#include <QMutex>
#include <future>


class ScanHandler : public QThread
{
 Q_OBJECT
public:
    ScanHandler();

    void registerAlgo(int, QAbstractItemModel *mod, std::function<ImgMatchFinderBase *()> );
    void setBar(QProgressBar * bar);

    ~ ScanHandler();

signals:
    void reset();
    void setRange(int min ,int max);
    void setValue(int);
    void setFormat(QString);

public slots:
    void stop();
    void setRoot(QString);
    void setAlgo(int);
private:
    void run() override;


    static std::map<int, std::pair<MyStandardItemModel *,
                std::function<ImgMatchFinderBase *()>>>_algoData;
    std::wstring m_root;

    int m_algoType = 0;
    std::future<int> numfu;
    std::future<void> scanfu;
    std::future<void> updatefu;
    std::atomic_bool  m_stop_scan = false;


};



#endif // SCANHANDLER_H
