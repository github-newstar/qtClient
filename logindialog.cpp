#include "logindialog.h"
#include "ui_logindialog.h"
#include <QDebug>
#include <QJsonObject>
#include <QUrl>
#include <QRegExpValidator>
#include "httpmgr.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    connect(ui->regBtn_, &QPushButton::clicked, this, &LoginDialog::switchRegister);
    ui->forgetLabel_->SetState("normal", "hover", "", "selected", "selected_hover", "");
    connect(ui->forgetLabel_, &ClickedLabel::clicked, this, &LoginDialog::slot_forget_pwd);
    
    initHandlers();
    connect(HttpMgr::GetInstance().get(), &HttpMgr::sig_login_mod_finish, this, &LoginDialog::slot_login_finish);
}

void LoginDialog::AddTipErr(TipErr te, QString tips) {
    tip_errs_[te] = tips;
    showTip(tips, false);
}

void LoginDialog::DelTipErr(TipErr te) {
    tip_errs_.remove(te);
    if (tip_errs_.empty()) {
        ui->login_tip_->clear();
        return;
    }
    showTip(tip_errs_.first(), false);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

bool LoginDialog::checkUserValid() {
    auto user = ui->userEdit_->text();
    if(user.isEmpty()){
        AddTipErr(TipErr::TIP_USER_ERR, tr("用户名不能为空"));
        return false;
    }
    
    return true;
}

bool LoginDialog::checkPwdValid() {
    auto pwd = ui->passEdit_->text();
    if(pwd.length() < 6 || pwd.length() > 15){
        AddTipErr(TipErr::TIP_PWD_ERR, tr("密码长度应为6~15"));
        return false;
    }
    // 创建一个正则表达式对象，按照上述密码要求
    // 这个正则表达式解释：
    // ^[a-zA-Z0-9!@#$%^&*]{6,15}$ 密码长度至少6，可以是字母、数字和特定的特殊字符
    QRegularExpression regExp("^[a-zA-Z0-9!@#$%^&*]{6,15}$");
    bool match = regExp.match(pwd).hasMatch();
    if(!match){
        //提示字符非法
        AddTipErr(TipErr::TIP_PWD_ERR, tr("不能包含非法字符"));
        return false;;
    }

    DelTipErr(TipErr::TIP_PWD_ERR);
    return true;
}

void LoginDialog::slot_forget_pwd()
{
    qDebug() << "forget pwd";
    emit switchReset();
}

void LoginDialog::on_loginBtn__clicked()
{
    qDebug() <<"login btn clicked";
    if( !checkUserValid()){
        return;
    }
    if(!checkPwdValid()){
        return;
    }
    auto user = ui->userEdit_->text();
    auto pwd = ui->passEdit_->text();

    QJsonObject jsonObj;
    jsonObj["user"] = user;
    jsonObj["passwd"] = xorString(pwd);
    HttpMgr::GetInstance()->PostHttpReq(QUrl(gate_url_prefix+"/user_login"),
                                        jsonObj, ReqId::ID_LOGIN_USER,Modules::LOGINMOD);
}

void LoginDialog::showTip(const QString& tip, bool success)
{
    if(success){
        ui->login_tip_->setProperty("state", "normal");
    }else{
        ui->login_tip_->setProperty("state", "err");
    }
    ui->login_tip_->setText(tip);
    repolish(ui->login_tip_);
}

void LoginDialog::initHandlers()
{
    handlers_.insert(ReqId::ID_LOGIN_USER, [this](const QJsonObject& obj){
            int error = obj["error"].toInt();
            if(error != ErrorCodes::SUCCESS){
                showTip(tr("参数错误"), false);
                return;
            }
            auto user = obj["user"].toString();
            showTip(tr("登录成功"), true);
            qDebug() << "user is " << user;
    });
}

void LoginDialog::slot_login_finish(ReqId id, QString res, ErrorCodes err)
{
    if( err != ErrorCodes::SUCCESS){
        showTip(tr("网络错误"), false);
        return;
    }
    // 解析 JSON 字符串,res需转化为QByteArray
    QJsonDocument jsonDoc = QJsonDocument::fromJson(res.toUtf8());
    //json解析错误
    if(jsonDoc.isNull()){
        showTip(tr("json解析错误"),false);
        return;
    }
    //json解析错误
    if(!jsonDoc.isObject()){
        showTip(tr("json解析错误"),false);
        return;
    }
    //调用对应的逻辑,根据id回调。
    handlers_[id](jsonDoc.object());
    return;
}
