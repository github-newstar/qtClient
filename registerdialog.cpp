#include "registerdialog.h"
#include "ui_registerdialog.h"
#include "global.h"
#include <QRegularExpression>
#include <QJsonObject>
#include "httpmgr.h"
#include<QNetworkAccessManager>
#include<QNetworkReply>
#include "global.h"

RegisterDialog::RegisterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);
    ui->passEdit_->setEchoMode(QLineEdit::Password);
    ui->confirmPassEdit_->setEchoMode(QLineEdit::Password);
    ui->err_tip->setProperty("state", "normal");
    repolish(ui->err_tip);
    initHttpHandlers();

    connect(HttpMgr::GetInstance().get(), &HttpMgr::sig_reg_mod_finish,this, &RegisterDialog::slot_reg_mod_finish);
}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}

void RegisterDialog::showTip(const QString &msg, bool ok) {
    if (!ok)
        ui->err_tip->setProperty("state", "err");
    else
        ui->err_tip->setProperty("state", "normal");

    ui->err_tip->setText(msg);
    repolish(ui->err_tip);

    // connect(HttpMgr::GetInstance().get(), &HttpMgr::sig_reg_mod_finish,
    //     this, &RegisterDialog::slot_reg_mod_finish);
}

void RegisterDialog::on_getBtn__clicked()
{
    auto email = ui->mailEdit_->text();
    QRegularExpression regex(R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)");
    bool match = regex.match(email).hasMatch();
    if(match){
        QJsonObject jsonObj;
        jsonObj["email"] = email;
        qDebug() << "jsonObj is " << jsonObj;
        // QUrl url("http://localhost:8080/get_test");
        // QNetworkRequest request(url);
        // QNetworkReply reply = HttpMgr::GetInstance()->manager_.get(request);
        // connect(reply, &QNetworkReply::finished, this, [&]() {
        //
        // });
        HttpMgr::GetInstance()->PostHttpReq(QUrl(gate_url_prefix + "/get_code"),
            jsonObj, ReqId::ID_GET_VARIFY_CODE, Modules::REGISTERMOD);
    }else{
        showTip("邮箱不正确", false);
    }
}

void RegisterDialog::slot_reg_mod_finish(ReqId id, QString res, ErrorCodes err, Modules mod) {
    if (err != ErrorCodes::SUCCESS) {
        showTip(tr("网络请求失败"), false);
        return;
    }
    //解析json字符串 res 转换为QByteArry
    QJsonDocument jsonDoc = QJsonDocument::fromJson(res.toUtf8());
    if (jsonDoc.isNull()) {
        showTip(tr("解析json失败"), false);
        return;
    }
    //json 解析失败
    if (!jsonDoc.isObject()) {
        showTip(tr("json解析失败"), false);
        return;
    }

    handlers_[id](jsonDoc.object());
    return;
}
void RegisterDialog::initHttpHandlers() {
    //注册获取验证码回包逻辑
    handlers_[ID_GET_VARIFY_CODE] = [this](const QJsonObject &obj) {
        int error = obj["error"].toInt();
        if (error != ErrorCodes::SUCCESS) {
            showTip(tr("参数错误"), false);
            return;
        }

        auto email = obj["email"].toString();
        showTip(tr("验证码已发送到邮箱").arg(email), true);
        qDebug() << "email is "<< email;
    };
    handlers_[ReqId::ID_REG_USER] = [this](QJsonObject jsonObj) {
        int erro = jsonObj["error"].toInt();
        if (erro != ErrorCodes::SUCCESS) {
            showTip(tr("参数错误"), false);
            return;
        }
        auto email = jsonObj["email"].toString();
        showTip(tr("用户注册成功").arg(email), true);
        qDebug() << "user name is " << jsonObj["user"].toString();
        qDebug() << "email is "<< email;
    };
}

void RegisterDialog::on_confirmBtn__clicked()
{
    if(ui->uesrEdit_->text() == ""){
        showTip(tr("用户名不能为空"), false);
        return;
    }
    if(ui->mailEdit_->text() == ""){
        showTip(tr("邮箱不能为空"), false);
        return;
    }
    if(ui->passEdit_->text() == ""){
        showTip(tr("密码不能为空"), false);
        return;
    }
    if(ui->confirmPassEdit_->text() == ""){
        showTip(tr("确认密码不能为空"), false);
        return;
    }
    if(ui->confirmPassEdit_->text() != ui->passEdit_->text()){
        showTip(tr("密码和确认密码不匹配"), false);
        return;
    }
    if(ui->verfiLabel_->text() == ""){
        showTip(tr("验证码不能为空"), false);
        return;
    }
    QJsonObject json_obj;
    json_obj["user"] = ui->uesrEdit_->text();
    json_obj["email"] = ui->mailEdit_->text();
    json_obj["passwd"] = xorString(ui->passEdit_->text());
    json_obj["confirm"] = xorString(ui->confirmPassEdit_->text());
    json_obj["varifycode"] = ui->verifyEdit_->text();
    HttpMgr::GetInstance()->PostHttpReq(QUrl(gate_url_prefix+"/ug"),
                 json_obj, ReqId::ID_REG_USER,Modules::REGISTERMOD);
}
