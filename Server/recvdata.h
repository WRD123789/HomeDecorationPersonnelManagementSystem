#ifndef RECVDATA_H
#define RECVDATA_H

#include <QThread>

class RecvData : public QThread
{
    Q_OBJECT
public:
    explicit RecvData(qintptr sock, QObject *parent = nullptr);
    ~RecvData();

protected:
    void run() override;

private:
    qintptr m_sock;
    QByteArray data;
    int count;
    int total;
    int flag;

signals:
    void over();
};

#endif // RECVDATA_H
