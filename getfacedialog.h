#ifndef GETFACEDIALOG_H
#define GETFACEDIALOG_H

#include <QDialog>
#include <QRadioButton>
#include <QCheckBox>

namespace Ui {
class GetFaceDialog;
}

class GetFaceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GetFaceDialog(QWidget *parent = nullptr);
    ~GetFaceDialog();

private:
    Ui::GetFaceDialog *ui;
    std::vector<QRadioButton *> m_buttons;
};

#endif // GETFACEDIALOG_H
