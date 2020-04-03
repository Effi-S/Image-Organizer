#pragma once
#ifndef MYTREEVIEW_H
#define MYTREEVIEW_H
#include <QTreeView>
#include "ImgOrganizer/COLOR.h"
#include <iostream>
#include "qevent.h"
#include "qmimedata.h"
#include <QStandardItem>
#include <QDrag>
#include "MyStandardItemModel.h"
#include <QLabel>
#include <QFileSystemModel>
#include <filesystem>
#include <QMenu>
#include <QAction>
#include <QCursor>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
class QDragEnterEvent;
class QDropEvent;
class QDragMoveEvent;
class QMouseEvent;

QT_END_NAMESPACE

/* *************************************
 * Class for viewing the filesystem
 *
 * This class derrives from QTreeView
 *
 * added options:
 *
 *  1) adding and removing folders in an added contex menu
 *
 *  2) drag and drop options
 *
 *  3) key events
 *
 * ************************************** */

class MyTreeView : public QTreeView{
    Q_OBJECT
public:
    MyTreeView(QWidget *parent = nullptr);
    bool CopyFile(const QString& sourceFile, const QString& destinationDir);
public slots:
    void ShowContextMenu(const QPoint &pos);
    ///virtual void startDrag(Qt::DropActions supportedActions) override{}
    void addFolder();
    void removeFolder();

protected:

    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;

    void keyPressEvent(QKeyEvent *event) override;
    void dropEvent(QDropEvent *event) override;


private:

};


#endif // MYTREEVIEW_H
