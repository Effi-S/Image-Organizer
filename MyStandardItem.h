#ifndef MYSTANDARDITEM_H
#define MYSTANDARDITEM_H
#include <QStandardItem>
#include "qmimedata.h"
class QMimeData;

class MyStandardItemModel : public QStandardItemModel
{
public:
    /**
     * Uses the passed indexes, and encodes a list of QStandardItem pointers into
     * the mime data.
     */
    virtual QMimeData* mimeData(const QModelIndexList &indexes) const;

    /**
     * Decodes the mimedata, and uses the each QStandardItem::clone() implmentation
     * to place a copy at the requested position of the model.  If it is a move
     * operation Qt will remove the previous item.
     */
    virtual bool dropMimeData(const QMimeData *data, Qt::DropAction action,
                              int row, int column, const QModelIndex &parent);

};
#endif // MYSTANDARDITEM_H
