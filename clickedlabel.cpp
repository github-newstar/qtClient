#include "clickedlabel.h"
#include <QMouseEvent>
#include <QDebug>

ClickedLabel::ClickedLabel (QWidget *parent) : QLabel(parent), curState_(ClickLbState::NORMAL)
{
}

//处理鼠标点击事件
void ClickedLabel::mousePressEvent(QMouseEvent *event) {
    if(event->button() == Qt::LeftButton) {
        if(curState_ == ClickLbState::NORMAL){
            qDebug() << "clicked , changd to selected hover" << selectd_hover_;
            curState_ = ClickLbState::SELECTED;
            setProperty("state",selectd_hover_);
            repolish(this);
            update();
        }else{
            qDebug() << "clicked , changd to nomal hover" << normal_hover_;
            curState_ = ClickLbState::NORMAL;
            setProperty("state",normal_hover_);
            repolish(this);
            update();
        }
        emit clicked();
    }
    QLabel::mousePressEvent(event);
}
//处理鼠标进入事件
void ClickedLabel::enterEvent(QEvent *event) {
    if(curState_ == ClickLbState::NORMAL){
        qDebug() << "enter , changd to normal hover" << normal_hover_;
        setProperty("state",normal_hover_);
        repolish(this);
        update();
    }else{
        qDebug() << "enter , changd to selected hover" << selectd_hover_;
        setProperty("state",selectd_hover_);
        repolish(this);
        update();
    }
    QLabel::enterEvent(event);
}

void ClickedLabel::leaveEvent(QEvent *event) {
    if(curState_ == ClickLbState::NORMAL){
        qDebug() << "leave , changd to normal" << normal_;
        setProperty("state",normal_);
        repolish(this);
        update();
    }else{
        qDebug() << "leave , changd to selected" << selectd_;
        setProperty("state",selectd_);
        repolish(this);
        update();
    }
    QLabel::leaveEvent(event);
}

void ClickedLabel::SetState(QString normal, QString hover, QString press, QString select, QString select_hover,
    QString select_press) {
    normal_ = normal;
    normal_hover_ = hover;
    normal_press_ = press;

    selectd_ = select;
    selectd_hover_ = select_hover;
    selectd_press_ = select_press;
    
    setProperty("state", normal);
    repolish(this);
}

ClickLbState ClickedLabel::GetState() {
    return curState_;
}


