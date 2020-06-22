#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    //-- basic config
    ui->setupUi(this);
    ui->commandLinkButton->setEnabled(false);
    ui->toolBar->setVisible(false);

    ui->splitter->setSizes(QList<int>() << 200 << 65); //setting offset of splitter

    //-- init file model and view
    m_fileModel = std::make_unique<QFileSystemModel>(this);
    m_fileModel->setReadOnly(false);
    m_fileModel->setFilter(QDir::NoDotAndDotDot| QDir::AllDirs | QDir::AllEntries);
    m_fileModel->sort(QDir::DirsFirst | QDir::IgnoreCase | QDir::Name );
    m_fileModel->setRootPath(QString("~/"));

    ui->treeView->setModel(m_fileModel.get());
    QModelIndex index = m_fileModel->index(QString("~/"), 0);

    ui->treeView->setRootIndex(index);

    //-- init views
    initView(ui->exact_groupView, ui->exact_itemView);
    initView(ui->similar_groupView, ui->similar_itemView);
    initView(ui->advanced_view, ui->advanced_view);

    // -- connect scanHandler
    m_scanHandler.registerAlgo(0, ui->exact_groupView->model(),    [](){ return new BitExactImgFinder; } );
    m_scanHandler.registerAlgo(1, ui->similar_groupView->model(),  [](){ return new SimilarImgFinder; }   );
    m_scanHandler.registerAlgo(2, ui->advanced_view->model() ,     [](){ return new AdvancedImgSearch; } );

    connect(ui->tabWidget, &QTabWidget::currentChanged, &m_scanHandler, &ScanHandler::setAlgo);
    connect(this , &MainWindow::stopScan, &m_scanHandler, &ScanHandler::stop);
    connect(&m_scanHandler, &ScanHandler::setFormat, [&](QString s){
        std::string str = s.toStdString();
        std::string sub = "%v/%m";
        std::string::size_type i = str.find(sub);
        if (i != std::string::npos)
           str.erase(i, sub.length());
        ui->statusBar->showMessage(QString::fromStdString(str));
    });

    //-- connect advancedSearch
    connect(ui->pushButton_adv_num , &QPushButton::pressed  , this , &MainWindow::on_actionNumber_of_people_triggered);
    connect(ui->pushButton_adv_face , &QPushButton::pressed  , this , &MainWindow::on_actionFace_to_find_triggered);
    connect(ui->pushButton_adv_file , &QPushButton::pressed  , this , &MainWindow::on_actionFile_to_search_for_triggered);

}

