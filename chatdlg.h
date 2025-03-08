#ifndef CHATDLG_H
#define CHATDLG_H

#include <QDialog>
#include "global.h"

namespace Ui {
class chatDlg;
}

class chatDlg : public QDialog
{
    Q_OBJECT

public:
    explicit chatDlg(QWidget *parent = nullptr);
    ~chatDlg();

private:
    void ShowSearch(bool bserarch = false);
    void addChatUserList();
    Ui::chatDlg *ui;
    ChatUIMode mode_;
    ChatUIMode state_;
    bool b_loading_;
public slots:
    void slot_loading_chat_user();
};

#endif // CHATDLG_H
