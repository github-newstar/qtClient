//
// Created by jo on 2025/3/1.
//

#ifndef TIMERBTN_H
#define TIMERBTN_H
#include<QPushButton>
#include<QTimer>



class TimerBtn : public QPushButton
{
public:
    TimerBtn(QWidget *parent = nullptr);
    ~TimerBtn();
    void mouseMoveEvent(QMouseEvent *event) override;
private:
    QTimer *timer_;
    int counter_;
};



#endif //TIMERBTN_H
