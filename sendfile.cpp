#include "sendfile.h"
#include "globalvariable.h"

#include <QFile>
#include <QFileInfo>
#include <qendian.h>


SendFile::SendFile(QString path, QObject *parent)
    : QObject{parent},
    filePath(path)
{}

QString SendFile::sendFile()
{
    m_tcp = new QTcpSocket;
    m_tcp->connectToHost(ipAddress, port);

    if (!m_tcp->waitForConnected()) {
        qWarning() << "连接服务器失败: " << m_tcp->errorString();
        return "";
    }

    QFile file(filePath);

    QFileInfo info(filePath);

    int fileSize = info.size();

    int flag = -1;
    QString extension = info.suffix().toLower();
    if (extension == "png" || extension == "jpg" || extension == "jpeg" || extension == "bmp")
        flag = 2;
    else if (extension == "xlsx" || extension == "xls")
        flag = 1;
    else {
        qDebug() << "未知的文件类型!";
        return "";
    }

    file.open(QFile::ReadOnly);

    // 发送要发送的数据的大小
    uint32_t temp0 = qToBigEndian(fileSize);
    QByteArray data0((char*)&temp0, 4);
    m_tcp->write(data0);
    m_tcp->flush();

    // 发送标志位
    uint32_t temp1 = qToBigEndian(flag);
    QByteArray data1((char*)&temp1, 4);
    m_tcp->write(data1);
    m_tcp->flush();

    QByteArray fileData = file.readAll();
    m_tcp->write(fileData);
    m_tcp->flush();

    file.close();

    // 等待服务器的响应
    if (!m_tcp->waitForReadyRead()) {
        qWarning() << "未接收到服务器的数据: " << m_tcp->errorString();
        return "";
    }

    // 接收服务端传输的文件路径
    QByteArray encodedData = m_tcp->readAll();
    QString sPath = QString::fromUtf8(encodedData);

    m_tcp->close();
    m_tcp->deleteLater();

    return sPath;
}
