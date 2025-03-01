#include "httpmgr.h"
#include "httpmgr.h"
#include <QtNetwork/qnetworkreply.h>

HttpMgr::HttpMgr() {
    connect(this, &HttpMgr::sig_http_finish, this, &HttpMgr::slot_http_finish);
}

void HttpMgr::PostHttpReq(QUrl url, QJsonObject json, ReqId reqId, Modules mod) {
    QByteArray data = QJsonDocument(json).toJson();
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setHeader(QNetworkRequest::ContentLengthHeader, QByteArray::number((data.length())));

    auto self = shared_from_this();
    QNetworkReply *reply = manager_.post(request, data);
    // QNetworkReply *reply = manager_.get(request);
    QObject::connect(reply, &QNetworkReply::finished, [self, reply, reqId, mod]() {
        if (reply->error() != QNetworkReply::NoError) {
            qDebug() << reply->errorString() << "haha";

            //发送信号通知完成
            emit self->sig_http_finish(reqId,"",ErrorCodes::ERR_NETWORK, mod);
            reply->deleteLater();
            return;
        }

        qDebug() << "can send" ;
        //无错误
        QString res = reply->readAll();

        //发送信号通知完成
        emit self->sig_http_finish(reqId, res, ErrorCodes::SUCCESS, mod);
        reply->deleteLater();
        return;
    });
}

HttpMgr::~HttpMgr() {
}

void HttpMgr::slot_http_finish(ReqId id, QString res, ErrorCodes err, Modules mod) {
    if (mod == Modules::REGISTERMOD) {
        //发送信号通知指定模块https响应完成
        emit sig_reg_mod_finish(id, res, err, mod);
    }
}
