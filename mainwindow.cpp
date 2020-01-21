#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->commandLinkButton->setEnabled(false);
    ui->toolBar->setVisible(false);
    ui->progressBar->setVisible(false);
    ui->splitter->setSizes(QList<int>() << 200 << 65); //setting offset of splitter


    //file model + tree view
    QString sPath = "~/";
    m_fileModel = std::make_unique<QFileSystemModel>(this);
    m_fileModel->setReadOnly(false);
    m_fileModel->setFilter( QDir::AllDirs);
    m_fileModel->sort(QDir::DirsFirst | QDir::IgnoreCase | QDir::NoDotAndDotDot|  QDir::Name );
    m_fileModel->setRootPath(sPath);

    ui->treeView->setModel(m_fileModel.get());
    QModelIndex index = m_fileModel->index(sPath, 0);
    ui->treeView->setRootIndex(index);;



    initView(ui->exact_groupView, "Groups");
    initView(ui->exact_itemView, "Images");
    initView(ui->similar_groupView, "Groups");
    initView(ui->simlar_itemView, "Images");

    on_tabWidget_currentChanged(ui->tabWidget->currentIndex());//MUST be after models creation to prevent null on startup

}

MainWindow::~MainWindow()
{
//    const QMimeData *clip = QApplication::clipboard()->mimeData();
//    if (clip->)
//    {

//    }


}

//const QClipboard *clipboard = QApplication::clipboard();
//   const QMimeData *mimeData = clipboard->mimeData();

//   if (mimeData->hasImage()) {
//       setPixmap(qvariant_cast<QPixmap>(mimeData->imageData()));
//   } else if (mimeData->hasHtml()) {
//       setText(mimeData->html());
//       setTextFormat(Qt::RichText);
//   } else if (mimeData->hasText()) {
//       setText(mimeData->text());
//       setTextFormat(Qt::PlainText);
//   } else {
//       setText(tr("Cannot display data"));
//   }


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

    //disabaling buttons
    ui->commandLinkButton->setEnabled(false);
    ui->FolderButton->setEnabled(false);
    ui->actionScan->setEnabled(false);
    ui->progressBar->setVisible(true);
    ui->tabWidget->setEnabled(false);



    //making thread
    m_scanThread = std::make_unique<ScanThread>(m_currDir, ui->tabWidget->currentIndex());


    m_curr_model->clear();


    //connecting thread
    connect(m_scanThread.get(), &ScanThread::resultReady, this, &MainWindow::windowHandle);
    connect(m_scanThread.get(), &ScanThread::scanDone , ui->commandLinkButton, &QCommandLinkButton::setEnabled);
    connect(m_scanThread.get(), &ScanThread::scanDone , ui->FolderButton, &QPushButton::setEnabled);
    connect(m_scanThread.get(), &ScanThread::scanStatus, ui->statusBar, &QStatusBar::showMessage );
    connect(m_scanThread.get(), &ScanThread::scanPercent, ui->progressBar, &QProgressBar::setValue );
    connect(m_scanThread.get(), &ScanThread::scanDone, ui->progressBar,[=](){ ui->progressBar->setVisible(false); });
    connect(m_scanThread.get(), &ScanThread::sendImgGroup, this, &MainWindow::on_addImageGroup);

    //sending to thread
    ui->statusBar->showMessage("Scanning " + m_currDir + "...");
    m_scanThread->start();
    ui->tabWidget->setEnabled(true);

}

void MainWindow::on_commandLinkButton_released(){
    on_actionScan_triggered();


}

void MainWindow::on_FolderButton_clicked(){

    on_actionchange_file_triggered();

}

void MainWindow::on_tabWidget_currentChanged(int i)
{
    switch(i){
    case 0:m_curr_model = static_cast<MyStandardItemModel *>(ui->exact_groupView->model());break;
    case 1:m_curr_model = static_cast<MyStandardItemModel *>(ui->similar_groupView->model());break;
    }

    switch(i)
    {
    case 0:m_curr_match_model = static_cast<MyStandardItemModel *>(ui->exact_itemView->model());break;
    case 1:m_curr_match_model = static_cast<MyStandardItemModel *>(ui->simlar_itemView->model());break;
    }
}

void MainWindow::on_exact_groupView_clicked(QModelIndex index)
{
    QStandardItem * group = m_curr_model->item(index.row());
    m_curr_match_model->clear();

    for(int i=0 ;i< group->rowCount(); ++i)
    {
        auto temp =  new QStandardItem(group->child(i)->icon(), group->child(i)->text() );

        temp->setDragEnabled(true);
        temp->setDragEnabled(true);
        m_curr_match_model->appendRow(temp);
    }
}

void MainWindow::on_similar_groupView_clicked(QModelIndex index)
{
    on_exact_groupView_clicked(index);
}

void MainWindow::on_addImageGroup(QStringList path_list)
{

    auto first = path_list.cbegin();

    QStandardItem *group = new QStandardItem(QIcon(*first),
                                             QVariant(path_list.length()).toString());

    group->setCheckable(true);

    for(;first != path_list.cend(); ++first)
    {
        QStandardItem *child = new QStandardItem(QIcon(*first) ,*first);

        child->setToolTip(*first);
        child->setCheckable(true);
        child->setDragEnabled(true);
        child->setDropEnabled(true);
        if(first!=path_list.cbegin())
            child->setCheckState(Qt::Checked);
        group->appendRow(child);
    }
    m_curr_model->appendRow(group);

}

void MainWindow::on_removeImage()
{

//    QModelIndex oIndex = ui->exact_list->currentIndex();
    //        ui->exact_list->model()->removeRow(oIndex.row());
}

void MainWindow::initView(QListView * view, QString header)
{
    //exact clumn view  + model
    view->setIconSize(QSize(64,64));
    auto mod = new MyStandardItemModel;
    mod->appendRow(new QStandardItem(header));
    view->setModel(mod);
    view->setDragEnabled(true);
    view->setDragEnabled(true);
    view->setAcceptDrops(true);
    view->setDropIndicatorShown(true);
    view->setDefaultDropAction(Qt::CopyAction);

}

