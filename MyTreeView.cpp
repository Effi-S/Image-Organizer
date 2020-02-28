#include "MyTreeView.h"
#include "MyStandardItem.h"
#include <QLabel>
#include <QFileSystemModel>
#include <filesystem>
#include <QMenu>
#include <QAction>
#include <QCursor>

MyTreeView::MyTreeView(QWidget *parent)
    :QTreeView(parent){
        setDragEnabled(true);
        setAcceptDrops(true);
        setDropIndicatorShown(true);
        setDefaultDropAction(Qt::CopyAction);
        setSelectionMode(QAbstractItemView::ExtendedSelection);

        this->setContextMenuPolicy(Qt::CustomContextMenu);

        connect(this, SIGNAL(customContextMenuRequested(const QPoint &)),
                this, SLOT(ShowContextMenu(const QPoint &)));
    }

bool MyTreeView::CopyFile(const QString& sourceFile, const QString& destinationDir)
{
    QFileInfo fileInfo(sourceFile);
    QString destinationFile = destinationDir + QDir::separator() + fileInfo.fileName();
    bool result = QFile::copy(sourceFile, destinationFile);
    return result;
}

void MyTreeView::ShowContextMenu(const QPoint &pos)
{
   QMenu contextMenu(tr("Context menu"), this);

   QAction action1("New Folder", this);
   QAction action2("Remove Folder", this);
   connect(&action1, SIGNAL(triggered()), this, SLOT(addFolder()));
   connect(&action2, SIGNAL(triggered()), this, SLOT(removeFolder()));
   contextMenu.addAction(&action1);
   contextMenu.addAction(&action2);

   contextMenu.exec(mapToGlobal(pos));
}

void MyTreeView::addFolder()
{
    QModelIndex index = this->currentIndex();
    QFileSystemModel * data = static_cast<QFileSystemModel *>(this ->model());
    if(data)
    if(data->isDir(index))
    data->mkdir(index, "New Folder");
    else
    {
        index = index.parent();
        if(data->isDir(index))
        data->mkdir(index, "New Folder");
    }
}

void MyTreeView::removeFolder()
{
    QModelIndex index = this->currentIndex();
    QFileSystemModel * data = static_cast<QFileSystemModel *>(this ->model());

    if(!data )return;

    if(data->isDir(index))
        data->rmdir(index);

//    std::cout<<RED<<data->filePath(index).toStdString().c_str()<<RESET<<std::endl;

}

void MyTreeView::dragEnterEvent(QDragEnterEvent *event)
{

     if (event->mimeData()->hasFormat("application/x-qabstractitemmodeldatalist")) {
            event->acceptProposedAction();

    } else if (event->mimeData()->hasFormat("text/uri-list")) {
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
    } else if(event->mimeData()->hasUrls()){
        event->acceptProposedAction();
    }else {
        std::cout<<RED<<"DragMove Event ignored"<<RESET<<std::endl;
        event->ignore();
    }

    setCurrentIndex(indexAt(mapFromGlobal(QCursor::pos())));
}




void MyTreeView::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key::Key_Delete )
    {
        QModelIndex index = this->currentIndex();
        QFileSystemModel * data = static_cast<QFileSystemModel *>(this ->model());
        if(data)
        {
            if(data->isDir(index))removeFolder();
            else
            remove(data->filePath(index).toStdString().c_str());
        }

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
         {
             QString source_path = stdItems[i]->text();
             CopyFile(source_path,target_path);
         }

     }
     else if (event->mimeData()->hasUrls())
        {

         QFileSystemModel * model = static_cast<QFileSystemModel *>(this ->model());

         if(!model )return;

         QString target_path = model->filePath(currentIndex());
         QList<QUrl> urlList = event->mimeData()->urls();

          // move the paths of the files
          for (int i = 0; i < urlList.size() ; ++i)
          {
              QString source_path = urlList.at(i).path();
              source_path.remove(0, 1);  //removing slash from begining of path
              CopyFile(source_path ,target_path);

          }
     }
}
