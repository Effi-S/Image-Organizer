#ifndef MYLISTWIDGET_H
#define MYLISTWIDGET_H
#include <QListWidget>
#include <iostream>
#include <QKeyEvent>

class MyListWidget : public QListWidget {
    Q_OBJECT
    protected:
    virtual void keyPressEvent(QKeyEvent* event) override
    {
        std::cout<<"+++++++++++++++!!!!!!!!"<<std::endl;
        if (event->key() == Qt::Key_Insert)
        {

        }
        else{
        QListWidget::keyPressEvent(event);
        }
    }
};

#endif // MYLISTWIDGET_H
