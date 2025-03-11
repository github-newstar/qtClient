#ifndef CHATVIEW_H
#define CHATVIEW_H

#include <QObject>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QWidget>
#include <QEvent>
#include <QPaintEvent>

class ChatView : public QWidget
{
    Q_OBJECT
public:
    ChatView(QWidget *parent = 0);
    void appendChatItem(QWidget *item);     //尾插
    void prependChatItem(QWidget *item);    //头插
    void insertChatItem(QWidget *before, QWidget *item);    //中间插
                                                            //
protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private slots:
    void onVScrollBarMoved(int min, int max);
private:
    void initStyleSheet();

    QVBoxLayout *layout_;
    QScrollArea *scrollArea_;
    bool isAppended; 
};

#endif // CHATVIEW_H
