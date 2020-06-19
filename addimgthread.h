#ifndef ADDIMGTHREAD_H
#define ADDIMGTHREAD_H
#include <QObject>
#include "MyStandardItemModel.h"
#include <QRunnable>
#include <QThreadPool>

/***********************
 * Thread for adding images to a model
 *
 * Derrived from QObject for sending signals
 *
 * and from QRunnable for being run in own thread in Qt's Threadpool.
 *
 * gets pointer to a model and QStringlist
 *
 * creats image group from QStringlist and emits to the model a signal
 *
 * for adding this group.
 *
 *********************** */

class AddingImgThread :public QObject, public QRunnable
{
    Q_OBJECT
public:
    AddingImgThread(MyStandardItemModel * model);

signals:
    void addRow(QStandardItem *);  ///< signal sent to model for it to add a row
    void clear();
public slots:
    void addStringList(const std::vector<std::wstring>  &l);


private:
void run() override;
QStringList m_path_list;

};

#endif // ADDIMGTHREAD_H
