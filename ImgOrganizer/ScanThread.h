#pragma once
#ifndef SCANTHREAD_H
#define SCANTHREAD_H

#endif // SCANTHREAD_H
#include <QMutex>
#include <QThread>
#include <MyStandardItem.h>
#include "ImgOrganizer/ImgMatchFinderBase.h"
#include "BitExactImgFinder.h"
#include "SimilarImgFinder.h"

class innerThread : public QThread
{
    Q_OBJECT
public:
    innerThread(ImgMatchFinderBase * comp)
        :m_comp(comp){}
signals:
    void resultReady(const QString &s);
private:
    ImgMatchFinderBase * m_comp;
    void run() override {
        auto start = double(std::clock());
        m_comp->makeMatchGroups();
        std::cout <<ORANGE<< "ImgFinder took: " <<GREEN<< double(std::clock()) - start <<RESET<< std::endl;
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

    void run() override
    {
        std::clock_t start(std::clock());
        QString result;
        int dbSize = 1;


            emit scanStatus("searching for images.");
            ImgFileScanner::scan(m_dir.toStdString());
            dbSize = int(ImgFileScanner::size());

            emit scanStatus("Found: "+ QString::number(dbSize) +"images.");
            std::cout <<ORANGE<< "Time reading images scan took: " <<GREEN<< double(std::clock()) - start <<RESET<< std::endl;

            ImgMatchFinderBase * comp;
              (m_type)?comp = new SimilarImgFinder:comp = new BitExactImgFinder;

           innerThread t(comp);
           t.start();
           dbSize = (dbSize)?dbSize : 1;

         while (!t.isFinished() || comp->getMatchGroups().size()>0) {
             for(auto i: comp->getMatchGroups())
               {
                  QStringList l;
                  for(auto mem: i)
                      l.append(mem.c_str());

                    int pr = (100*int(comp->numberOfImagesFound()))/dbSize;
                    emit scanPercent(pr);
                    emit sendImgGroup(std::move(l));
                }
            }
           emit scanDone(true);
    }
};

class addImgThread : public QThread
{
    Q_OBJECT
public:
    addImgThread( MyStandardItemModel ** model )
        :m_model(model){}
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
//                if(first!=m_path_list.cbegin())
//                    child->setCheckState(Qt::Checked);
                group->appendRow(std::move(child));
                m_images++;
            }

            (*m_model)->appendRow(std::move(group));
            group->setCheckable(false);

      m_mutex.unlock();
    }
int m_images=0;
QStringList m_path_list;
MyStandardItemModel ** m_model;
QMutex m_mutex;
};
