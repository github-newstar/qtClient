#ifndef FINDSUCCESSDLG_H
#define FINDSUCCESSDLG_H

#include <QDialog>
#include "userdata.h"

namespace Ui {
class FindSuccessDlg;
}

class FindSuccessDlg : public QDialog
{
    Q_OBJECT

public:
    explicit FindSuccessDlg(QWidget *parent = nullptr);
    ~FindSuccessDlg();
    void SetSearchInfo(std::shared_ptr<SearchInfo> s);
private slots:
    void on_add_friend_btn__clicked();

private:
    Ui::FindSuccessDlg *ui;
    QWidget *parent_;
    std::shared_ptr<SearchInfo> si_;
};

#endif // FINDSUCCESSDLG_H
