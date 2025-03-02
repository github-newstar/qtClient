#ifndef RESETDIALOG_H
#define RESETDIALOG_H

#include <QDialog>
#include "global.h"
#include <QMap>

namespace Ui {
class ResetDialog;
}

class ResetDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ResetDialog(QWidget *parent = nullptr);
    ~ResetDialog();

private:
    Ui::ResetDialog *ui;
    bool checkUserValid();
    bool checkEmailValid();
    bool checkVarifyValid();
    bool checkNewPwdValid();
    void showTip(const QString &msg, bool ok);

    void AddTipErr(TipErr te, QString tips);
    void DelTipErr(TipErr te);
    
    void initHttpHandlers();

    QMap<TipErr, QString> tip_errs_;
    QMap<ReqId, std::function<void(const QJsonObject&)>> handlers_;
signals:
    void switchLogin();
private slots:
    void on_varifyBtn__clicked();
    void slot_reset_mod_finish(ReqId id, QString res, ErrorCodes err);
    void on_confirmBtn__clicked();
    void on_returnBtn__clicked();
};

#endif // RESETDIALOG_H
