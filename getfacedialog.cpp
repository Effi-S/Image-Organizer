#include "getfacedialog.h"
#include "ui_getfacedialog.h"

GetFaceDialog::GetFaceDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GetFaceDialog)
{
    ui->setupUi(this);
    for(int i=0; i <25 ; i++)
    {
        auto radioButton = new QRadioButton(QString().setNum(i), this);

        ui->radioLayout->addWidget(radioButton);
        m_buttons.push_back(radioButton);
    }

    for(int i=0; i <25 ; i++)
    {
        auto radioButton = new QCheckBox(this);
        radioButton->setText(QString().setNum(i));
        ui->radioLayout->addWidget(radioButton);

    }
}

GetFaceDialog::~GetFaceDialog()
{
    delete ui;
}
