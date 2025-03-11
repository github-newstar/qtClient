#include "picbubble.h"
#include <QLabel>

const int PIC_MAX_WIDTH = 160;
const int PIC_MAX_HEIGHT = 90;

PicBubble::PicBubble(const QPixmap &pic, ChatRole role, QWidget *parent) : BubbleFrame(role, parent){
    QLabel *lb = new QLabel();
    lb->setScaledContents(true);
    QPixmap pix = pic.scaled(QSize(PIC_MAX_WIDTH, PIC_MAX_HEIGHT), Qt::KeepAspectRatio);
    lb->setPixmap(pix);
    this->setWidget(lb);
    int left_margin = this->layout()->contentsMargins().left();
    int right_margin = this->layout()->contentsMargins().right();
    int v_margin = this->layout()->contentsMargins().bottom();
    setFixedSize(pix.width()+left_margin + right_margin, pix.height() + v_margin *2);
}