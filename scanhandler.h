#ifndef SCANHANDLER_H
#define SCANHANDLER_H
#include <QProgressBar>
#include "MyStandardItemModel.h"
#include "ImgOrganizer/ImgMatchFinderBase.h"
#include <QObject>
#include "ImgOrganizer/ImgFileScanner.h"
#include <QThread>
#include <QtConcurrent/QtConcurrentRun>
#include "addimgthread.h"
#include <QFutureWatcher>
#include <thread>  // Because QThread and QtConcurrent::map/run are extremely slow and buggy
class ScanHandler : public QThread
{
 Q_OBJECT
public:
    ScanHandler();
    void registerAlgo(int, QAbstractItemModel * mod, std::function<ImgMatchFinderBase *()> func);
    void setBar(QProgressBar * bar);

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
    std::map<int, std::pair<MyStandardItemModel *,
                std::function<ImgMatchFinderBase *()>>> _algoData;
    QString m_root;
    std::thread * t1, *t2; ///< INTERNAL THREADS
    int m_algo = 0;

};



#endif // SCANHANDLER_H
