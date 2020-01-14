#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QMessageBox>
#include <QtGui>
#include <QtCore>
#include <QFileSystemModel>


#include <opencv2/opencv.hpp>
#include <ImgOrganizer/BitExactImgFinder.h>
#include <ImgOrganizer/SimilarImgFinder.h>
#include <ImgOrganizer/ImgScanner.h>
#include "COLOR.h"
#include <QColumnView>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


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
           emit scanPercent(10);
           ImgScanner::scan(m_dir.toStdWString());

           std::cout <<ORANGE<< "Time reading images scan took: " <<GREEN<< double(std::clock()) - start <<RESET<< std::endl;

        } catch (...) {
           std::cout<<"scan failed!"<<std::endl;
        }
        try {
            if(m_type == 0 )
            {
                BitExactImgFinder comp;

                std::cout <<ORANGE<< "Time scan + ImgFinder took: " <<GREEN<< double(std::clock()) - start <<RESET<< std::endl;

                comp.show();
                for(auto i: comp.getGroups())
                    {
                        QStringList l;
                        for(auto mem: i)
                            l.append(mem.c_str());
                        emit sendImgGroup(l);
                     }
                }
                else
                {
                    std::cout<<"hererererererere\n";
                }

        } catch (...) {
                std::cout<<"ImgFinder failed!"<<std::endl;
        }

        emit scanPercent(100);
        emit scanDone(true);        
        emit scanStatus("Done scanning:" + m_dir);
    }
};


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionchange_file_triggered();

    void on_actionundo_triggered();

    void on_actionCopy_triggered();

    void on_actionPaste_triggered();

    void on_actionCut_triggered();

    void on_actionUndo_triggered();

    void on_actionToggle_Toolbar_triggered();

    void on_actionsave_changes_triggered();

    void on_actionScan_triggered();

    void on_commandLinkButton_released();

    void on_FolderButton_clicked();

public slots:
    void on_addImageGroup(QStringList);
    void on_removeImage();


private:    
    QString m_currDir ="";
    std::unique_ptr<Ui::MainWindow> ui;
    std::unique_ptr<ScanThread> m_scanThread;

    std::unique_ptr<QFileSystemModel> m_fileModel =nullptr;

    int m_cur_job = 0;
    QStandardItemModel m_exact_model;

};
#endif // MAINWINDOW_H
