#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include "global.h"
#include <QMap>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

    bool checkUserValid();
    bool checkPwdValid();
public slots:
    void slot_forget_pwd();
private:
    Ui::LoginDialog *ui;
    
    void initHandlers();
    void showTip(const QString& tip, bool b_ok);
    void AddTipErr(TipErr te, QString tips);
    void DelTipErr(TipErr te);
    
    QMap<TipErr, QString> tip_errs_;
    QMap<ReqId, std::function<void(const QJsonObject&)>> handlers_;
signals:
    void switchRegister();
    void switchReset();
private slots:
    void on_loginBtn__clicked();
    void slot_login_finish(ReqId id, QString res, ErrorCodes err);
};

#endif // LOGINDIALOG_H
