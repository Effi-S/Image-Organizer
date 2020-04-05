#ifndef MYSTANDARDITEM_H
#define MYSTANDARDITEM_H
#include <QStandardItem>
#include <QListWidget>
#include "qmimedata.h"
#include <QKeyEvent>
#include <iostream>

/* *************************************
 * Class for a model holding image Groups
 *
 * This class derrives from QStandardItemModel
 *
 * with the adition of implementing draging and dropping as well
 *
 * as adding rows properly.
 *
 * ************************************** */

class QMimeData;

class MyStandardItemModel : public QStandardItemModel
{
public:
    virtual QMimeData* mimeData(const QModelIndexList &indexes) const;
    virtual bool dropMimeData(const QMimeData *data, Qt::DropAction action,
                              int row, int column, const QModelIndex &parent);

public slots:
    void addRow(QStandardItem * item){ appendRow(item);}
protected:

};

#endif // MYSTANDARDITEM_H
