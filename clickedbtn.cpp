#include "clickedbtn.h"
#include <QString>
#include "global.h"
ClickedBtn::ClickedBtn(QWidget *parent) : QPushButton(parent) {
    setCursor(Qt::PointingHandCursor);
}
ClickedBtn::~ClickedBtn(){}

void ClickedBtn::SetState(QString normal, QString hover, QString press){
    hover_ = hover;
    normal_ = normal;
    press_ = press;
    setProperty("state",normal);
    repolish(this);
    update();

}
void ClickedBtn::enterEvent(QEvent *event){
    setProperty("state",hover_);
    repolish(this);
    update();
    QPushButton::enterEvent(event);
}
void ClickedBtn::leaveEvent(QEvent *event){
    setProperty("state",normal_);
    repolish(this);
    update();
    QPushButton::leaveEvent(event);
}
void ClickedBtn::mousePressEvent(QMouseEvent *event){
    setProperty("state",press_);
    repolish(this);
    update();
    QPushButton::mousePressEvent(event);
}
void ClickedBtn::mouseReleaseEvent(QMouseEvent *event){
    setProperty("state",hover_);
    repolish(this);
    update();
    QPushButton::mouseReleaseEvent(event);
}


