#include "ScanController.h"
#include <QAtomicInt>
ScanController::ScanController()
{

}
void ScanController::addModel(QAbstractItemModel * model, ScanController::algoType type, QProgressBar * bar)
{
    auto thread = new  ScannerThread(model,typeToFunc(type));

    connect(thread, &ScannerThread::Scanning , model, [=](bool fl){if(fl)model->removeRows(1,model->rowCount());} );

    connect(thread, &ScannerThread::sendImgGroup, model, [=](const QStringList  l){
        QAbstractItemModel *m = model;
        auto t = new AddingImgThread(&m, l);
        QThreadPool::globalInstance()->start(t);

    });

    if(bar)
    {
        connect(thread, &ScannerThread::scanPercent, bar, &QProgressBar::setValue );
        connect(thread, &ScannerThread::Scanning, bar, &QProgressBar::setVisible );
    }
    m_threads.push_back(std::move(thread));
}

void ScanController::run()
{
    std::clock_t start(std::clock());
    int dbSize = 1;

    emit scanStatus("searching for images.");
    ImgFileScanner::scan(m_root.toStdString());

    emit scanDone(true);
    dbSize = int(ImgFileScanner::size());

    emit scanStatus("Found: "+ QString::number(dbSize) +"images.");

    std::cout <<ORANGE<< "Time reading images scan took: " <<GREEN<< double(std::clock()) - start <<RESET<< std::endl;

    //running algorithms in threads
    std::vector<std::unique_ptr<QFuture<void> >> futures;

    for(auto &thread: m_threads)
        futures.push_back(std::make_unique<QFuture<void>>(QtConcurrent::run(thread , &ScannerThread::start)));

    for(auto & future: futures)
        future->waitForFinished();

}

std::function<ImgMatchFinderBase *()> ScanController::typeToFunc(ScanController::algoType type)
{
    std::unordered_map<algoType, std::function<ImgMatchFinderBase *()> >
            m = {
    {algoType::exact,[=](){return std::move(new BitExactImgFinder);}},
    {algoType::similar,[=](){return std::move(new SimilarImgFinder);}},
    {algoType::search,[=](){return std::move(new ImgSearch);}}
};

    return m.at(type);
}

void ScannerThread::run()
{
   emit Scanning(true);
   auto comp = m_func();

    m_algo =std::make_unique<AlgoThread> (comp);

    QFuture<void> future = QtConcurrent::run(m_algo.get(), &AlgoThread::start);

    int db_size = int(ImgFileScanner::size());
    int images = 1;
    while (future.isRunning() || comp->getMatchGroups().size()>0) {
        for(auto i: comp->getMatchGroups())
        {
            QStringList l;
            for(auto mem: i)
                l.append(mem.c_str());
            images += l.size();
            emit sendImgGroup(l);
            emit scanPercent(100*int(images/db_size));
        }
    }
    //emit Scanning(false);
}
void AlgoThread::run()
{
    auto start = double(std::clock());
    m_comp->makeMatchGroups();
    std::cout <<ORANGE<< "ImgFinder took: " <<GREEN<< double(std::clock()) - start <<RESET<< std::endl;
    emit resultReady();
}

AddingImgThread::AddingImgThread(QAbstractItemModel **model, const QStringList &l)
    : m_path_list(l), m_model(model){
    auto mod = static_cast<MyStandardItemModel *>(*m_model);
    connect(this, &AddingImgThread::addRow, mod, &MyStandardItemModel::addRow);
}

void AddingImgThread::run()
{
    auto first = m_path_list.cbegin();

    QStandardItem *group = new QStandardItem(QIcon(*first),
                                             QVariant(m_path_list.length()).toString());

    for(;first != m_path_list.cend(); ++first)
    {
        QStandardItem *child = new QStandardItem(QIcon(*first) ,*first);

        child->setToolTip(*first);
        child->setCheckable(true);
        child->setDragEnabled(true);
        child->setDropEnabled(true);
        child->setEditable(false);
        if(first!=m_path_list.cbegin())
            child->setCheckState(Qt::Checked);
        group->appendRow(std::move(child));
    }
    group->setCheckable(false);

   emit addRow(std::move(group));
}
