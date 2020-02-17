#include "MyStandardItem.h"

QMimeData* MyStandardItemModel::mimeData(const QModelIndexList &indexes) const
{
    QMimeData* mimeData = QStandardItemModel::mimeData(indexes);

    // The raw data that will be placed in the mimeData.
    QByteArray mimeBytes;

    // Scope the data stream.
    {
         QDataStream ds(&mimeBytes, QIODevice::WriteOnly);

         // The first item encoded will be the number of pointers to expect.
         ds << quint32(indexes.size());

         // for each index gets a pointer to the standardItem, and write
         // into the datastream.
         for (int i = 0; i < indexes.size(); i++)
         {
              QStandardItem* ptrItem = itemFromIndex(indexes[i]);
              ds.writeRawData((const char*)&ptrItem, sizeof(QStandardItem*));
         }
    }

    // Add the encoded standard item pointers into the mimeData.
    mimeData->setData("Qt/QStandardItemArray", mimeBytes);

    return mimeData;
}

bool MyStandardItemModel::dropMimeData(const QMimeData *data, Qt::DropAction action,
                                     int row, int column, const QModelIndex &parent)
{
    // Get the QStandardItem target of the drop.
    QStandardItem* target = itemFromIndex(parent);


    // If the target is valid, accepts drops and the mimedata has QStandardItem pointers
    // go ahead with decode and insertion.  (Checking drop enabled pobably already
    // done by the framework before calling this function.)
    if ( NULL != target && target->isDropEnabled() && data->hasFormat("Qt/QStandardItemArray") )
    {
         // Fetch the encoded bytes, create a data stream for decoding,
         // and variables to store the output.
         QByteArray indexListBytes = data->data("Qt/QStandardItemArray");
         QDataStream ds(&indexListBytes, QIODevice::ReadOnly);
         quint32 numItems = 0;

         // Get the number of items, allocate memory to store pointers to
         // them and read the pointer data into that memory.
         ds >> numItems;
         int byteLen = numItems*sizeof(QStandardItem*);
         QStandardItem** stdItems = (QStandardItem**)malloc(byteLen);
         ds.readRawData((char*)stdItems, byteLen);

         // Add items to the target at a specific child index if requested,
         // using thier clone() function to create the items.
         for (int i = 0; i < numItems; i++)
         {
             if ( 0 <= row )
                  target->insertRow(row, stdItems[i]->clone());
              else
                  target->appendRow(stdItems[i]->clone());
         }

         // Free memory allocated to store item pointers.
         free(stdItems);

         return true;
    }

    return false;
}
