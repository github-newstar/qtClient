#ifndef HTTPMGR_H
#define HTTPMGR_H
#include "singleton.h"
#include "QString"
#include <QString>
#include <QUrl>
#include <QObject>
#include <QtNetwork/qnetworkaccessmanager.h>
#include <QJsonObject>
#include <QJsonDocument>
#include<QUrl>

class HttpMgr : public QObject, public Singleton<HttpMgr> , public  std::enable_shared_from_this<HttpMgr>
{
    Q_OBJECT
public:
    ~HttpMgr();
    void PostHttpReq(QUrl url, QJsonObject json, ReqId reqId, Modules mod);
private slots:
    void slot_http_finish(ReqId id, QString res, ErrorCodes err, Modules mod);
public:
    friend class Singleton<HttpMgr>;
    HttpMgr();
    QNetworkAccessManager manager_;

    signals:
    void sig_http_finish(ReqId id, QString res, ErrorCodes err, Modules mod);
    void sig_reg_mod_finish(ReqId id, QString res, ErrorCodes err);
    void sig_reset_mod_finish(ReqId id, QString res, ErrorCodes err);
    void sig_login_mod_finish(ReqId id, QString res, ErrorCodes err);
};


#endif // HTTPMGR_H
