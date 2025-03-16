#include "chatdlg.h"
#include "statewidget.h"
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
    
    QPixmap pixmap("res/head_1.jpg");
    ui->side_head_lab_->setPixmap(pixmap); // 将图片设置到QLabel上
    QPixmap scaledPixmap = pixmap.scaled( ui->side_head_lab_->size(), Qt::KeepAspectRatio); // 将图片缩放到label的大小
    ui->side_head_lab_->setPixmap(scaledPixmap); // 将缩放后的图片设置到QLabel上
    ui->side_head_lab_->setScaledContents(true); // 设置QLabel自动缩放图片内容以适应大小
    ui->side_chat_lab_->setProperty("state","normal");
    ui->side_chat_lab_->SetState("normal","hover","pressed","selected_normal","selected_hover","selected_pressed");
    ui->side_contact_lab_->SetState("normal","hover","pressed","selected_normal","selected_hover","selected_pressed");
    
    AddLBGroup(ui->side_chat_lab_);
    AddLBGroup(ui->side_contact_lab_);
        
    connect(ui->side_chat_lab_, &StateWidget::clicked, this, &chatDlg::slot_side_chat);
    connect(ui->side_contact_lab_, &StateWidget::clicked, this, &chatDlg::slot_side_contact);
    
    connect(ui->searchEdit_, &QLineEdit::textChanged, this, &chatDlg::slot_show_search);
    
    // 检测鼠标点击位置判断是否要清空搜索框
    this->installEventFilter(this);
    ui->side_chat_lab_->SetSelected(true);
}

void chatDlg::ShowSearch(bool bsearch ){
    if(bsearch){
        ui->chatUserList_->hide();
        ui->conUserList_->hide();
        ui->searchList_->show();
        mode_ = ChatUIMode::SearchMode;
    }else if(state_ == ChatUIMode::ChatMode){
        ui->chatUserList_->show();
        ui->conUserList_->hide();
        ui->searchList_->hide();
        mode_ = ChatUIMode::ChatMode;
    }else if(state_ == ChatUIMode::ContactMode){
        ui->chatUserList_->hide();
        ui->searchList_->hide();
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

void chatDlg::AddLBGroup(StateWidget* lb) {
    lb_list_.push_back(lb);
}

void chatDlg::slot_side_chat() {
    qDebug()<< "receive side chat clicked";
    ClearLabelState(ui->side_chat_lab_);
    ui->stackedWidget->setCurrentWidget(ui->chatPage_);
    state_= ChatUIMode::ChatMode;
    ShowSearch(false);
}

void chatDlg::slot_side_contact() {
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

void chatDlg::ClearLabelState(StateWidget* lb){
    for(auto &item : lb_list_){
        if(item == lb){
            continue;
        }
        item->ClearState();
    }
}
void chatDlg::slot_show_search(const QString &text){
    ShowSearch(!text.isEmpty());
}
bool chatDlg::eventFilter(QObject *watched, QEvent *event){
    if (event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        handleGlobalMousePress(mouseEvent);
     }
     return QDialog::eventFilter(watched, event);
}

void chatDlg::handleGlobalMousePress(QMouseEvent *event) {
    // 实现点击位置的判断和处理逻辑
    // 先判断是否处于搜索模式，如果不处于搜索模式则直接返回
    if( mode_!= ChatUIMode::SearchMode){
        return;
    }
    // 将鼠标点击位置转换为搜索列表坐标系中的位置
    QPoint posInSearchList = ui->searchList_->mapFromGlobal(event->globalPos());
    // 判断点击位置是否在聊天列表的范围内
    if (!ui->searchList_->rect().contains(posInSearchList)) {
        // 如果不在聊天列表内，清空输入框
        ui->searchEdit_->clear();
        ShowSearch(false);
    }
    
}