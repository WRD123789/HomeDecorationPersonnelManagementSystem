#ifndef SENDFILE_H
#define SENDFILE_H

#include <QObject>
#include <QTcpSocket>

class SendFile : public QObject
{
    Q_OBJECT
public:
    explicit SendFile(QString path, QObject *parent = nullptr);

    // 发送文件
    QString sendFile();

private:
    QTcpSocket *m_tcp;
    QString filePath;
};

#endif // SENDFILE_H
