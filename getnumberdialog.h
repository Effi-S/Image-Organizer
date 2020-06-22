#ifndef GETNUMBERDIALOG_H
#define GETNUMBERDIALOG_H

#include <QDialog>
#include <QPushButton>

namespace Ui {
class GetNumberDialog;
}

class GetNumberDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GetNumberDialog(QWidget *parent = nullptr);
    ~GetNumberDialog();
signals:
    void valueChosen(int);
private:
    Ui::GetNumberDialog *ui;
};

#endif // GETNUMBERDIALOG_H
