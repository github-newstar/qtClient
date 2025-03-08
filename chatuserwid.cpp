#include "chatuserwid.h"
#include "ui_chatuserwid.h"

ChatUserWid::ChatUserWid(QWidget *parent) :
    ListItemBase(parent),
    ui(new Ui::ChatUserWid)
{
    ui->setupUi(this);
    SetItemType(ListItemType::CHAT_USER_ITEM);
}

ChatUserWid::~ChatUserWid()
{
    delete ui;
}

void ChatUserWid::SetInfo(QString name, QString head, QString msg)
{
    name_ = name;
    head_ = head;
    msg_ = msg;
    // 加载图片
    QPixmap pixmap(head_);
    // 设置图片自动缩放
    ui->iconLab_->setPixmap(pixmap.scaled(ui->iconLab_->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    ui->iconLab_->setScaledContents(true);
    ui->userNameLab_->setText(name_);
    ui->userChatLab_->setText(msg_);
}

