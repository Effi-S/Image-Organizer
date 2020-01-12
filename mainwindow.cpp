#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QList>
#include <QScrollArea>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->commandLinkButton->setEnabled(false);
    ui->toolBar->setVisible(false);
    ui->progressBar->setVisible(false);
    ui->splitter->setSizes(QList<int>() << 200 << 80); //setting offset of splitter
    m_fileModel = std::make_unique<QFileSystemModel>(this);
    m_fileModel->setReadOnly(false);
    m_fileModel->sort(QDir::DirsFirst | QDir::IgnoreCase| QDir::Name );
    ui->treeView->setModel(m_fileModel.get());
//    QLabel *imageLabel1 = new QLabel;
//    QLabel *imageLabel2 = new QLabel;
//    QImage image1("C:\\Users\\effi\\Desktop\\temp\\temp\\collage_mixed.png");
//    QImage image2("C:\\Users\\effi\\Desktop\\temp\\temp\\collage_ordered.png");
//    imageLabel1->setPixmap(QPixmap::fromImage(image1));
//    imageLabel2->setPixmap(QPixmap::fromImage(image2));

//    ui->scrollArea_similar_tab->setBackgroundRole(QPalette::Midlight);
//    ui->label->setPixmap((QPixmap::fromImage(image1)));
//    ui->label_2->setPixmap((QPixmap::fromImage(image2)));

//    ui->scrollArea_exact_tab->setBackgroundRole(QPalette::Dark);



//   ui->exact_list->setDragEnabled(true);
//   ui->exact_list->setAcceptDrops(true);
//   ui->exact_list->setDropIndicatorShown(true);
//   ui->exact_list->setDefaultDropAction(Qt::MoveAction);


//    ui->exact_list->setStyleSheet
//       ("QListView { font-size: 20pt; font-weight: bold; }"
//        "QListView::item { background-color: #E74C3C; padding: 10%;"
//        "border: 1px solid #C0392B; }"
//        "QListView::item::hover { background-color: #C0392B }");




//    ui->exact_list->addAction(m_addAction.get());
//    ui->exact_list->addAction(m_removeAction.get());

    connect(m_addAction.get(), &QAction::triggered , this, &MainWindow::on_addImage);
    connect(m_removeAction.get(), &QAction::triggered, this, &MainWindow::on_removeImage);

//    ui->exact_list->model()->insertRow(ui->exact_list->model()->rowCount());
//    QModelIndex oIndex = ui->exact_list->model()->index(
//                   ui->exact_list->model()->rowCount() - 1, 0);

//      ui->exact_list->edit(oIndex);

//  ui->scrollArea_exact_tab->mode1()(imageLabel2);
//    ui->scrollArea_exact_tab->setWidget(imageLabel1);


}

MainWindow::~MainWindow()
{

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
    ui->FolderButton->setEnabled(false);
    ui->actionScan->setEnabled(false);
    ui->progressBar->setVisible(true);
    ui->statusBar->showMessage("Scanning " + m_currDir + "...");

    //sending to thread
    m_scanThread = std::make_unique<ScanThread>(m_currDir);
    connect(m_scanThread.get(), &ScanThread::resultReady, this, &MainWindow::windowHandle);
    connect(m_scanThread.get() , &ScanThread::scanDone , ui->commandLinkButton, &QCommandLinkButton::setEnabled);
    connect(m_scanThread.get() , &ScanThread::scanDone , ui->FolderButton, &QPushButton::setEnabled);
    connect(m_scanThread.get(), &ScanThread::scanStatus, ui->statusBar, &QStatusBar::showMessage );
    connect(m_scanThread.get(), &ScanThread::scanPercent, ui->progressBar, &QProgressBar::setValue );
    connect(m_scanThread.get(), &ScanThread::scanDone, ui->progressBar,[=](){ ui->progressBar->setVisible(false); });
    m_scanThread->start();
    //


}

void MainWindow::on_commandLinkButton_released(){
    on_actionScan_triggered();


}

void MainWindow::on_FolderButton_clicked(){

    on_actionchange_file_triggered();

}

void MainWindow::on_addImage()
{
//    ui->exact_list->model()->insertRow(ui->exact_list->model()->rowCount());
//        QModelIndex oIndex = ui->exact_list->model()->index(
//                    ui->exact_list->model()->rowCount() - 1, 0);

//        ui->exact_list->edit(oIndex);
}

void MainWindow::on_removeImage()
{

//    QModelIndex oIndex = ui->exact_list->currentIndex();
//        ui->exact_list->model()->removeRow(oIndex.row());
}

