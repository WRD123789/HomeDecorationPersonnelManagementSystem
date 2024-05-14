#include "mytcpserver.h"

MyTcpServer::MyTcpServer(QObject *parent)
    : QTcpServer{parent}
{

}

// 有新连接时该函数自动被调用
void MyTcpServer::incomingConnection(qintptr socketDescriptor)
{
    emit newDescriptor(socketDescriptor);
}
