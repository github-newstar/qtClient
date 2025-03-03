#ifndef TCPMHR_H
#define TCPMHR_H

#include <QObject>

class TcpMhr : public QObject
{
    Q_OBJECT
public:
    explicit TcpMhr(QObject *parent = nullptr);

signals:

};

#endif // TCPMHR_H
