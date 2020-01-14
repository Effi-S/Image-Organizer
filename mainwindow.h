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
#include "ImgOrganizer/ScanThread.h"
#include "COLOR.h"
#include <QColumnView>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

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

    int m_cur_model= 0;
    QStandardItemModel m_exact_model;
    QStandardItemModel m_similar_model;

};
#endif // MAINWINDOW_H
