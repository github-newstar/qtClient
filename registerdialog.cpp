#include "registerdialog.h"
#include "ui_registerdialog.h"
#include "global.h"
#include <QRegularExpression>
#include <QDebug>
#include <QJsonObject>
#include "httpmgr.h"
#include<QNetworkAccessManager>
#include<QNetworkReply>
#include "global.h"
#include "clickedlabel.h"

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

    ui->err_tip->clear();
    connect(ui->uesrEdit_, &QLineEdit::editingFinished, this ,[this] {
        checkUserValid();
    });
    connect(ui->mailEdit_, &QLineEdit::editingFinished, this ,[this] {
        checkEmailValid();
    });
    connect(ui->passEdit_, &QLineEdit::editingFinished, this ,[this] {
        checkPwdValid();
    });
    connect(ui->confirmPassEdit_, &QLineEdit::editingFinished, this ,[this] {
        checkConfirmValid();
    });
    connect(ui->verifyEdit_, &QLineEdit::editingFinished, this ,[this] {
        checkVarifyValid();
    });
    ui->passVisible_->setCursor(Qt::PointingHandCursor);
    ui->confirmPassVisible_->setCursor(Qt::PointingHandCursor);
    
    ui->passVisible_->SetState("unvisible", "unvisible_hover","" ,
        "visible", "visible_hover", "");
    ui->confirmPassVisible_->SetState("unvisible", "unvisible_hover","" ,
        "visible", "visible_hover", "");
    
    connect(ui->passVisible_, &ClickedLabel::clicked, this, [this] {
            auto state = ui->passVisible_->GetState();
            if(state == ClickLbState::NORMAL){
                ui->passEdit_->setEchoMode(QLineEdit::Password);
            }else{
                ui->passEdit_->setEchoMode(QLineEdit::Normal);
            }
            
            qDebug() << "label clicked";
    });
    connect(ui->confirmPassVisible_, &ClickedLabel::clicked, this, [this] {
            auto state = ui->confirmPassVisible_->GetState();
            if(state == ClickLbState::NORMAL){
                ui->confirmPassEdit_->setEchoMode(QLineEdit::Password);
            }else{
                ui->confirmPassEdit_->setEchoMode(QLineEdit::Normal);
            }
            
            qDebug() << "label clicked";
    });
}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}

void RegisterDialog::AddTipErr(TipErr te, QString tips) {
    tips_errs_[te] = tips;
    showTip(tips, false);
}

void RegisterDialog::DelTipErr(TipErr te) {
    tips_errs_.remove(te);
    if (tips_errs_.isEmpty()){
        ui->err_tip->clear();
        return;
    }
    showTip(tips_errs_.first(), false);
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
    if (checkUserValid() == false) {
        return;
    }
    if (checkEmailValid() == false) {
        return;
    }
    if (checkPwdValid() == false) {
        return;
    }
    if(checkConfirmValid() == false) {
        return;
    }
    if(checkVarifyValid() == false) {
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

bool RegisterDialog::checkUserValid() {
    if (ui->uesrEdit_->text().isEmpty()) {
        AddTipErr(TipErr::TIP_USER_ERR, tr("用户名不能为空"));
        return false;
    }
    DelTipErr(TipErr::TIP_USER_ERR);
    return true;
}

bool RegisterDialog::checkEmailValid() {

    auto email = ui->mailEdit_->text();
    // 邮箱地址的正则表达式
    QRegularExpression regex(R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)");
    bool match = regex.match(email).hasMatch(); // 执行正则表达式匹配
    if(!match){
        //提示邮箱不正确
        AddTipErr(TipErr::TIP_EMAIL_ERR, tr("邮箱地址不正确"));
        return false;
    }
    DelTipErr(TipErr::TIP_EMAIL_ERR);
    return true;
}

bool RegisterDialog::checkPwdValid() {
    auto pass = ui->passEdit_->text();
    if(pass.length() < 6 || pass.length()>15){
        //提示长度不准确
        AddTipErr(TipErr::TIP_PWD_ERR, tr("密码长度应为6~15"));
        return false;
    }
    // 创建一个正则表达式对象，按照上述密码要求
    // 这个正则表达式解释：
    // ^[a-zA-Z0-9!@#$%^&*]{6,15}$ 密码长度至少6，可以是字母、数字和特定的特殊字符
    QRegularExpression regExp("^[a-zA-Z0-9!@#$%^&*]{6,15}$");
    bool match = regExp.match(pass).hasMatch();
    if(!match){
        //提示字符非法
        AddTipErr(TipErr::TIP_PWD_ERR, tr("不能包含非法字符"));
        return false;;
    }
    DelTipErr(TipErr::TIP_PWD_ERR);
    return true;
}

bool RegisterDialog::checkConfirmValid() {
    auto firstPass = ui->passEdit_->text();
    auto secondPass = ui->confirmPassEdit_->text();
    if (firstPass != secondPass) {
        AddTipErr(TipErr::TIP_CONFIRM_ERR, tr("两次输入的密码不一致"));
        return false;
    }
    DelTipErr(TipErr::TIP_CONFIRM_ERR);
    return true;
}

bool RegisterDialog::checkVarifyValid() {
    auto varify = ui->verifyEdit_->text();
    if (varify.isEmpty()) {
        AddTipErr(TipErr::TIP_VERIFY_ERR, tr("验证码不能为空"));
        return false;
    }
    DelTipErr(TipErr::TIP_VERIFY_ERR);
    return true;
}
