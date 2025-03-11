#ifndef PICBUBBLE_H
#define PICBUBBLE_H
#include "bubbleframe.h"


class PicBubble : public BubbleFrame
{
    Q_OBJECT
public:
    PicBubble(const QPixmap &pic, ChatRole role, QWidget *parent = nullptr);
};

#endif // PICBUBBLE_H
