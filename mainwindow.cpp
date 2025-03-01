#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loginDialog_ = new LoginDialog(this);
    setCentralWidget(loginDialog_);
//    loginDialog_->show();

    //创建和注册消息连接
    connect(loginDialog_, &LoginDialog::switchRegister, this, &MainWindow::SlotSwitchReg);
    regDlg_ = new RegisterDialog(this);

    loginDialog_->setWindowFlags(Qt::CustomizeWindowHint |
                                Qt::FramelessWindowHint);
    regDlg_->setWindowFlags(Qt::CustomizeWindowHint |
                                Qt::FramelessWindowHint);
    regDlg_->hide();
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
    setCentralWidget(regDlg_);
    loginDialog_->hide();
    regDlg_->show();
}

