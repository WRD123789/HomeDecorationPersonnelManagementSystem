#include "accountmodel.h"
#include "globalvariable.h"

#include <QVariant>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

#define ACC_ID       "id"
#define ACC_NUMBER   "account_number"
#define ACC_PASSWORD "password"
#define ACC_IDENTITY "identity"

AccountModel::AccountModel() {}

Account AccountModel::queryByNumber(QString &num)
{
    // 尝试连接服务器
    QTcpSocket socket;


    socket.connectToHost(ipAddress, port);

    if (!socket.waitForConnected()) {
        qWarning() << "连接服务器失败: " << socket.errorString();
        return Account();
    }

    QString sql = QString("SELECT * "
                          "FROM account "
                          "WHERE `account_number` = '%1'").arg(num);
    QByteArray requestData = sql.toUtf8();

    // 发送要发送的数据的大小
    int dataSize = requestData.size();
    uint32_t temp0 = qToBigEndian(dataSize);
    QByteArray data0((char*)&temp0, 4);
    socket.write(data0);
    socket.flush();

    // 发送标志位
    int flag = 3;
    uint32_t temp1 = qToBigEndian(flag);
    QByteArray data1((char*)&temp1, 4);
    socket.write(data1);
    socket.flush();

    // 将 sql 查询交给服务端处理
    socket.write(requestData);
    socket.flush();

    // 等待服务器的响应
    if (!socket.waitForReadyRead()) {
        qWarning() << "未接收到服务器的数据: " << socket.errorString();
        return Account();
    }

    QByteArray responseData = socket.readAll();

    // 解析 Json 数据
    QJsonDocument jsonResponse = QJsonDocument::fromJson(responseData);
    if (!jsonResponse.isArray()) {
        qWarning() << "无效的 Json 数据!";
        return Account();
    }

    QJsonArray jsonArray = jsonResponse.array();
    for (const auto &jsonObj : jsonArray) {
        if (jsonObj.isObject()) {
            QJsonObject obj = jsonObj.toObject();

            // 处理查询结果
            Account account;
            account.setId(obj.value(ACC_ID).toString());
            account.setAccount(obj.value(ACC_NUMBER).toString());
            account.setPassword(obj.value(ACC_PASSWORD).toString());
            account.setIdentity(obj.value(ACC_IDENTITY).toString());
            return account;
        }
    }
    return Account();
}

Account AccountModel::queryById(QString id)
{
    // 尝试连接服务器
    QTcpSocket socket;
    socket.connectToHost(ipAddress, port);

    if (!socket.waitForConnected()) {
        qWarning() << "连接服务器失败: " << socket.errorString();
        return Account();
    }

    QString sql = QString("SELECT * "
                          "FROM account "
                          "WHERE id = '%1'").arg(id);
    QByteArray requestData = sql.toUtf8();

    // 发送要发送的数据的大小
    int dataSize = requestData.size();
    uint32_t temp0 = qToBigEndian(dataSize);
    QByteArray data0((char*)&temp0, 4);
    socket.write(data0);
    socket.flush();

    // 发送标志位
    int flag = 3;
    uint32_t temp1 = qToBigEndian(flag);
    QByteArray data1((char*)&temp1, 4);
    socket.write(data1);
    socket.flush();

    // 将 sql 查询交给服务端处理
    socket.write(requestData);
    socket.flush();

    // 等待服务器的响应
    if (!socket.waitForReadyRead()) {
        qWarning() << "未接收到服务器的数据: " << socket.errorString();
        return Account();
    }

    QByteArray responseData = socket.readAll();

    // 解析 Json 数据
    QJsonDocument jsonResponse = QJsonDocument::fromJson(responseData);
    if (!jsonResponse.isArray()) {
        qWarning() << "无效的 Json 数据!";
        return Account();
    }

    QJsonArray jsonArray = jsonResponse.array();
    for (const auto &jsonObj : jsonArray) {
        if (jsonObj.isObject()) {
            QJsonObject obj = jsonObj.toObject();

            // 处理查询结果
            Account account;
            account.setId(obj.value(ACC_ID).toString());
            account.setAccount(obj.value(ACC_NUMBER).toString());
            account.setPassword(obj.value(ACC_PASSWORD).toString());
            account.setIdentity(obj.value(ACC_IDENTITY).toString());
            return account;
        }
    }
    return Account();
}

