#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QScrollArea>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->commandLinkButton->setEnabled(false);
    ui->toolBar->setVisible(false);
    ui->progressBar->setVisible(false);

    QLabel *imageLabel = new QLabel;
    QImage image("C:\\Users\\effi\\Desktop\\temp\\Player_01.png");
    imageLabel->setPixmap(QPixmap::fromImage(image));

    ui->scrollArea_exact_tab->setBackgroundRole(QPalette::Dark);
    ui->scrollArea_exact_tab->setWidget(imageLabel);


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
        m_currDir =foldername;
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
    ui->commandLinkButton->setEnabled(true);
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
    static bool state = false;
    state = !state;
    ui->statusBar->showMessage("toggled toolbar");
    ui->toolBar->setVisible(state);
}

void MainWindow::on_actionsave_changes_triggered()
{
    ui->statusBar->showMessage("Save Changes");
}

void MainWindow::on_actionScan_triggered()
{
    ui->commandLinkButton->setEnabled(false);
    ui->progressBar->setVisible(true);
    //scanning for images
    ui->statusBar->showMessage("Scanning " + m_currDir + "...");

    ui->actionScan->setEnabled(false);

    //sending to thread
    m_scanThread = std::make_unique<ScanThread>(m_currDir);
    connect(m_scanThread.get(), &ScanThread::resultReady, this, &MainWindow::windowHandle);
    //connect(m_scanThread.get(), &ScanThread::finished, m_scanThread, &QObject::deleteLater);
    connect(m_scanThread.get() , &ScanThread::scanDone , ui->commandLinkButton, &QCommandLinkButton::setEnabled);
    //connect(m_scanThread.get(), &ScanThread::scanDone, ui->statusBar, &QStatusBar::showMessage );
    m_scanThread->start();
    ui->statusBar->showMessage( "Done Scanning:" + m_currDir);

    //
    ui->progressBar->setValue(100);
    ui->progressBar->reset();
    ui->progressBar->setVisible(false);


}

void MainWindow::on_commandLinkButton_released(){
    on_actionScan_triggered();


}

void MainWindow::on_FolderButton_clicked(){

    on_actionchange_file_triggered();

}

