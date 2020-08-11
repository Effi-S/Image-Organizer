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

/***********************
 * Class for handeling a Scan request
 * Derived from QThread so it will ocur on it's own thread
 * under Qt's event loop.
 *
 * Connects Front end with back end.
 * Connects QProgressBars with the events it handles.
 * Sends variace tasks utilizing std concurency.
 * ********************** */

class ScanHandler : public QThread
{
 Q_OBJECT
public:
    ScanHandler();

    void registerAlgo(int, QAbstractItemModel *mod, std::function<ImgMatchFinderBase *()> ); ///< factory function.
    void setBar(QProgressBar * bar); ///< setting QProgressBars to connect events to.

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
                std::function<ImgMatchFinderBase *()>>>_algoData; ///< Holds data for possible scans.
    std::wstring m_root; ///< directory to search.

    int m_algoType = 0;
    std::future<int> numfu; ///< future for getting number of images recursivly
    std::future<void> scanfu;  ///< future for searching for images recursively
    std::future<void> updatefu; ///< future for updating.
    std::atomic_bool  m_stop_scan = false; ///< boolian for stopping futures.


};



#endif // SCANHANDLER_H
