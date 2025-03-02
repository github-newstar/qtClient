#ifndef CLICKEDLABEL_H

#define CLICKEDLABEL_H
#include <QLabel>
#include <global.h>

class ClickedLabel : public QLabel
{
    Q_OBJECT
public:
    ClickedLabel(QWidget *parent = nullptr);
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void enterEvent(QEvent *event) override;
    virtual void leaveEvent(QEvent *event) override;
    
    void SetState(QString normal = "", QString hover = "", QString press = "",
                  QString select = "", QString select_hover = "", QString select_press = "");
    ClickLbState GetState();
private:
    QString normal_;
    QString normal_hover_;
    QString normal_press_;
    
    QString selectd_;
    QString selectd_hover_;
    QString selectd_press_;
    
    ClickLbState curState_;
    
signals:
    void clicked();
    
};

#endif // CLICKEDLABEL_H
