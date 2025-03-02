#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loginDialog_ = new LoginDialog(this);
    loginDialog_->setWindowFlags(Qt::CustomizeWindowHint |
                                Qt::FramelessWindowHint);

    setCentralWidget(loginDialog_);
//    loginDialog_->show();

    //创建和注册消息连接
    connect(loginDialog_, &LoginDialog::switchRegister, this, &MainWindow::SlotSwitchReg);
    
    //连接登录界面忘记密码信号    void SoltSwitchReset();


    connect(loginDialog_, &LoginDialog::switchReset, this, &MainWindow::SlotSwitchReset);

}

MainWindow::~MainWindow()
{
    delete ui;
//    if(loginDialog_){
//        delete loginDialog_;
//        loginDialog_ = nullptr;
//    }
//    if(regDlg_){
//        delete regDlg_;
//        regDlg_ = nullptr;
//    }
}

void MainWindow::SlotSwitchReg() {
    regDlg_ = new RegisterDialog(this);
    regDlg_->setWindowFlags(Qt::CustomizeWindowHint |
                                Qt::FramelessWindowHint);

    connect(regDlg_, &RegisterDialog::sigSwitchLogin, this, &MainWindow::SlotSwitchLogin);
    setCentralWidget(regDlg_);
    loginDialog_->hide();
    regDlg_->show();
}
void MainWindow::SlotSwitchLogin() {
    // 创建一个CentralWidget, 并将其设置为MainWindow的中心部件
    loginDialog_ = new LoginDialog(this);
    loginDialog_->setWindowFlags(Qt::CustomizeWindowHint |
                                 Qt::FramelessWindowHint);
    setCentralWidget(loginDialog_);
    regDlg_->hide();
    loginDialog_->show();
    // 连接登录界面注册信号
    connect(loginDialog_, &LoginDialog::switchRegister, this,
            &MainWindow::SlotSwitchReg);
    // 连接登录界面忘记密码信号     
    connect(loginDialog_, &LoginDialog::switchReset, this,
            &MainWindow::SlotSwitchReset);
}

void MainWindow::SlotSwitchReset() {
    resetDlg_ = new ResetDialog(this);
    resetDlg_->setWindowFlags(Qt::CustomizeWindowHint |
                                Qt::FramelessWindowHint);
    setCentralWidget(resetDlg_);
    loginDialog_->hide();
    resetDlg_->show();
    //注册返回登录和信号和槽函数
    connect(resetDlg_, &ResetDialog::switchLogin, this, &MainWindow::SlotSwitchLogin2);
}
void MainWindow::SlotSwitchLogin2() {
    // 创建一个CentralWidget, 并将其设置为MainWindow的中心部件
    loginDialog_ = new LoginDialog(this);
    loginDialog_->setWindowFlags(Qt::CustomizeWindowHint |
                                 Qt::FramelessWindowHint);
    setCentralWidget(loginDialog_);
    resetDlg_->hide();
    loginDialog_->show();
    // 连接登录界面注册信号
    connect(loginDialog_, &LoginDialog::switchRegister, this,
            &MainWindow::SlotSwitchReg);
    // 连接登录界面忘记密码信号
    connect(loginDialog_, &LoginDialog::switchReset, this,
            &MainWindow::SlotSwitchReset);
}
