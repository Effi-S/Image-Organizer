#pragma once
#ifndef SCANTHREAD_H
#define SCANTHREAD_H

#endif // SCANTHREAD_H
#include <QThread>
#include "ImgOrganizer/ImgFinderBase.h"
#include "BitExactImgFinder.h"
#include "SimilarImgFinder.h"

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


        try {
           ImgScanner::scan(m_dir.toStdString());

           std::cout <<ORANGE<< "Time reading images scan took: " <<GREEN<< double(std::clock()) - start <<RESET<< std::endl;

        } catch (...) {
           std::cout<<"scan failed!"<<std::endl;
        }
        try {
            if(m_type == 0 )
            {
                ImgFinderBase * comp = new BitExactImgFinder;

                std::cout <<ORANGE<< "Time scan + ImgFinder took: " <<GREEN<< double(std::clock()) - start <<RESET<< std::endl;

                comp->makeGroups();
                for(auto i: comp->getGroups())
                    {
                        QStringList l;
                        for(auto mem: i)
                            l << mem.c_str();
                        emit sendImgGroup(l);
                     }
                }
                else
                {
                ImgFinderBase * comp  = new SimilarImgFinder;

                std::cout <<ORANGE<< "Time scan + ImgFinder took: " <<GREEN<< double(std::clock()) - start <<RESET<< std::endl;

                comp->makeGroups();
                int count = 0;
                for(auto i: comp->getGroups())
                    {                 
                        QStringList l;
                        for(auto mem: i)
                        {
                            l.append(mem.c_str());

                        }
                        //int pr = (100*comp->numOfImages())/int(ImgScanner::size());
                        //emit scanPercent(pr);
                        emit sendImgGroup(l);
                        emit scanStatus("Found: "+ QString::number(count) +"images.");
                     }
                }

        } catch (...) {
                std::cout<<"ImgFinder failed!"<<std::endl;
        }

        emit scanPercent(100);
        emit scanDone(true);

    }
};
