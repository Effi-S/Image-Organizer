#include "MyTreeView.h"
#include "MyStandardItem.h"
#include <QLabel>
#include <QFileSystemModel>
#include <filesystem>

MyTreeView::MyTreeView(QWidget *parent)
    :QTreeView(parent){
        setDragEnabled(true);
        setAcceptDrops(true);
        setDropIndicatorShown(true);
        setDefaultDropAction(Qt::CopyAction);
    }

bool MyTreeView::CopyFile(const QString& sourceFile, const QString& destinationDir)
{
    QFileInfo fileInfo(sourceFile);
    QString destinationFile = destinationDir + QDir::separator() + fileInfo.fileName();
    bool result = QFile::copy(sourceFile, destinationFile);
    return result;
}

void MyTreeView::dragEnterEvent(QDragEnterEvent *event)
{

    if (event->mimeData()->hasFormat("application/x-qabstractitemmodeldatalist")) {
            event->acceptProposedAction();

    } else {
        std::cout<<RED<<"Drag enter Event ignored"<<RESET<<std::endl;
        event->ignore();
    }
}

void MyTreeView::dragMoveEvent(QDragMoveEvent *event)
{
    std::cout<<RED<<"DragMove Event"<<RESET<<std::endl;
    if (event->mimeData()->hasFormat("application/x-qabstractitemmodeldatalist")
     || event->mimeData()->hasFormat("application/x-qstandarditemmodeldatalist")
     ||  event->mimeData()->hasFormat("Qt/QStandardItemArray")) {
        event->acceptProposedAction();
    } else {
        std::cout<<RED<<"DragMove Event ignored"<<RESET<<std::endl;
        event->ignore();
    }
}

void MyTreeView::dropEvent(QDropEvent *event)
{

     std::cout<<RED<<"Drop Event"<<RESET<<std::endl;
     if (event->mimeData()->hasFormat("application/x-qabstractitemmodeldatalist"))
          {
         // Fetch the encoded bytes, create a data stream for decoding,
         // and variables to store the output.
         QByteArray indexListBytes = event->mimeData()->data("Qt/QStandardItemArray");
         QDataStream ds(&indexListBytes, QIODevice::ReadOnly);
         quint32 numItems = 0;

         // Get the number of items, allocate memory to store pointers to
         // them and read the pointer data into that memory.
         ds >> numItems;
         int byteLen = numItems*sizeof(QStandardItem*);
         QStandardItem** stdItems = (QStandardItem**)malloc(byteLen);
         ds.readRawData((char*)stdItems, byteLen);

         auto model = static_cast<QFileSystemModel *>(this->model());
         QString target_path = model->filePath(currentIndex());

         // Add items to the target index if requested,
         for (int i = 0; i < numItems; i++)
            CopyFile(stdItems[i]->text(),target_path);
     }
}
