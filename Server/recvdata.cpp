#include "recvdata.h"

#include <QFileInfo>
#include <QFile>
#include <QTcpSocket>
#include <QImage>
#include <QDateTime>
#include <QRandomGenerator>
#include <QUrl>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlDatabase>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDir>

RecvData::RecvData(qintptr sock, QObject *parent)
    : QThread{parent},
    count(0),
    total(0),
    flag(-1),
    m_sock(sock)
{

}

RecvData::~RecvData()
{
    qDebug() << "~~~~~~";
}

void RecvData::run()
{
    qDebug() << "子线程1:" << QThread::currentThreadId();

    QTcpSocket *m_tcp = new QTcpSocket;
    m_tcp->setSocketDescriptor(m_sock);

    // 在子线程中创建一个 QObject 子类对象作为接收者
    QObject* receiverObj = new QObject();
    receiverObj->moveToThread(QThread::currentThread()); // 将接收者对象移动到当前线程

    // 接收数据
    connect(m_tcp, &QTcpSocket::readyRead, receiverObj, [=](){
        qDebug() << "子线程2: " << QThread::currentThreadId();
        qDebug() << QString("count: %1").arg(count);
        if (count == 0) {
            QByteArray temp = m_tcp->read(sizeof(int));
            total = qFromBigEndian(*(int*)temp.data());
        }

        // 判断是读取文件、写文件还是查询数据库
        // 0 表示读取文件, 1 表示存 Execl 文件, 2 表示存图片, 3 表示查询数据库
        if (flag == -1) {
            QByteArray temp = m_tcp->read(sizeof(int));
            flag = qFromBigEndian(*(int*)temp.data());
        }

        // 读取剩余的数据
        QByteArray all = m_tcp->readAll();
        qDebug() << all.size();
        data.append(all);
        count += all.size();

        qDebug() << QString("count: %1").arg(count) <<
            QString("total: %1").arg(total) << QString("flag: %1").arg(flag);

        // 判断数据是否接收完毕
        if (count == total) {
            // 读取文件
            if (flag == 0) {
                QString filePath = QString::fromUtf8(data);

                qDebug() << filePath;

                QFile file(filePath);

                if (!file.open(QIODevice::ReadOnly)) {
                    qDebug() << "Failed to open file" << filePath;
                    return;
                }

                // 发送要发送的数据的大小
                QFileInfo info(filePath);
                int fileSize = info.size();
                uint32_t temp0 = qToBigEndian(fileSize);
                QByteArray data0((char*)&temp0, 4);
                m_tcp->write(data0);
                m_tcp->flush();

                // 读取文件数据
                const int chunkSize = 1024;
                while (!file.atEnd()) {
                    QByteArray chunk = file.read(chunkSize); // 读取数据块
                    m_tcp->write(chunk); // 发送数据块
                    m_tcp->flush();
                }

                file.close();
            } else if (flag == 1) {
                // 存储 Execl 文件
                // 根据时间戳和随机数来生成文件名;
                QString fileName = QString("%1%2").arg(QDateTime::currentDateTime().toMSecsSinceEpoch())
                                       .arg(QRandomGenerator::global()->generate());

                QString relativePath = QString("tables/%1.xlsx").arg(fileName);
                QString relativeDir = QString("tables");
                QString currentDir = QDir::currentPath();
                QString filePath = QDir::cleanPath(currentDir + QDir::separator()
                                                   + relativePath);
                QString dirPath = (currentDir + QDir::separator()
                                   + relativeDir);

                QDir dir(dirPath);
                if (!dir.exists()) {
                    // 如果不存在，则尝试创建目录
                    if (!dir.mkpath(dirPath)) {
                        qWarning() << "创建文件夹失败!";
                        return;
                    }
                    qDebug() << "创建文件夹成功!";
                }

                QFile file(filePath);
                if (!file.open(QIODevice::WriteOnly)) {
                    qDebug() << "Failed to open file for writing";
                    return;
                }

                file.write(data);
                file.close();

                // 将文件的路径发送给客户端
                m_tcp->write(filePath.toUtf8());
                m_tcp->flush();
            } else if (flag == 2){
                // 存储图片
                // 将数据存储在本地
                QImage image;
                image.loadFromData(data);

                // 根据时间戳和随机数来生成文件名
                QString fileName = QString("%1%2").arg(QDateTime::currentDateTime().toMSecsSinceEpoch())
                                     .arg(QRandomGenerator::global()->generate());

                // 根据图片格式设置文件扩展名
                QString format;
                switch (image.format()) {
                case QImage::Format_RGB32:
                case QImage::Format_ARGB32:
                    format = "jpg";
                    break;
                case QImage::Format_RGB888:
                case QImage::Format_Indexed8:
                    format = "png";
                    break;
                default:
                    qDebug() << "Unsupported image format";
                    return;
                }

                QString relativePath = QString("images/%1.").arg(fileName) + format;
                QString relativeDir = QString("images");
                QString currentDir = QDir::currentPath();
                QString filePath = QDir::cleanPath(currentDir + QDir::separator()
                                                   + relativePath);
                QString dirPath = (currentDir + QDir::separator()
                                   + relativeDir);

                QDir dir(dirPath);
                if (!dir.exists()) {
                    // 如果不存在，则尝试创建目录
                    if (!dir.mkpath(dirPath)) {
                        qWarning() << "创建文件夹失败!";
                        return;
                    }
                    qDebug() << "创建文件夹成功!";
                }

                QFile file(filePath);
                if (!file.open(QIODevice::WriteOnly)) {
                    qDebug() << "Failed to open file for writing" << file.errorString();
                    return;
                }

                // 将图片数据写入文件
                file.write(data);
                file.close();

                // 将文件的路径发送给客户端
                m_tcp->write(filePath.toUtf8());
                m_tcp->flush();
            } else {
                // 连接数据库
                QSqlDatabase db = QSqlDatabase::addDatabase(
                    "QMYSQL", QString::number(reinterpret_cast<int>
                                              (QThread::currentThreadId())));
                db.setHostName("127.0.0.1");
                db.setPort(3306);
                db.setDatabaseName("home_decoration");
                db.setUserName("root");
                db.setPassword("12345678");
                if(!db.open())
                    qDebug() << "错误";

                // 查询数据库
                QString sql = QString::fromUtf8(data);

                qDebug() << sql;

                QSqlQuery query(sql, db);
                query.exec();

                // 将数据库的查询结果转换为 Json 格式
                QJsonArray jsonArray;
                while (query.next()) {
                    QJsonObject jsonObject;
                    for (int i = 0; i < query.record().count(); ++i) {
                        QString fieldName = query.record().fieldName(i);
                        QVariant value = query.value(i);
                        jsonObject[fieldName] = QJsonValue::fromVariant(value);
                    }
                    jsonArray.append(jsonObject);
                }

                if (!jsonArray.isEmpty()) {
                    QJsonDocument jsonDoc(jsonArray);
                    QByteArray jsonData = jsonDoc.toJson();

                    // 将 Json 格式的数据传输给客户端
                    m_tcp->write(jsonData);
                    m_tcp->flush();
                }

                db.close();
            }

            // 关闭连接
            m_tcp->close();
            m_tcp->deleteLater();

            emit over();
        }
    });

    exec();
}