bool AccountModel::insert(Account &acc)
{
    // 尝试连接服务器
    QTcpSocket socket;
    socket.connectToHost(ipAddress, port);

    if (!socket.waitForConnected()) {
        qWarning() << "连接服务器失败: " << socket.errorString();
        return false;
    }

    QString sql = QString("INSERT INTO account "
                          "VALUES ('%1', '%2', '%3', '%4')").arg(
                          acc.getId(),
                          acc.getAccount(),
                          acc.getPassword(),
                          acc.getIdentity());
    QByteArray requestData = sql.toUtf8();

    // 发送要发送的数据的大小
    int dataSize = requestData.size();
    uint32_t temp0 = qToBigEndian(dataSize);
    QByteArray data0((char*)&temp0, 4);
    socket.write(data0);
    socket.flush();

    // 发送标志位
    int flag = 3;
    uint32_t temp1 = qToBigEndian(flag);
    QByteArray data1((char*)&temp1, 4);
    socket.write(data1);
    socket.flush();

    // 将 sql 查询交给服务端处理
    socket.write(requestData);
    socket.flush();

    return true;
}

bool AccountModel::remove(Account &acc)
{
    // 尝试连接服务器
    QTcpSocket socket;
    socket.connectToHost(ipAddress, port);

    if (!socket.waitForConnected()) {
        qWarning() << "连接服务器失败: " << socket.errorString();
        return false;
    }

    QString sql = QString("DELETE FROM account "
                          "WHERE id = '%1'").arg(acc.getId());
    QByteArray requestData = sql.toUtf8();

    // 发送要发送的数据的大小
    int dataSize = requestData.size();
    uint32_t temp0 = qToBigEndian(dataSize);
    QByteArray data0((char*)&temp0, 4);
    socket.write(data0);
    socket.flush();

    // 发送标志位
    int flag = 3;
    uint32_t temp1 = qToBigEndian(flag);
    QByteArray data1((char*)&temp1, 4);
    socket.write(data1);
    socket.flush();

    // 将 sql 查询交给服务端处理
    socket.write(requestData);
    socket.flush();

    return true;
}

bool AccountModel::update(Account &acc)
{
    // 尝试连接服务器
    QTcpSocket socket;
    socket.connectToHost(ipAddress, port);

    if (!socket.waitForConnected()) {
        qWarning() << "连接服务器失败: " << socket.errorString();
        return false;
    }

    QString sql = QString("UPDATE account "
                          "SET "
                          "password = '%1', "
                          "identity = '%2' "
                          "WHERE `account_number` = '%3'").arg(
                          acc.getPassword(),
                          acc.getIdentity(),
                          acc.getAccount());
    QByteArray requestData = sql.toUtf8();

    // 发送要发送的数据的大小
    int dataSize = requestData.size();
    uint32_t temp0 = qToBigEndian(dataSize);
    QByteArray data0((char*)&temp0, 4);
    socket.write(data0);
    socket.flush();

    // 发送标志位
    int flag = 3;
    uint32_t temp1 = qToBigEndian(flag);
    QByteArray data1((char*)&temp1, 4);
    socket.write(data1);
    socket.flush();

    // 将 sql 查询交给服务端处理
    socket.write(requestData);
    socket.flush();

    return true;
}

QVector<Account> AccountModel::queryAll()
{
    QVector<Account> accVec{};

    // 尝试连接服务器
    QTcpSocket socket;
    socket.connectToHost(ipAddress, port);

    if (!socket.waitForConnected()) {
        qWarning() << "连接服务器失败: " << socket.errorString();
        return accVec;
    }

    QString sql = QString("SELECT * "
                          "FROM account");
    QByteArray requestData = sql.toUtf8();

    // 发送要发送的数据的大小
    int dataSize = requestData.size();
    uint32_t temp0 = qToBigEndian(dataSize);
    QByteArray data0((char*)&temp0, 4);
    socket.write(data0);
    socket.flush();

    // 发送标志位
    int flag = 3;
    uint32_t temp1 = qToBigEndian(flag);
    QByteArray data1((char*)&temp1, 4);
    socket.write(data1);
    socket.flush();

    // 将 sql 查询交给服务端处理
    socket.write(requestData);
    socket.flush();

    // 等待服务器的响应
    if (!socket.waitForReadyRead()) {
        qWarning() << "未接收到服务器的数据: " << socket.errorString();
        return accVec;
    }

    QByteArray responseData = socket.readAll();

    // 解析 Json 数据
    QJsonDocument jsonResponse = QJsonDocument::fromJson(responseData);
    if (!jsonResponse.isArray()) {
        qWarning() << "无效的 Json 数据!";
        return accVec;
    }

    QJsonArray jsonArray = jsonResponse.array();
    for (const auto &jsonObj : jsonArray) {
        if (jsonObj.isObject()) {
            QJsonObject obj = jsonObj.toObject();

            // 处理查询结果
            Account account;
            account.setId(obj.value(ACC_ID).toString());
            account.setAccount(obj.value(ACC_NUMBER).toString());
            account.setPassword(obj.value(ACC_PASSWORD).toString());
            account.setIdentity(obj.value(ACC_IDENTITY).toString());
            accVec.push_back(account);
        }
    }

    return accVec;
}
