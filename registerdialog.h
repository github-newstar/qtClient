#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>
#include <QJsonObject>
#include <QMap>

#include "global.h"

namespace Ui {
class RegisterDialog;
}

class RegisterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterDialog(QWidget *parent = nullptr);
    ~RegisterDialog();

private slots:
    void on_getBtn__clicked();
    void slot_reg_mod_finish(ReqId id, QString res, ErrorCodes err, Modules mod);

    void on_confirmBtn__clicked();

private:
    void initHttpHandlers();
    void showTip(const QString &msg, bool ok);
    Ui::RegisterDialog *ui;
    QMap<ReqId, std::function<void(const QJsonObject&)>> handlers_;
};

#endif // REGISTERDIALOG_H
