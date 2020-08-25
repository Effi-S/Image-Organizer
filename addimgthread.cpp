#include "addimgthread.h"

size_t AddingImgThread::m_size_limit = 5;
AddingImgThread::AddingImgThread(MyStandardItemModel *model)
    {

    connect(this, &AddingImgThread::addRow, model, &MyStandardItemModel::addRow);
    connect(this, &AddingImgThread::clear, model, &MyStandardItemModel::clear);
    emit clear();

}
void AddingImgThread::setGroupSizeLimit(size_t limit){
   AddingImgThread::m_size_limit = limit;
}
void AddingImgThread::addStringList(const std::vector<std::wstring>  &l)
{
   if(l.size() < m_size_limit)return;

    for(auto & x : l){
        //std::wcout << L"adding " << x <<std::endl;
        m_path_list.append(QString::fromStdWString(x));
   }
   run();
}

void AddingImgThread::run()
{

    QList<QString>::const_iterator first = m_path_list.cbegin();

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
   m_path_list.clear();
}
