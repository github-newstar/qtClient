#include "tcpmgr.h"
#include "usermgr.h"
#include <QAbstractSocket>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include "global.h"
TcpMgr::~TcpMgr() {
}

TcpMgr::TcpMgr(): host_("") , port_(0) , b_recv_penging_(false) , messageId_(0) , messageLen_(0)
{

    connect(&socket_, &QTcpSocket::connected,   [&](){
        qDebug() << "connected to server ";
        emit sig_con_success(true);
    });
    
    QObject::connect(&socket_, &QTcpSocket::readyRead,  [&](){
        //有数据时读取所有数据
        buffer_.append(socket_.readAll());
        
        QDataStream stream(&buffer_, QIODevice::ReadOnly);
        stream.setVersion(QDataStream::Qt_5_0);
        
        forever{
            if(!b_recv_penging_){
                //数据不够直接等
                if(buffer_.size() < static_cast<int>(sizeof(quint16) *2)){
                    return;
                }
                
                //从缓冲区中读消息id核长度
                stream >> messageId_ >> messageLen_;
                
                //从缓冲区中移除头部数据
                buffer_ = buffer_.mid(sizeof(quint16) * 2);
                
                qDebug() << "message id : " << messageId_ << "message len : " << messageLen_ ;
            }
            //检查剩余长度是否满足消息体长度
            if(buffer_.size() < messageLen_){
                b_recv_penging_ = true;
                return;
            }
            //长度的足够 开始读
            b_recv_penging_ = false;
            
            QByteArray messageBody = buffer_.mid(0, messageLen_);
            qDebug() <<"receive message body" << messageBody;
            buffer_ = buffer_.mid(messageLen_);
            
            //处理消息
            handleMsg(ReqId(messageId_), messageLen_, messageBody);
        }
        
    });
    //错误处理
/*      QObject::connect(&socket_,
                       QOverload<QAbstractSocket::SocketError>::of(
                           &QTcpSocket::errorOccurred),
                       [&](QAbstractSocket::SocketError socketError) {
                           Q_UNUSED(socketError)
                           qDebug() << "Error:" << socket_.errorString();
                       }) */;
    
     QObject::connect(&socket_, static_cast<void (QTcpSocket::*)(QTcpSocket::SocketError)>(&QTcpSocket::error),
                       [&](QTcpSocket::SocketError socketError) {
          qDebug() << "Error:" <<socket_.errorString() ;
          switch (socketError) {
              case QTcpSocket::ConnectionRefusedError:
                  qDebug() << "Connection Refused!";
                  emit sig_con_success(false);
                  break;
              case QTcpSocket::RemoteHostClosedError:
                  qDebug() << "Remote Host Closed Connection!";
                  break;
              case QTcpSocket::HostNotFoundError:
                  qDebug() << "Host Not Found!";
                  emit sig_con_success(false);
                  break;
              case QTcpSocket::SocketTimeoutError:
                  qDebug() << "Connection Timeout!";
                  emit sig_con_success(false);
                  break;
              case QTcpSocket::NetworkError:
                  qDebug() << "Network Error!";
                  break;
              default:
                  qDebug() << "Other Error!";
                  break;
          }
    });
     QObject::connect(&socket_, &QTcpSocket::disconnected, [](){
        qDebug() << "disconnected frome server " ;
     });
     //连接发送数据信号核接受数据槽函数
     QObject::connect(this, &TcpMgr::sig_send_data,&TcpMgr::slot_send_data);
     
     //初始化回调函数
     initHandlers();
}

void TcpMgr::initHandlers() {
    handlers_[ReqId::ID_CHAST_LOGIN_RSP] = [this](ReqId id, int len , QByteArray data){
        qDebug() << "handle id is " << id << " data is " << data;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
        
        //检查json解析
        if(jsonDoc.isNull() == true){
            qDebug() << "json prase failed, is not json ";
            return;
        }
        
        QJsonObject jsonObj = jsonDoc.object();
        if(!jsonObj.contains("error")){
            int err = ErrorCodes::ERR_JSON;
            qDebug() << "json prase failed, don't contain error";
            emit sig_login_failed(err);
            return;
        }
        
        int err = jsonObj["error"].toInt();
        if(err != ErrorCodes::SUCCESS){
            qDebug() << "login failed , err is" << err;
            emit sig_login_failed(err);
            return;
        }
        
        UserMgr::GetInstance()->SetUid(jsonObj["uid"].toInt());
        UserMgr::GetInstance()->SetName(jsonObj["name"].toString());
        UserMgr::GetInstance()->SetToken(jsonObj["token"].toString());
        
        emit TcpMgr::GetInstance()->sig_switch_chatDlg();
    };
}

void TcpMgr::handleMsg(ReqId id, int len, QByteArray data) {
    auto iter = handlers_.find(id);
    if(iter == handlers_.end()){
        qDebug() << "not found id " << id ;
        return;
    }
    //调用回调函数
    iter.value()(id, len , data);
}

void TcpMgr::slot_tcp_connect(ServerInfo serverInfo) {
    qDebug()<< "receive tcp connect signal";
    // 尝试连接到服务器
    qDebug() << "Connecting to server...";
    host_ = serverInfo.Host;
    port_ = static_cast<uint16_t>(serverInfo.Port.toInt());
    socket_.connectToHost(serverInfo.Host, port_);
}

void TcpMgr::slot_send_data(ReqId reqId, QString data) {
    uint16_t id = reqId;
    
    //字符utf-8编码
    QByteArray dataBytes = data.toUtf8();
    
    //计算长度
    quint16 len = static_cast<quint16>(data.size());
    
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    
    out.setByteOrder(QDataStream::BigEndian);
    
    out << id << len;
    block.append(dataBytes);
    
    //发送数据
    socket_.write(block);
}
