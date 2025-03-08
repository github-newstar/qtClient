#include "chatdlg.h"
#include "loadingdlg.h"
#include <QAction>
#include <QRandomGenerator>
#include "ui_chatdlg.h"
#include "chatuserwid.h"
#include "chatuserlist.h"
#include <vector>

chatDlg::chatDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::chatDlg),
    mode_(ChatUIMode::ChatMode),
    state_(ChatUIMode::ChatMode),
    b_loading_(false)
{
    ui->setupUi(this);
    ui->addBtn_->SetState("normal", "hover", "press" );
    ui->searchEdit_->SetMaxLength(15);
    
    QAction *serachAction = new QAction(ui->searchEdit_);
    serachAction->setIcon(QIcon(":/res/search.png"));
    ui->searchEdit_->addAction(serachAction, QLineEdit::LeadingPosition);
    ui->searchEdit_->setPlaceholderText(QStringLiteral("搜索"));
    
    //创建清除动∏作并设置图标
    QAction *clearAction = new QAction(ui->searchEdit_);
    clearAction->setIcon(QIcon(":/res/close_transparent.png"));
    ui->searchEdit_->addAction(clearAction, QLineEdit::TrailingPosition);
    
    //设置显示清理图标的逻辑
    connect(ui->searchEdit_, &QLineEdit::textChanged, [clearAction](const QString &text){
            if(!text.isEmpty()){
                clearAction->setIcon(QIcon("res/close_search.png"));
            }else{
                clearAction->setIcon(QIcon("res/close_transparent.png"));
            }
 } );
    
    //  连接定理文本的信号和槽函数
    connect(clearAction, &QAction::triggered, [this, clearAction]{
            ui->searchEdit_->clear();
            //清除后设置图标为透明
            clearAction->setIcon(QIcon("res/close_transparent.png"));
            ui->searchEdit_->clearFocus();
            // TODO 按下按钮不显示搜索框
            ShowSearch(false);
    });
    
    connect(ui->chatUserList_, &ChatUserList::sig_loading_chat_user, this, &chatDlg::slot_loading_chat_user);
    ShowSearch(false);
    addChatUserList();
}

void chatDlg::ShowSearch(bool bsearch ){
    if(bsearch){
        ui->chatUserList_->hide();
        ui->conUserList_->hide();
        ui->serarchList_->show();
        mode_ = ChatUIMode::SearchMode;
    }else if(state_ == ChatUIMode::ChatMode){
        ui->chatUserList_->show();
        ui->conUserList_->hide();
        ui->serarchList_->hide();
        mode_ = ChatUIMode::ChatMode;
    }else if(state_ == ChatUIMode::ContactMode){
        ui->chatUserList_->hide();
        ui->serarchList_->hide();
        ui->conUserList_->show();
        mode_ = ChatUIMode::ContactMode;
    }
    }
chatDlg::~chatDlg()
{
    delete ui;
}
std::vector<QString>  strs ={"hello world !",
    "nice to meet u",
    "New year，new life",
   "You have to love yourself",
   "My love is written in the wind ever since the whole world is you"};
std::vector<QString> heads = {
"res/head_1.jpg",
"res/head_2.jpg",
"res/head_3.jpg",
"res/head_4.jpg",
"res/head_5.jpg"
};
std::vector<QString> names = {
"llfc",
"zack",
"golang",
"cpp",
"java",
"nodejs",
"python",
"rust"
};
void chatDlg::addChatUserList()
{
    // 创建QListWidgetItem，并设置自定义的widget
    for(int i = 0; i < 13; i++){
        int randomValue = QRandomGenerator::global()->bounded(100); // 生成0到99之间的随机整数
        int str_i = randomValue%strs.size();
        int head_i = randomValue%heads.size();
        int name_i = randomValue%names.size();
        auto *chat_user_wid = new ChatUserWid();
        chat_user_wid->SetInfo(names[name_i], heads[head_i], strs[str_i]);
        QListWidgetItem *item = new QListWidgetItem;
        //qDebug()<<"chat_user_wid sizeHint is " << chat_user_wid->sizeHint();
        item->setSizeHint(chat_user_wid->sizeHint());
        ui->chatUserList_->addItem(item);
        ui->chatUserList_->setItemWidget(item, chat_user_wid);
    }
}

void chatDlg::slot_loading_chat_user() {
    if(b_loading_){
        return;
    }
    
    b_loading_ = true;
    LoadingDlg *loadingDlg = new LoadingDlg(this);
    loadingDlg->setModal(true);
    loadingDlg->show();
    addChatUserList();
    qDebug() << "add new data to list....";
    loadingDlg->deleteLater();
    b_loading_ = false;
}