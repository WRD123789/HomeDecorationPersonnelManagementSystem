#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QTcpServer>

class MyTcpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit MyTcpServer(QObject *parent = nullptr);


protected:
    virtual void incomingConnection(qintptr socketDescriptor);

signals:
    void newDescriptor(qintptr sock);
};

#endif // MYTCPSERVER_H
