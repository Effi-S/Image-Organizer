#pragma once
#ifndef MYTREEVIEW_H
#define MYTREEVIEW_H
#include <QTreeView>
#include "ImgOrganizer/COLOR.h"
#include <iostream>
#include "qevent.h"
#include "qmimedata.h"
#include <QStandardItem>


QT_BEGIN_NAMESPACE
class QDragEnterEvent;
class QDropEvent;
class QDragMoveEvent;
class QMouseEvent;
QT_END_NAMESPACE

class MyTreeView : public QTreeView{
    Q_OBJECT
public:
    MyTreeView(QWidget *parent = nullptr);
    bool CopyFile(const QString& sourceFile, const QString& destinationDir);
protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    //void mousePressEvent(QMouseEvent *event) override;


    void dropEvent(QDropEvent *event) override;


};


#endif // MYTREEVIEW_H
