//
// Created by jo on 2025/3/1.
//
#include <QDebug>
#include <QMouseEvent>

#include "TimerBtn.h"

TimerBtn::TimerBtn(QWidget *parent) : QPushButton(parent), counter_(10) {
    timer_ = new QTimer(this);
    connect(timer_, &QTimer::timeout, this, [=]() {
        counter_--;
        if (counter_ <= 0) {
            timer_->stop();
            counter_ = 10;
            this->setText("获取");
            this->setEnabled(true);
            return;
        }
        this->setText(QString::number(counter_));
    });
}

TimerBtn::~TimerBtn() {
}

void TimerBtn::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() == Qt::LeftButton) {
        qDebug() << "left button";
        this->setEnabled(false);
        this->setText(QString::number(counter_));
        timer_->start(1000);
        emit clicked();
    }
    QPushButton::mouseMoveEvent(event);
}
