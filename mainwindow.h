#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QMessageBox>
#include <QtGui>
#include <QtCore>


#include <opencv2/opencv.hpp>
#include <ImgOrganizer/BitExactImgFinder.h>
#include <ImgOrganizer/SimilarImgFinder.h>
#include <ImgOrganizer/ImgScanner.h>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class ScanThread : public QThread
{
public:
    ScanThread(QString& dir):m_dir(dir){}

private:
    QString m_dir;
    Q_OBJECT
    void run() override {

        QString result;
        try {
            ImgScanner::scan(m_dir.toStdWString());
        } catch (...) {
           std::cout<<"scan failed!"<<std::endl;
        }
        try {
            BitExactImgFinder comp;

            comp.show();
        } catch (...) {
                std::cout<<"BitExact failed!"<<std::endl;
        }

        emit resultReady(result);
    }
signals:
    void resultReady(const QString &s);
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


private:
    Ui::MainWindow *ui;
    QString m_currDir ="";
    ScanThread *m_scanThread;


};
#endif // MAINWINDOW_H
