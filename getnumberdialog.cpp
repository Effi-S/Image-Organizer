#include "getnumberdialog.h"
#include "ui_getnumberdialog.h"

GetNumberDialog::GetNumberDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GetNumberDialog)
{
    ui->setupUi(this);
    connect(ui->buttonBox, &QDialogButtonBox::accepted , this,
            [&](){ emit valueChosen(ui->spinBox->value());});
}

GetNumberDialog::~GetNumberDialog()
{
    delete ui;
}
