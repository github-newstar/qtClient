#include "chatuserwid.h"
#include "ui_chatuserwid.h"

ChatUserWid::ChatUserWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatUserWid)
{
    ui->setupUi(this);
}

ChatUserWid::~ChatUserWid()
{
    delete ui;
}
