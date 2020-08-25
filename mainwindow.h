

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QMessageBox>
#include <QtGui>
#include <QtCore>
#include <QTreeView>
#include <QFileSystemModel>
#include <QColumnView>
#include <QList>
#include <QListView>
#include <opencv2/opencv.hpp>
#include "ImgOrganizer/BitExactImgFinder.h"
#include "ImgOrganizer/SimilarImgFinder.h"
#include "ImgOrganizer/ImgFileScanner.h"
#include "ImgOrganizer/advancedimgsearch.h"

#include "ImgOrganizer/COLOR.h"
#include "MyStandardItemModel.h"
#include <QGraphicsView>
#include <QProgressBar>
#include "scanhandler.h"
#include <QStandardItem>
#include "getnumberdialog.h"
#include "getfacedialog.h"
#include "settingsdialog.h"

/***********************
 * Main Window of the application
 *
 * This Class holds all of the logic behind the main window
 * of the application.
 *
 *
 * ********************** */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    bool eventFilter(QObject *object, QEvent *event);

    ~MainWindow();
signals:
    void stopScan();
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

    void on_actionFace_to_find_triggered();

    void on_actionFile_to_search_for_triggered();

    void on_actionNumber_of_people_triggered();

    void on_SettingsButton_released();

private:

    Ui::MainWindow * ui;

    std::unique_ptr<QFileSystemModel> m_fileModel =nullptr;

    void initView(QListView * view1, QListView * view2);

    ScanHandler m_scanHandler;

    // user movement functions
    void moveRight(QObject *object, QListView *view, QListView *items);
    void moveUp(QObject *object, QListView *view);
    void moveDown(QObject *object, QListView *view);
    void moveLeft(QObject *object, QListView *view, QListView *groups);
    void moveEnter(QObject *object, QListView *groups, QListView *items);
    void removeFunc(QObject *object, QListView *view);

};


#endif
