#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include <QMessageBox>
#include "addimgthread.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    ui->spinBox_2->setValue(int(AddingImgThread::getGroupSizeLimit()));
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::on_radioButton_2_pressed()
{
    QMessageBox msgBox(this);
    msgBox.setInformativeText("Sorry,\nThis option is not ready yet.");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setIcon(QMessageBox::Icon::Information);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();

}

void SettingsDialog::on_buttonBox_accepted()
{
    AddingImgThread::setGroupSizeLimit(ui->spinBox_2->value());
}
