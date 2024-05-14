#ifndef RECVFILE_H
#define RECVFILE_H

#include <QObject>
#include <QTcpSocket>

class RecvFile : public QObject
{
    Q_OBJECT
public:
    explicit RecvFile(QString sPath, QObject *parent = nullptr);

    QByteArray recvFile();

private:
    QTcpSocket *m_tcp;
    QString sPath;
};

#endif // RECVFILE_H
