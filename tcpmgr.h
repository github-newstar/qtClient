#ifndef TCPMHR_H
#define TCPMHR_H

#include <QObject>
#include <QByteArray>
#include <QMap>
#include "singleton.h"
#include "global.h"
#include <functional>
#include <QTcpSocket>


class TcpMgr : public QObject, public Singleton<TcpMgr> , public std::enable_shared_from_this<TcpMgr>
{
    Q_OBJECT
        friend class Singleton<TcpMgr>;
public:
    ~TcpMgr();
private:
    TcpMgr();
    void initHandlers();
    
    void handleMsg(ReqId id, int len , QByteArray data);

    QTcpSocket socket_;
    QString host_;
    uint16_t port_;

    QByteArray buffer_;
    bool b_recv_penging_;
    quint16 messageId_;
    quint16 messageLen_;

    QMap<ReqId, std::function<void(ReqId, int , QByteArray)>> handlers_;
public slots:
    void slot_tcp_connect(ServerInfo);
    void slot_send_data(ReqId reqId, QString data);
signals:
    void sig_con_success(bool success);
    void sig_send_data(ReqId reqId, QString data);
    void sig_switch_chatDlg();
    void sig_login_failed(int errCode);
};

#endif // TCPMHR_H
