#ifndef MYSTANDARDITEM_H
#define MYSTANDARDITEM_H
#include <QStandardItem>
#include <QListWidget>
#include "qmimedata.h"
#include <QKeyEvent>
#include <iostream>
class QMimeData;

class MyStandardItemModel : public QStandardItemModel
{
public:

    virtual QMimeData* mimeData(const QModelIndexList &indexes) const;
    virtual bool dropMimeData(const QMimeData *data, Qt::DropAction action,
                              int row, int column, const QModelIndex &parent);
};

#endif // MYSTANDARDITEM_H
