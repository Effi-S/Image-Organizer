#pragma once
#ifndef SCANTHREAD_H
#define SCANTHREAD_H

#endif // SCANTHREAD_H
#include <QMutex>
#include <QThread>
#include <MyStandardItem.h>
#include "ImgOrganizer/ImgFinderBase.h"
#include "BitExactImgFinder.h"
#include "SimilarImgFinder.h"

class innerThread : public QThread
{
    Q_OBJECT
public:
    innerThread(ImgFinderBase * comp)
        :m_comp(comp){}
signals:
    void resultReady(const QString &s);
private:
    ImgFinderBase * m_comp;
    void run() override {
        m_comp->makeGroups();
    }
};

class ScanThread : public QThread
{
    Q_OBJECT
public:
    ScanThread(QString& dir , int type)
        :m_dir(dir), m_type(type){}
signals:

    void resultReady(const QString &s);
    void scanDone(bool);
    void scanStatus(QString s, int = 0);
    void scanPercent(int);
    void sendImgGroup(QStringList);

private:
    QString m_dir;
    int m_type;

    void run() override {
        std::clock_t start(std::clock());
        QString result;
        int dbSize = 1;

        try {
            emit scanStatus("searching for images.");
            ImgScanner::scan(m_dir.toStdString());
            dbSize = int(ImgScanner::size());
            emit scanStatus("Found: "+ QString::number(dbSize) +"images.");
            std::cout <<ORANGE<< "Time reading images scan took: " <<GREEN<< double(std::clock()) - start <<RESET<< std::endl;

        } catch (...) {
            std::cout<<"scan failed!"<<std::endl;
        }
        try {
            ImgFinderBase * comp;
              (m_type)?comp = new SimilarImgFinder:comp = new BitExactImgFinder;
            std::cout <<ORANGE<< "Time scan + ImgFinder took: " <<GREEN<< double(std::clock()) - start <<RESET<< std::endl;
            innerThread t(comp);
            t.start();
           dbSize = (dbSize)?dbSize : 1;

            while (t.isRunning()) {
                for(auto i: comp->getGroups())
                {
                    QStringList l;
                    for(auto mem: i)
                    {
                        l.append(mem.c_str());

                    }

                    int pr = (100*int(comp->numOfImages()))/dbSize;
                    emit scanPercent(pr);
                    emit sendImgGroup(l);

                }

            }

        } catch (...) {
            std::cout<<"ImgFinder failed!"<<std::endl;
        }

        emit scanDone(true);

    }
};

class addImgThread : public QThread
{
    Q_OBJECT
public:
    addImgThread(QStringList pl, MyStandardItemModel ** model ):m_path_list(pl),m_model(model){};
    void setList(const QStringList & l) {

        m_mutex.lock();
        m_path_list = l;
        m_mutex.unlock();
    }
protected:

    void run() override
        {
        m_mutex.lock();

            auto first = m_path_list.cbegin();

            QStandardItem *group = new QStandardItem(QIcon(*first),
                                                     QVariant(m_path_list.length()).toString());

            for(;first != m_path_list.cend(); ++first)
            {
                QStandardItem *child = new QStandardItem(QIcon(*first) ,*first);


                child->setToolTip(*first);
                child->setCheckable(true);
                child->setDragEnabled(true);
                child->setDropEnabled(true);
                if(first!=m_path_list.cbegin())
                    child->setCheckState(Qt::Checked);
                group->appendRow(std::move(child));
            }
            //group->setCheckable(true);
            (*m_model)->appendRow(std::move(group));
      m_mutex.unlock();
    }

QStringList m_path_list;
MyStandardItemModel ** m_model;
QMutex m_mutex;
};
