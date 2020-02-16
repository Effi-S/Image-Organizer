#pragma once
#ifndef SCANTHREAD_H
#define SCANTHREAD_H

#endif // SCANTHREAD_H
#include <QThread>
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
