#include "logindialog.h"
#include "ui_logindialog.h"
#include <QDebug>
#include <QJsonObject>
#include <QUrl>
#include <QRegExpValidator>
#include "httpmgr.h"
#include "tcpmgr.h"

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
    
    //连接tcp连接请求和槽函数
    QObject::connect(this, &LoginDialog::sig_connect_tcp, TcpMgr::GetInstance().get(), &TcpMgr::slot_tcp_connect);
    
    //连接tcpmgr的连接成功信号
    connect(TcpMgr::GetInstance().get(), &TcpMgr::sig_con_success, this, &LoginDialog::slot_tcp_con_finish);
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
    //使用邮箱验证用户
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
bool LoginDialog::enableBtn(bool enabled)
{
    ui->loginBtn_->setEnabled(enabled);
    ui->regBtn_->setEnabled(enabled);
    return true;
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
    //关闭按钮
    enableBtn(false);
    auto email= ui->emailEdit_->text();
    auto pwd = ui->passEdit_->text();

    QJsonObject jsonObj;
    jsonObj["email"] = email;
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
            
            //发信号通知tcpMgr发送长连接
            ServerInfo si;
            si.Uid = obj["uid"].toInt();
            si.Host = obj["host"].toString();
            si.Port = obj["port"].toString();
            si.Token = obj["token"].toString();
            
            
            uid_ = si.Uid;
            token_ = si.Token;
            qDebug() << "user is " << user << "uid is " << si.Uid << " host is "
            << si.Host << " port  is " << si.Port << " token is " << si.Token;
            emit sig_connect_tcp(si);
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
void LoginDialog::slot_tcp_con_finish(bool success){
    if(success){
        showTip(tr("聊天服务连接成功，正在登录..."),true);
        QJsonObject jsonObj;
        jsonObj["uid"] = uid_;
        jsonObj["token"] = token_;
  
        QJsonDocument doc(jsonObj);
        QString jsonString = doc.toJson(QJsonDocument::Indented);
  
        //发送tcp请求给chat server
        TcpMgr::GetInstance()->sig_send_data(ReqId::ID_CHAT_LOGIN, jsonString);
    }
    else{
        showTip(tr("网络错误"), false);
        enableBtn(true);
    }
}