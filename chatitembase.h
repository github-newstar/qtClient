#ifndef CHATITEMBASE_H
#define CHATITEMBASE_H
#include <QWidget>
#include "global.h"
#include <QLabel>
class BubbleFrame;
class ChatItemBase : public QWidget
{
    Q_OBJECT
public:
    explicit ChatItemBase(ChatRole role, QWidget *parent = nullptr);
    void setUserName(const QString &name);
    void setUserIcon(const QPixmap &icon);
    void setWidget(QWidget *w);
private:
    ChatRole role_;
    QLabel *pNameLable_;
    QLabel *pIconLable_;
    QWidget *pBubble_;

};

#endif // CHATITEMBASE_H