//removes current object from view
void MainWindow::removeFunc(QObject *object, QListView *view)
{
    if(object != view || !view->isVisible())return;

    MyStandardItemModel * model =static_cast<MyStandardItemModel *>( view->model());
    QModelIndex index = view->currentIndex();
    QStandardItem * item = model->itemFromIndex(index);
    MyStandardItemModel mod;

    QMessageBox msgBox(this);
    msgBox.setInformativeText("Are you sure you want to delete: "+item->text()+"?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
    msgBox.setIcon(QMessageBox::Icon::Critical);
    msgBox.setDefaultButton(QMessageBox::Yes);
    int ret = msgBox.exec();
    if(ret == QMessageBox::Yes)
    {
        remove(item->text().toStdString().c_str());

        item->parent()->removeRow(index.row());
    }
}

void MainWindow::moveUp(QObject *object, QListView *view)
{
    if(object != view || !view->isVisible())return;

//    auto model =static_cast<MyStandardItemModel *>( view->model());
    QModelIndex index= view->currentIndex();
    auto row = index.row() - 1 ;
    if(row<0)return;
    view->setCurrentIndex(index.siblingAtRow(row));

}

void MainWindow::moveDown(QObject *object, QListView *view)
{
    if(object != view || !view->isVisible())return;

//    auto model =static_cast<MyStandardItemModel *>( view->model());
    QModelIndex index= view->currentIndex();
    auto row = index.row() + 1 ;

    if(row > view->model()->rowCount() -1 )return;

    view->setCurrentIndex(index.siblingAtRow(row));
}

void MainWindow::moveLeft(QObject *object, QListView *view, QListView *groups)
{
    if(object != view || !view->isVisible())return;
    auto par = view->currentIndex().parent();
    view->setVisible(false);
    groups->setCurrentIndex(par);
    view->setVisible(true);


}

void MainWindow::moveEnter(QObject *object, QListView *groups, QListView *items)
{
    if(object == groups)
    {
        moveRight(object, groups, items);
    }

    else if (object == items)
    {

        auto mod = static_cast<MyStandardItemModel *>(items->model());
        auto item = mod->itemFromIndex(items->currentIndex());
        std::cout <<" Opening: " << item->text().toStdString() <<"\n"<<std::endl;

        QDesktopServices::openUrl(QUrl::fromLocalFile(item->text()));
    }


}

void MainWindow::moveRight(QObject *object, QListView *view, QListView *items)
{
    if(object != view || !view->isVisible())return;
    auto index  = view->currentIndex();
    view->clicked(index);

}

bool MainWindow::eventFilter(QObject *object, QEvent *event)
{
    if ( event->type() == QEvent::KeyPress)
    {
        QKeyEvent *ke = static_cast<QKeyEvent *>(event);
        if (ke->key() == Qt::Key_Delete)
        {
            removeFunc(object, ui->similar_itemView);
            removeFunc(object, ui->exact_itemView);
        }
        else if (ke->key() == Qt::Key_Up) {
            moveUp(object, ui->similar_itemView);
            moveUp(object, ui->exact_itemView);
            moveUp(object, ui->similar_groupView);
            moveUp(object, ui->exact_groupView);
        }
        else if (ke->key() == Qt::Key_Down) {
            moveDown(object, ui->similar_itemView);
            moveDown(object, ui->exact_itemView);
            moveDown(object, ui->similar_groupView);
            moveDown(object, ui->exact_groupView);
        }
        else if (ke->key() == Qt::Key_Right){
            moveRight(object, ui->similar_groupView , ui->similar_itemView);
            moveRight(object, ui->exact_groupView   , ui->exact_itemView);
        }
        else if (ke->key() == Qt::Key_Left){
            moveLeft(object, ui->similar_itemView , ui->similar_groupView);
            moveLeft(object, ui->exact_itemView   , ui->exact_groupView  );
        }
        else if (ke->key() == 16777220){ // Enter key (Qt has a bug)
            moveEnter(object, ui->similar_groupView , ui->similar_itemView);
            moveEnter(object, ui->exact_groupView   , ui->exact_itemView);
//
        }
        return true;
    }

    return false;
}


MainWindow::~MainWindow()
{
}

void MainWindow::on_actionchange_file_triggered()
{
    ui->statusBar->showMessage("Changeing file");

    QString foldername = QFileDialog::getExistingDirectory(this , "Choose the Folder");

    if(!QFile(foldername).exists())
    {
        QMessageBox::warning(this, "Warning", "Cannot Open:"+foldername);
        ui->actionScan->setEnabled(true);
        ui->FolderButton->setText("Folder");
    }
    else
    {
        ui->FolderButton->setToolTip(foldername);
        ui->FolderButton->setText(foldername.split("/").last());
        ui->statusBar->showMessage("File" + foldername);
        m_scanHandler.setRoot(foldername);

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

void MainWindow::on_commandLinkButton_released(){
    on_actionScan_triggered();
}

void MainWindow::on_FolderButton_clicked(){
    on_actionchange_file_triggered();
}

void MainWindow::initView(QListView * view1, QListView * view2 )
{
    //exact column view  + model
    auto mod = new MyStandardItemModel;
    auto item = new QStandardItem("Groups");
    item->appendRow(new QStandardItem("Images"));
    mod->appendRow(item);
    for (auto view : {view1, view2})
    {
        view->setIconSize(QSize(64,64));
        view->setModel(mod);
        view->setDragEnabled(true);
        view->setAcceptDrops(true);
        view->setDropIndicatorShown(true);
        view->setDefaultDropAction(Qt::MoveAction);
        view->installEventFilter(this);
        view->setSelectionMode(QAbstractItemView::SelectionMode::ExtendedSelection);
        if(view1 == view2){
            mod->setStandalone();
            mod->clear();
            mod->appendRow(new QStandardItem("Images"));
            return;
        }
    }
    view2->setRootIndex(mod->index(0,0));
}

void MainWindow::on_actionScan_triggered()
{
    std::cout << "Main thread: "
              << QThread::currentThreadId() << std::endl;
//    auto set_enabled = [=](bool b){
//            ui->commandLinkButton->setEnabled(b);
//            ui->FolderButton->setEnabled(b);
//            ui->actionScan->setEnabled(b);
//            ui->tabWidget->setEnabled(b);
//         };

////    set_enabled(false);
    if(m_scanHandler.isRunning())
    {
        QMessageBox msgBox(this);
        msgBox.setInformativeText("Scan is already running:\nNew scan?");
        msgBox.setIcon(QMessageBox::Icon::Warning);
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Yes);
        int ret = msgBox.exec();
        if(ret == QMessageBox::Yes)
            emit stopScan();
            return;
    }
    QProgressBar * bar = new QProgressBar(this);
    bar->setRange(0, 0);
    ui->barLayout->addWidget(bar);
    connect(&m_scanHandler, &ScanHandler::finished,
            ui->barLayout , [&](){ui->barLayout->removeWidget(bar);});
    connect(&m_scanHandler, &ScanHandler::finished, bar , &QProgressBar::deleteLater);

    m_scanHandler.setBar(bar);
    m_scanHandler.start();

    ui->statusBar->showMessage("Scanning for images...");
}

void MainWindow::on_actionFace_to_find_triggered()
{
    auto dialog = new GetFaceDialog(this);
    dialog->exec();
    AdvancedImgSearch::setFaceToFind(L"3");
}

void MainWindow::on_actionFile_to_search_for_triggered()
{
    ui->statusBar->showMessage("Choose an Image File");
    QString imgPath = QFileDialog::getOpenFileName(this , "Choose the Folder");
    auto file = QFile(imgPath);
    QString imageFormat = QImageReader::imageFormat(imgPath);
    if(!file.exists() || imageFormat.size() == 0)
        QMessageBox::warning(this, "Warning", "Cannot Open:"+imgPath);
    else
        AdvancedImgSearch::setSearchFile(imgPath.toStdWString());
}

void MainWindow::on_actionNumber_of_people_triggered()
{
     auto dialog = new GetNumberDialog(this);
     connect(dialog, &GetNumberDialog::valueChosen, this, [](int val){ AdvancedImgSearch::setNumberOfPeople(val);});
     dialog->exec();

}
