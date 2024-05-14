#include "recvfile.h"
#include "globalvariable.h"

#include <QPixmap>
#include <qendian.h>

RecvFile::RecvFile(QString sPath, QObject *parent)
    : QObject{parent},
    sPath(sPath)
{}

QByteArray RecvFile::recvFile()
{
    m_tcp = new QTcpSocket;
    m_tcp->connectToHost(ipAddress, port);

    if (!m_tcp->waitForConnected()) {
        qWarning() << "连接服务器失败: " << m_tcp->errorString();
        return "";
    }

    if (sPath == "") {
        return "";
    }

    QByteArray path = sPath.toUtf8();

    // 发送要发送的数据的大小
    int dataSize = path.size();
    uint32_t temp0 = qToBigEndian(dataSize);
    QByteArray data0((char*)&temp0, 4);
    m_tcp->write(data0);
    m_tcp->flush();

    // 发送标志位
    int flag = 0;
    uint32_t temp1 = qToBigEndian(flag);
    QByteArray data1((char*)&temp1, 4);
    m_tcp->write(data1);
    m_tcp->flush();

    // 将文件的路径发送给服务端
    m_tcp->write(path);
    m_tcp->flush();

    // 等待服务器的响应
    if (!m_tcp->waitForReadyRead()) {
        qWarning() << "未接收到服务器的数据: " << m_tcp->errorString();
        return "";
    }

    QByteArray temp = m_tcp->read(sizeof(int));
    int total = qFromBigEndian(*(int*)temp.data());
    int count = 0;

    qDebug() << QString("total: %1").arg(total);

    QByteArray data;
    while (m_tcp->waitForReadyRead()) {
        // 接收数据
        QByteArray part = m_tcp->readAll();
        data.append(part);
        count += part.size();

        if (count == total)
            break;
    }

    qDebug() << QString("data: %1").arg(data.size());

    m_tcp->close();
    m_tcp->deleteLater();

    return data;
}
