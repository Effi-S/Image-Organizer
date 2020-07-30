#ifndef MYSTANDARDITEM_H
#define MYSTANDARDITEM_H
#include <QStandardItem>
#include <QListWidget>
#include "qmimedata.h"
#include <QKeyEvent>
#include <iostream>
#include <QSortFilterProxyModel>

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
    void mouseDoubleClickEvent( QMouseEvent * e )
    {
        std::cout << "herererere\n" <<std::endl;
    }

    virtual bool dropMimeData(const QMimeData *data, Qt::DropAction action,
                              int row, int column, const QModelIndex &parent);
    void setStandalone();
public slots:
    void addRow(QStandardItem * item);
    void clear();
protected:
private:
bool m_standalone=false;

};


#endif // MYSTANDARDITEM_H
