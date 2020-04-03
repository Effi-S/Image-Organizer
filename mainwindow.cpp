#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStandardItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->commandLinkButton->setEnabled(false);
    ui->toolBar->setVisible(false);
    //ui->progressBar->setVisible(false);
    ui->progressBar_2->setVisible(false);
    ui->progressBar_3->setVisible(false);
    ui->splitter->setSizes(QList<int>() << 200 << 65); //setting offset of splitter

    //file model + tree view
    m_fileModel = std::make_unique<QFileSystemModel>(this);
    m_fileModel->setReadOnly(false);
    m_fileModel->setFilter(QDir::NoDotAndDotDot| QDir::AllDirs | QDir::AllEntries);
    m_fileModel->sort(QDir::DirsFirst | QDir::IgnoreCase | QDir::Name );
    m_fileModel->setRootPath(QString("~/"));

    ui->treeView->setModel(m_fileModel.get());
    QModelIndex index = m_fileModel->index(QString("~/"), 0);

    ui->treeView->setRootIndex(index);
    initView(ui->exact_groupView, ui->exact_itemView);
    initView(ui->similar_groupView, ui->similar_itemView);

    m_scanController.addModel(ui->exact_groupView->model(), ScanController::algoType::exact, ui->progressBar_2);
    m_scanController.addModel(ui->similar_groupView->model(), ScanController::algoType::similar, ui->progressBar_3);

}

//removes current object from view
void MainWindow::removeFunc(QObject *object, QListView *view)
{
    if(object != view || !view->isVisible())return;

    MyStandardItemModel * model =static_cast<MyStandardItemModel *>( view->model());
    QModelIndex index = view->currentIndex();
    QStandardItem * item = model->itemFromIndex(index);
    MyStandardItemModel mod;

    QMessageBox msgBox;
    msgBox.setInformativeText("Are you sure you want to delete: "+item->text()+"?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
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

    auto model =static_cast<MyStandardItemModel *>( view->model());
    QModelIndex index= view->currentIndex();
    auto row = index.row() - 1 ;
    if(row<0)return;
    view->setCurrentIndex(index.siblingAtRow(row));

}

void MainWindow::moveDown(QObject *object, QListView *view)
{
    if(object != view || !view->isVisible())return;

    auto model =static_cast<MyStandardItemModel *>( view->model());
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
        std::cout<<"here1"<<std::endl;
        moveRight(object, groups, items);
    }

    else if (object == items)
    {
        std::cout<<"here2"<<std::endl;
        auto mod = static_cast<MyStandardItemModel *>(items->model());
        auto item = mod->itemFromIndex(items->currentIndex());
        std::cout <<" Opening: " << item->text().toStdString() <<"\n"<<std::endl;

        QDesktopServices::openUrl(QUrl::fromLocalFile(item->text()));
    }

    std::cout<<"here3"<<std::endl;
}

void MainWindow::moveRight(QObject *object, QListView *view, QListView *items)
{
    if(object != view || !view->isVisible())return;
    auto index  = view->currentIndex();
    view->clicked(index);

}

bool MainWindow::eventFilter(QObject *object, QEvent *event)
{
    if (!( event->type() == QEvent::KeyPress)) return false;

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

     if (ke->key() == Qt::Key_Enter)
    {
        std::cout << RED << "Enter pressed!" << RESET << std::endl;
        moveEnter(object, ui->similar_itemView , ui->similar_groupView);
        moveEnter(object, ui->exact_itemView   , ui->exact_groupView  );
    }
    return true;
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
        m_scanController.setRoot(foldername);
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
    auto set_enabled = [=](bool b){
        ui->commandLinkButton->setEnabled(b);
        ui->FolderButton->setEnabled(b);
        ui->actionScan->setEnabled(b);
        ui->tabWidget->setEnabled(b);

    };

    set_enabled(false);
    ui->statusBar->showMessage("Scanning for images...");

    connect(&m_scanController, &ScanController::scanDone, this,[=](){
        set_enabled(true);
        ui->statusBar->showMessage("scanning for images done");
    });
    connect(&m_scanController, &ScanController::scanStatus ,this, [=]( QString s){
        ui->statusBar->showMessage(s);
    });

    m_scanController.start();
}

void MainWindow::on_commandLinkButton_released(){
    on_actionScan_triggered();
}

void MainWindow::on_FolderButton_clicked(){
    on_actionchange_file_triggered();
}

void MainWindow::initView(QListView * view1, QListView * view2 )
{
    //exact clumn view  + model
    auto mod = new MyStandardItemModel;
    auto item = new QStandardItem("Groups");
    item->appendRow(new QStandardItem("Images"));
    mod->appendRow(item);
    for (auto view : {view1,view2})
    {
        view->setIconSize(QSize(64,64));
        view->setModel(mod);
        view->setDragEnabled(true);
        view->setAcceptDrops(true);
        view->setDropIndicatorShown(true);
        view->setDefaultDropAction(Qt::MoveAction);
        view->installEventFilter(this);
        view->setSelectionMode(QAbstractItemView::SelectionMode::ExtendedSelection);
    }
    view2->setRootIndex(mod->index(0,0));
}

