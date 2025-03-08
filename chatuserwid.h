#ifndef CHATUSERWID_H
#define CHATUSERWID_H

#include <QWidget>

namespace Ui {
class ChatUserWid;
}

class ChatUserWid : public QWidget
{
    Q_OBJECT

public:
    explicit ChatUserWid(QWidget *parent = nullptr);
    ~ChatUserWid();

private:
    Ui::ChatUserWid *ui;
};

#endif // CHATUSERWID_H
