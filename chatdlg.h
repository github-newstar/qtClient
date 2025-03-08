#ifndef CHATDLG_H
#define CHATDLG_H

#include <QDialog>

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
    Ui::chatDlg *ui;
};

#endif // CHATDLG_H
