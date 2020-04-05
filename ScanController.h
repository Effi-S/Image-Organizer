#ifndef SCANCONTROLLER_H
#define SCANCONTROLLER_H
#include <QAbstractItemView>
#include "MyStandardItemModel.h"
#include <QThread>
#include <QMutex>
#include <QProgressBar>
#include <QAbstractItemModel>
#include "ImgOrganizer/ImgMatchFinderBase.h"
#include "ImgOrganizer/SimilarImgFinder.h"
#include "ImgOrganizer/ImgSearch.h"
#include "ImgOrganizer/BitExactImgFinder.h"
#include <QThreadPool>
#include <QRunnable>
#include <QtConcurrent/QtConcurrentRun>


/***********************
 * Thread runnig an algorithm
 *
 * Derrived from QObject for sending signals
 *
 * and from QRunnable for being run in own thread in Qt's Threadpool.
 *
 * receives an algorithm to run in constructor
 *
 * runs algo and then
 *
 * emits signal when algo ready to give results
 *
 *********************** */

class AlgoThread :public QObject, public QRunnable
{
    Q_OBJECT
public:
    AlgoThread(ImgMatchFinderBase * comp)
        :m_comp(comp){}
    void start(){run();}
signals:
    void resultReady();

private:
    void run() override ;
    ImgMatchFinderBase * m_comp;

};
/***********************
 * Thread for adding images to a model
 *
 * Derrived from QObject for sending signals
 *
 * and from QRunnable for being run in own thread in Qt's Threadpool.
 *
 * gets pointer to a model and QStringlist
 *
 * creats image group from QStringlist and emits to the model a signal
 *
 * for adding this group.
 *
 *********************** */

class AddingImgThread :public QObject, public QRunnable
{
    Q_OBJECT
public:
    AddingImgThread( QAbstractItemModel ** model, const QStringList & l );
    void start(){run();}
signals:
    void addRow(QStandardItem *);  ///< signal sent to model for it to add a row

private:
void run() override;
QStringList m_path_list;
QAbstractItemModel ** m_model;

};

/***********************
 * Thread for running an algorithm and sending images
 *
 *  Derrived from QThread as it runs in its own thread.
 *
 * The procedure:
 *
 * 1) creates AlgoThread for running the algorithm.
 *
 * 2) creates AddingImgThread
 *
 * 3) while both are running check AlgoThread for added groups
 *
 * 4) If found emitting to AddingImgThread
 *
 *********************** */

class ScannerThread :public QThread
{
    Q_OBJECT
public:
    ScannerThread(QAbstractItemModel * mod, std::function<ImgMatchFinderBase *()> func, QProgressBar * = nullptr)
        :m_model(mod), m_func(func) {}
    void start(){run();}

signals:
    void Scanning(bool);
    void resultReady(const QString &s);
    void scanPercent(int);
    void sendImgGroup(QStringList);

private:
    void run() override;
    QAbstractItemModel * m_model;
    std::function<ImgMatchFinderBase *()> m_func;
    std::unique_ptr<AlgoThread> m_algo;
    int m_type;
};


/***********************
 * Scan Controller
 *
 * This Class controls all the threads of the algorithms.
 *
 * Derrived from QThread as it runs in its own thread.
 *
 *
 * The procedure:
 *
 * 1) runs the ImgFileScanner
 *
 * 2) creates a ScanThread for each algorithm set to run
 *
 * 3) waits for all of the threads above to finish.
 *
 *********************** */

class ScanController : public QThread
{
    Q_OBJECT
public:
    enum algoType{exact, similar, search};
    ScanController();
    void addModel(QAbstractItemModel *, algoType, QProgressBar * = nullptr);
    void setRoot(const QString & s){m_root = s;}

signals:
     void scanStatus(QString s);
     void scanDone(bool);
private:
    void run() override;
    std::function<ImgMatchFinderBase *()> typeToFunc(algoType);
    QString m_root;
    std::vector<ScannerThread *> m_threads;
    QThreadPool m_pool;

};
#endif // SCANCONTROLLER_H
