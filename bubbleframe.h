#ifndef BUBBLEFRAME_H
#define BUBBLEFRAME_H

#include <QWidget>
#include <QFrame>
#include "global.h"
#include <QHBoxLayout>

class BubbleFrame : public QFrame
{
    Q_OBJECT
public:
    BubbleFrame(ChatRole role, QWidget *parent = nullptr);
    void setMaregin(int margin);
    void setWidget(QWidget *w);
protected:
    void paintEvent(QPaintEvent *event) override;
private:
    QHBoxLayout *pHlayout_;
    ChatRole role_;
    int margin_;
};

#endif // BUBBLEFRAME_H
