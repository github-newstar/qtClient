#include "findsuccessdlg.h"
#include <QDir>
#include <QDebug>
#include "ui_findsuccessdlg.h"

FindSuccessDlg::FindSuccessDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FindSuccessDlg)
{
    ui->setupUi(this);
    
    // 设置对话框标题
    setWindowTitle("添加");
    // 隐藏对话框标题栏
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
    // 获取当前应用程序的路径
    QString app_path = QCoreApplication::applicationDirPath();
    QString pix_path = QDir::toNativeSeparators(app_path +
                             QDir::separator() + "static"+QDir::separator()+"head_1.jpg");
    QPixmap head_pix(pix_path);
    head_pix = head_pix.scaled(ui->head_lb_->size(),
            Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->head_lb_->setPixmap(head_pix);
    ui->add_friend_btn_->SetState("normal","hover","press");
    this->setModal(true);
}

FindSuccessDlg::~FindSuccessDlg()
{
    qDebug() << "FindSuccessDlg destructor";
    delete ui;
}

void FindSuccessDlg::SetSearchInfo(std::shared_ptr<SearchInfo> s) {
    ui->name_lb_->setText(s->name_);
    si_ = s;
}

void FindSuccessDlg::on_add_friend_btn__clicked()
{
    //TODO 添加好友界面弹出
}
