#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "COLOR.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionchange_file_triggered()
{
    ui->statusBar->showMessage("Changeing file");

    QString foldername = QFileDialog::getExistingDirectory(this , "Choose the Folder");
    QFile dir(foldername);
    m_currDir = foldername;

    if(!dir.exists())
    {
        QMessageBox::warning(this, "Warning", "Cannot Open file");
        ui->actionScan->setEnabled(true);
        ui->FolderButton->setText("Folder");
    }
    else
    {
        ui->FolderButton->setToolTip(m_currDir);
        ui->FolderButton->setText(m_currDir.split("/").last());
        ui->statusBar->showMessage("File" + m_currDir);
    }
}

void MainWindow::on_actionundo_triggered()
{
    ui->statusBar->showMessage("undo");
    
}
void MainWindow::on_actionCopy_triggered()
{
    ui->statusBar->showMessage("Copy");
}

void MainWindow::on_actionPaste_triggered()
{
    ui->statusBar->showMessage("Paste");
}

void MainWindow::on_actionCut_triggered()
{
    ui->statusBar->showMessage("Cut");
}

void MainWindow::on_actionUndo_triggered()
{
    on_actionundo_triggered();
}

void MainWindow::on_actionToggle_Toolbar_triggered()
{
    ui->statusBar->showMessage("Toggle Toolbar");
}

void MainWindow::on_actionsave_changes_triggered()
{
    ui->statusBar->showMessage("Save Changes");
}

void MainWindow::on_actionScan_triggered()
{
    //scanning for images
    //TODO: place in thread
    ui->statusBar->showMessage("Scanning " + m_currDir + "...");

    ui->actionScan->setEnabled(false);

    ImgScanner::scan(m_currDir.toStdWString());

    std::clock_t start(std::clock());

    std::cout <<ORANGE<< "Time reading images scan took: " <<GREEN<< double(std::clock()) - start << std::endl;

    start = std::clock_t(std::clock());

    BitExactImgFinder comp;

    std::cout <<ORANGE<<"Time BitExactImgFinder took: " <<GREEN<< double(std::clock()) - start <<REG<<std::endl;

    ui->statusBar->showMessage( "Done Scanning");

    ui->actionScan->setEnabled(false);

    comp.show();

}

void MainWindow::on_commandLinkButton_released(){
    on_actionScan_triggered();


}

void MainWindow::on_FolderButton_clicked(){
    on_actionchange_file_triggered();

}
