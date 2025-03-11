#include "chatpage.h"
#include "chatitembase.h"
#include <QStyleOption>
#include <QPainter>
#include "textbubble.h"
#include "picbubble.h"
#include "ui_chatpage.h"

ChatPage::ChatPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatPage)
{
    ui->setupUi(this);
    //设置按钮样式
    ui->recvBtn_->SetState("normal","hover","press");
    ui->sendBtn_->SetState("normal","hover","press");
    //设置图标样式
    ui->emo_lab_->SetState("normal","hover","press","normal","hover","press");
    ui->file_lab_->SetState("normal","hover","press","normal","hover","press");
}

ChatPage::~ChatPage()
{
    delete ui;
}

void ChatPage::paintEvent(QPaintEvent *event){
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
void ChatPage::on_sendBtn__clicked()
{
    auto pTextEdit = ui->chatEdit_;
        ChatRole role = ChatRole::Self;
        QString userName = QStringLiteral("恋恋风辰");
        QString userIcon = "res/head_1.jpg";
        const QVector<MsgInfo>& msgList = pTextEdit->getMsgList();
        for(int i=0; i<msgList.size(); ++i)
        {
            QString type = msgList[i].msgFlag;
            ChatItemBase *pChatItem = new ChatItemBase(role);
            pChatItem->setUserName(userName);
            pChatItem->setUserIcon(QPixmap(userIcon));
            QWidget *pBubble = nullptr;
            if(type == "text")
            {
                pBubble = new TextBubble(role, msgList[i].content);
            }
            else if(type == "image")
            {
                pBubble = new PicBubble(QPixmap(msgList[i].content) , role);
            }
            else if(type == "file")
            {
            }
            if(pBubble != nullptr)
            {
                pChatItem->setWidget(pBubble);
                ui->chat_data_list_->appendChatItem(pChatItem);
            }
        }
}
