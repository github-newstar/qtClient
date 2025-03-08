#include "chatpage.h"
#include <QStyleOption>
#include <QPainter>
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