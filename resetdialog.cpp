#include "resetdialog.h"
#include "ui_resetdialog.h"
#include <QRegExpValidator>
#include "global.h"
#include <QDebug>
#include "httpmgr.h"

ResetDialog::ResetDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ResetDialog)
{
    ui->setupUi(this);
    
    ui->newPwdEdit_->setEchoMode(QLineEdit::Password);
    ui->err_tip_->setProperty("state", "normal");
    repolish(ui->err_tip_);
    
    ui->err_tip_->clear();
    
    initHttpHandlers();
    connect(HttpMgr::GetInstance().get(), &HttpMgr::sig_reset_mod_finish, this, &ResetDialog::slot_reset_mod_finish);


    connect(ui->userEdit_, &QLineEdit::editingFinished, this, [this]{
        checkUserValid();
    });
    connect(ui->emailEdit_, &QLineEdit::editingFinished, this, [this]{
        checkEmailValid();
    });
    connect(ui->varifyEdit_, &QLineEdit::editingFinished, this, [this]{
        checkVarifyValid();
    });
    connect(ui->newPwdEdit_, &QLineEdit::editingFinished, this, [this]{
        checkNewPwdValid();
    });
}

ResetDialog::~ResetDialog()
{
    delete ui;
}

bool ResetDialog::checkUserValid() {
    if(ui->userEdit_->text() == ""){
        AddTipErr(TipErr::TIP_USER_ERR, tr("用户名不能为空"));
        return false;
    }
    DelTipErr(TipErr::TIP_USER_ERR);
    return true;
}

bool ResetDialog::checkEmailValid() {
//验证邮箱的地址正则表达式
    auto email = ui->emailEdit_->text();
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

bool ResetDialog::checkVarifyValid() {
    auto pass = ui->varifyEdit_->text();
    if(pass.isEmpty()){
        AddTipErr(TipErr::TIP_VARIFY_ERR, tr("验证码不能为空"));
        return false;
    }
    DelTipErr(TipErr::TIP_VARIFY_ERR);
    return true;
}

bool ResetDialog::checkNewPwdValid() {
    auto pass = ui->newPwdEdit_->text();
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

void ResetDialog::AddTipErr(TipErr te, QString tips)
{
    tip_errs_[te] = tips;
    showTip(tips, false);
}
void ResetDialog::DelTipErr(TipErr te) {
    tip_errs_.remove(te);
    if (tip_errs_.empty()) {
        ui->err_tip_->clear();
        return;
    }
    showTip(tip_errs_.first(), false);
}

void ResetDialog::showTip(const QString &msg, bool ok) {
    if (!ok)
        ui->err_tip_->setProperty("state", "err");
    else
        ui->err_tip_->setProperty("state", "normal");
    ui->err_tip_->setText(msg);
    repolish(ui->err_tip_);
}

void ResetDialog::initHttpHandlers() {
    //注册验证码回包
    handlers_.insert(ReqId::ID_GET_VARIFY_CODE, [this](QJsonObject jsonobj){
            int error = jsonobj["error"].toInt();
            if(error != ErrorCodes::SUCCESS){
                showTip("参数错误", false);
                return;
            }
            
            auto email = jsonobj["email"].toString();
            showTip("验证码已发送至" + email+"请注意查收", true);
            qDebug() << "email is " << email;
    });
    
    //注册重置密码回包
    handlers_.insert(ReqId::ID_RESET_PWD, [this](QJsonObject jsonobj){
            int error = jsonobj["error"].toInt();
            if(error != ErrorCodes::SUCCESS){
                showTip("参数错误", false);
                return;
            }
            auto email = jsonobj["email"].toString();
            showTip("重置密码成功,点击登录返回", true);
            qDebug() << "email is " << email;
            qDebug() << "uuid is" << jsonobj["uuid"].toString();
    });

}

void ResetDialog::on_varifyBtn__clicked()
{
    qDebug() <<"receive varify btn clicked";
    auto email = ui->emailEdit_->text();
    auto bcheck = checkEmailValid();
    if(!bcheck){
        return;
    }
    
    //发送http请求获取验证码
    QJsonObject jsonObj;
    jsonObj["email"] = email;
    HttpMgr::GetInstance()->PostHttpReq(QUrl(gate_url_prefix + "/get_code"),
        jsonObj, ReqId::ID_GET_VARIFY_CODE, Modules::RESETMOD);
}

void ResetDialog::slot_reset_mod_finish(ReqId id, QString res, ErrorCodes err) {
    if( err != ErrorCodes::SUCCESS){
        showTip("网络错误", false);
        return;
    }
    
    QJsonDocument jsonDoc = QJsonDocument::fromJson(res.toUtf8());
    
    //json解析错误
    if(jsonDoc.isNull()){
        showTip("网络错误", false);
        return;
    }
    
    if(!jsonDoc.isObject()){
        showTip("网络错误", false);
        return;
    }
    
    handlers_[id](jsonDoc.object());
    
    return;
}

void ResetDialog::on_confirmBtn__clicked()
{
    bool valid = checkUserValid();
        if(!valid){
            return;
        }
        valid = checkEmailValid();
        if(!valid){
            return;
        }
        valid = checkNewPwdValid();
        if(!valid){
            return;
        }
        valid = checkVarifyValid();
        if(!valid){
            return;
        }
        //发送http重置用户请求
        QJsonObject json_obj;
        json_obj["user"] = ui->userEdit_->text();
        json_obj["email"] = ui->emailEdit_->text();
        json_obj["passwd"] = xorString(ui->newPwdEdit_->text());
        json_obj["varifycode"] = ui->varifyEdit_->text();
        HttpMgr::GetInstance()->PostHttpReq(QUrl(gate_url_prefix+"/reset_pwd"),
                     json_obj, ReqId::ID_RESET_PWD,Modules::RESETMOD);
}

void ResetDialog::on_returnBtn__clicked()
{
    qDebug() << "return clicked";
    emit switchLogin();
}
