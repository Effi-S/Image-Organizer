#include "MyTreeView.h"

MyTreeView::MyTreeView(QWidget *parent)
    :QTreeView(parent){
        setDragEnabled(true);
        setAcceptDrops(true);
        setDropIndicatorShown(true);
        setDefaultDropAction(Qt::CopyAction);
    }

void MyTreeView::dragEnterEvent(QDragEnterEvent *event)
{
    std::cout<<RED<<"Drag enter Event"<<RESET<<std::endl;

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
//    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
//        if (event->source() == this) {
//            event->setDropAction(Qt::MoveAction);
//            event->accept();
//        } else {
//            event->acceptProposedAction();
//        }
//    } else {
//        event->ignore();
//    }
}

void MyTreeView::dropEvent(QDropEvent *event)
{
     std::cout<<RED<<"Drop Event"<<RESET<<std::endl;
    if (event->mimeData()->hasFormat("application/x-qabstractitemmodeldatalist"))
    {
        QByteArray itemData = event->mimeData()->data("application/x-qabstractitemmodeldatalist");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

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
}

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

