#ifndef STATEWIDGET_H
#define STATEWIDGET_H

#include <QWidget>
#include "global.h"
#include <QLabel>

class StateWidget : public QWidget
{
    Q_OBJECT
public:
    explicit StateWidget(QWidget *parent = nullptr);
    void SetState(QString normal="", QString hover="", QString press="",
        QString select="", QString select_hover="", QString select_press="");
    ClickLbState GetCurState();
    void ClearState();
    void SetSelected(bool bselected);
    void AddRedPoint();
    void ShowRedPoint(bool show=true);

protected:
    void paintEvent(QPaintEvent* event);
    virtual void mousePressEvent(QMouseEvent *ev) override;
    virtual void mouseReleaseEvent(QMouseEvent *ev) override;
    virtual void enterEvent(QEvent* event) override;
    virtual void leaveEvent(QEvent* event) override;
private:
    
    QString normal_;
    QString normal_hover_;
    QString normal_press_;

    QString select_;
    QString select_hover_;
    QString select_press_;

    ClickLbState curState_;
    QLabel *redPoint_;
signals:
    void clicked();


};

#endif // STATEWIDGET_H
