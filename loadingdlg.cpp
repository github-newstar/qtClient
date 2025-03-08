#include "loadingdlg.h"
#include <QMovie>
#include "ui_loadingdlg.h"

LoadingDlg::LoadingDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoadingDlg)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint |
    Qt::WindowSystemMenuHint);
    setAttribute(Qt::WA_TranslucentBackground);
    //获取屏幕尺寸
    setFixedSize(parent->size());
    
    QMovie *movie = new QMovie("res/loading.gif");
    ui->loadLab_->setMovie(movie);
    movie->start();
}

LoadingDlg::~LoadingDlg()
{
    delete ui;
}
