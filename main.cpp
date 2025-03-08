#include "mainwindow.h"
#include <QFile>
#include<QSettings>
#include<QDir>
#include <QDebug>
/******************************************************************************
     *
     * @file       main.cpp
     * @brief      XXXX Function
     *
     * @author     shuai
     * @date       2025/02/19
     * @history
     ***************************************************************************/
#include <QApplication>
#include<QString>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile qss("style/stylesheet.qss");
    if(qss.open(QFile::ReadOnly)){
        qDebug("open success");
        QString style = QLatin1String(qss.readAll());
        a.setStyleSheet(style);
        qss.close();
    }else{
        qDebug("Open failed");
    }

    QString fileName = "config.ii";
    QString app_path = QCoreApplication::applicationDirPath();
    QString config_path = QDir::toNativeSeparators(app_path + QDir::separator() + fileName);
    QSettings settings(config_path, QSettings::IniFormat);
    QString gate_host = settings.value("GateServer/host").toString();
    QString gate_port = settings.value("GateServer/port").toString();

    gate_url_prefix = "http://" + gate_host + ":" + gate_port;

    MainWindow w;
    w.show();
    return a.exec();
}
