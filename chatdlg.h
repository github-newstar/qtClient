#ifndef CHATDLG_H
#define CHATDLG_H

#include <QDialog>
#include "global.h"
class StateWidget;
namespace Ui {
class chatDlg;
}

class chatDlg : public QDialog
{
    Q_OBJECT

public:
    explicit chatDlg(QWidget *parent = nullptr);
    ~chatDlg();
protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

private:
    void ShowSearch(bool bserarch = false);
    void addChatUserList();
    void AddLBGroup(StateWidget*);
    void ClearLabelState(StateWidget*);
    void handleGlobalMousePress(QMouseEvent *event);

    Ui::chatDlg *ui;
    ChatUIMode mode_;
    ChatUIMode state_;
    bool b_loading_;
    QList<StateWidget*> lb_list_;
public slots:
    void slot_loading_chat_user();
    void slot_side_chat();
    void slot_side_contact();
    void slot_show_search(const QString &text);
};

#endif // CHATDLG_H
