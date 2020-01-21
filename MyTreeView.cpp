#include "MyTreeView.h"
#include "MyStandardItem.h"
#include <QLabel>

MyTreeView::MyTreeView(QWidget *parent)
    :QTreeView(parent){
        setDragEnabled(true);
        setAcceptDrops(true);
        setDropIndicatorShown(true);
        setDefaultDropAction(Qt::CopyAction);
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
    std::cout<<RED<<"Drag enter Event"<<RESET<<std::endl;

//    std::cout<<RED<<event->mimeData()->hasHtml()<<RESET<<std::endl;
//    std::cout<<RED<<event->mimeData()->hasText()<<RESET<<std::endl;
//    std::cout<<RED<<event->mimeData()->hasUrls()<<RESET<<std::endl;
//    std::cout<<RED<<event->mimeData()->hasColor()<<RESET<<std::endl;
//    std::cout<<RED<<event->mimeData()->hasImage()<<RESET<<std::endl;
//    for (auto x: event->mimeData()->formats())
//    std::cout<<RED<<x.toStdString()<<RESET<<std::endl;

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

         // Add items to the target at a specific child index if requested,
         // using thier clone() function to create the items.
         for (int i = 0; i < numItems; i++)
         {
             std::cout<<ORANGE<<"ITEM:"<<stdItems[i]->text().toStdString() <<RESET <<std::endl;
//             if ( 0 <= row )
//                  target->insertRow(row, stdItems[i]->clone());
//              else
//                  target->appendRow(stdItems[i]->clone());
         }

         // Free memory allocated to store item pointers.
         free(stdItems);












//         QByteArray bytes_arr = event->mimeData()->data("application/x-qabstractitemmodeldatalist");
//         //QDataStream dataStream(&bytes_arr, QIODevice::ReadWrite);
//         for(auto x: bytes_arr)
//         std::cout<<ORANGE<<x<<RESET<<" ";
//         std::cout<<std::endl;


//         QPixmap pixmap;
//         QPoint offset;
//         dataStream >> pixmap >> offset;

//         Q *newIcon = new QLabel(this);
//         newIcon->setPixmap(pixmap);
//         newIcon->move(event->pos() - offset);
//         newIcon->show();
//         newIcon->setAttribute(Qt::WA_DeleteOnClose);


     }

     else
     {
         std::cout<<RED<<"Drop Event ignored"<<RESET<<std::endl;
         event->ignore();
     }
}

//        QByteArray itemData = event->mimeData()->data("application/x-qabstractitemmodeldatalist");
//        QDataStream dataStream(&itemData, QIODevice::ReadOnly);
//        std::cout<<ORANGE<<"FILE: "<<item_model.icicon().name().toStdString()<<"\n"<<item.text().toStdString()<<RESET<<std::endl;


//        QPixmap pixmap;
//        QPoint offset;
//        dataStream >> pixmap >> offset;

//        QLabel *newIcon = new QLabel(this);
//        newIcon->setPixmap(pixmap);
//        newIcon->move(event->pos() - offset);
//        newIcon->show();
//        newIcon->setAttribute(Qt::WA_DeleteOnClose);

//        if (event->source() == this) {
//            event->setDropAction(Qt::MoveAction);
//            event->accept();
//        }
//        else
//            event->acceptProposedAction();

//    }
//    else {
//        event->ignore();
//    }

//! [1]
//void MyTreeView::mousePressEvent(QMouseEvent *event)
//{
//    QLabel *child = static_cast<QLabel*>(childAt(event->pos()));
//    if (!child)
//        return;

//    QPixmap pixmap = *child->pixmap();

//    QByteArray itemData;
//    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
//    dataStream << pixmap << QPoint(event->pos() - child->pos());
////! [1]

////! [2]
//    QMimeData *mimeData = new QMimeData;
//    mimeData->setData("application/x-dnditemdata", itemData);
////! [2]

////! [3]
//    QDrag *drag = new QDrag(this);
//    drag->setMimeData(mimeData);
//    drag->setPixmap(pixmap);
//    drag->setHotSpot(event->pos() - child->pos());
////! [3]

//    QPixmap tempPixmap = pixmap;
//    QPainter painter;
//    painter.begin(&tempPixmap);
//    painter.fillRect(pixmap.rect(), QColor(127, 127, 127, 127));
//    painter.end();

//    child->setPixmap(tempPixmap);

//    if (drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) == Qt::MoveAction) {
//        child->close();
//    } else {
//        child->show();
//        child->setPixmap(pixmap);
//    }
//}

