#include "searchlist.h"
#include "adduseritem.h"
#include "tcpmgr.h"



SearchList::SearchList(QWidget *parent): QListWidget(parent) ,
     send_pending_(false),
     find_dlg_(nullptr),
     search_edit_(nullptr)
     {
        Q_UNUSED(parent);
       this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
       this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
       // 安装事件过滤器
       this->viewport()->installEventFilter(this);
       //连接点击的信号和槽
       connect(this, &QListWidget::itemClicked, this, &SearchList::slot_item_clicked);
       //添加条目
       addTipItem();
       //连接搜索条目
       connect(TcpMgr::GetInstance().get(), &TcpMgr::sig_user_search, this, &SearchList::slot_user_search);
}

void SearchList::CloseFindDlg() {
}

void SearchList::SetSearchEdit(QWidget *edit) {
}

void SearchList::waitPending(bool pending) {
}

void SearchList::addTipItem() {
    auto *invalid_item = new QWidget();
    QListWidgetItem *item_tmp = new QListWidgetItem;
    //qDebug()<<"chat_user_wid sizeHint is " << chat_user_wid->sizeHint();
    item_tmp->setSizeHint(QSize(250,10));
    this->addItem(item_tmp);
    invalid_item->setObjectName("invalid_item");
    this->setItemWidget(item_tmp, invalid_item);
    item_tmp->setFlags(item_tmp->flags() & ~Qt::ItemIsSelectable);
    auto *add_user_item = new AddUserItem();
    QListWidgetItem *item = new QListWidgetItem;
    //qDebug()<<"chat_user_wid sizeHint is " << chat_user_wid->sizeHint();
    item->setSizeHint(add_user_item->sizeHint());
    this->addItem(item);
    this->setItemWidget(item, add_user_item);
}

void SearchList::slot_item_clicked(QListWidgetItem *item) {
}

void SearchList::slot_user_search(std::shared_ptr<SearchInfo> si) {
}
