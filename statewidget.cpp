#include "statewidget.h"
#include <QDebug>
#include <QMouseEvent>
#include <QStyleOption>
#include <QPainter>
#include <QVBoxLayout>
#include <QVariant>

StateWidget::StateWidget(QWidget *parent) : QWidget(parent), curState_(ClickLbState::NORMAL)
{
    setCursor(Qt::PointingHandCursor);
    AddRedPoint();
}

void StateWidget::SetState(QString normal, QString hover, QString press, QString select, QString select_hover,
    QString select_press) {
    normal_ = normal;
    normal_hover_ = hover;
    normal_press_ = press;
    select_ = select;
    select_hover_ = select_hover;
    select_press_ = select_press;

    setProperty("state",normal);
    repolish(this); 
}

ClickLbState StateWidget::GetCurState() {
    return curState_;
}

void StateWidget::ClearState() {
    curState_ = ClickLbState::NORMAL;
    setProperty("state",normal_);
    repolish(this);
    update();
}

void StateWidget::SetSelected(bool bselected) {
    if(bselected){
        curState_= ClickLbState::SELECTED;
        setProperty("state",select_);
        repolish(this);
        update();
        return;
    }
    curState_= ClickLbState::NORMAL;
    setProperty("state",normal_);
    repolish(this);
    update();
    return;
}

void StateWidget::AddRedPoint() {
    redPoint_ = new QLabel();
    redPoint_->setObjectName("red_point_");
    QVBoxLayout *layout = new QVBoxLayout();
    redPoint_->setAlignment(Qt::AlignCenter);
    layout->addWidget(redPoint_);
    layout->setMargin(0);
    this->setLayout(layout);
    redPoint_->setVisible(false);
}

void StateWidget::ShowRedPoint(bool show) {
    redPoint_->setVisible(true);
}

void StateWidget::paintEvent(QPaintEvent *event) {
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    return;
}

void StateWidget::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        if(curState_ == ClickLbState::SELECTED){
            qDebug()<<"PressEvent , already to selected press: "<< select_press_;
            //emit clicked();
            // 调用基类的mousePressEvent以保证正常的事件处理
            QWidget::mousePressEvent(event);
            return;
        }
        if(curState_ == ClickLbState::NORMAL){
            qDebug()<<"PressEvent , change to selected press: "<< select_press_;
            curState_ = ClickLbState::SELECTED;
            setProperty("state",select_press_);
            repolish(this);
            update();
        }
        return;
    }
    // 调用基类的mousePressEvent以保证正常的事件处理
    QWidget::mousePressEvent(event);
}

void StateWidget::mouseReleaseEvent(QMouseEvent *ev) {
    if(ev->button() == Qt::LeftButton){
        if(curState_ == ClickLbState::NORMAL){
            qDebug()<<"ReleaseEvent, change to normal hover: "<< normal_hover_;
            setProperty("state",normal_hover_);
            repolish(this);
            update();
        }else{
            qDebug()<<"ReleaseEvent, change to selected hover: "<< select_hover_;
            setProperty("state",select_hover_);
            repolish(this);
            update();
        }
        emit clicked();
        return;
    }
    QWidget::mouseReleaseEvent(ev);
}

void StateWidget::enterEvent(QEvent *event) {
    // 在这里处理鼠标悬停进入的逻辑
    if(curState_ == ClickLbState::NORMAL){
        //qDebug()<<"enter , change to normal hover: "<< _normal_hover;
       setProperty("state", normal_hover_);
       repolish(this);
       update();
   }else{
        //qDebug()<<"enter , change to selected hover: "<< _selected_hover;
       setProperty("state", select_hover_);
       repolish(this);
       update();
   }
    QWidget::enterEvent(event);
}

void StateWidget::leaveEvent(QEvent *event) {
    // 在这里处理鼠标悬停离开的逻辑
    if(curState_== ClickLbState::NORMAL){
        // qDebug()<<"leave , change to normal : "<< _normal;
        setProperty("state",normal_);
        repolish(this);
        update();
    }else{
        // qDebug()<<"leave , change to select normal : "<< _selected;
        setProperty("state",select_);
        repolish(this);
        update();
    }
    QWidget::leaveEvent(event);
}


