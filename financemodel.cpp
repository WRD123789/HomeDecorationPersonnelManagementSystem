#include "financemodel.h"
#include "globalvariable.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTcpSocket>
#include <QVariant>

#define FIN_ID      "id"
#define FIN_DEPOSIT "deposit"
#define FIN_COST    "cost"
#define FIN_AMOUNT  "amount"
#define FIN_PROJ_ID "proj_id"

FinanceModel::FinanceModel() {}

Finance FinanceModel::queryById(QString id)
{
    // 尝试连接服务器
    QTcpSocket socket;
    socket.connectToHost(ipAddress, port);

    if (!socket.waitForConnected()) {
        qWarning() << "连接服务器失败: " << socket.errorString();
        return Finance();
    }

    QString sql = QString("SELECT * "
                          "FROM finance "
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
        return Finance();
    }

    QByteArray responseData = socket.readAll();

    // 解析 Json 数据
    QJsonDocument jsonResponse = QJsonDocument::fromJson(responseData);
    if (!jsonResponse.isArray()) {
        qWarning() << "无效的 Json 数据!";
        return Finance();
    }

    QJsonArray jsonArray = jsonResponse.array();
    for (const auto &jsonObj : jsonArray) {
        if (jsonObj.isObject()) {
            QJsonObject obj = jsonObj.toObject();

            // 处理查询结果
            Finance fin;
            fin.setId(obj.value(FIN_ID).toString());
            fin.setDeposit(obj.value(FIN_DEPOSIT).toDouble());
            fin.setCost(obj.value(FIN_COST).toDouble());
            fin.setAmount(obj.value(FIN_AMOUNT).toDouble());
            fin.setProjId(obj.value(FIN_PROJ_ID).toString());
            return fin;
        }
    }
    return Finance();
}

Finance FinanceModel::queryByProjId(QString projId)
{
    // 尝试连接服务器
    QTcpSocket socket;
    socket.connectToHost(ipAddress, port);

    if (!socket.waitForConnected()) {
        qWarning() << "连接服务器失败: " << socket.errorString();
        return Finance();
    }

    QString sql = QString("SELECT * "
                          "FROM finance "
                          "WHERE `proj_id` = '%1'").arg(projId);
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
        return Finance();
    }

    QByteArray responseData = socket.readAll();

    // 解析 Json 数据
    QJsonDocument jsonResponse = QJsonDocument::fromJson(responseData);
    if (!jsonResponse.isArray()) {
        qWarning() << "无效的 Json 数据!";
        return Finance();
    }

    QJsonArray jsonArray = jsonResponse.array();
    for (const auto &jsonObj : jsonArray) {
        if (jsonObj.isObject()) {
            QJsonObject obj = jsonObj.toObject();

            // 处理查询结果
            Finance fin;
            fin.setId(obj.value(FIN_ID).toString());
            fin.setDeposit(obj.value(FIN_DEPOSIT).toDouble());
            fin.setCost(obj.value(FIN_COST).toDouble());
            fin.setAmount(obj.value(FIN_AMOUNT).toDouble());
            fin.setProjId(obj.value(FIN_PROJ_ID).toString());
            return fin;
        }
    }
    return Finance();
}

bool FinanceModel::insert(Finance &fin)
{
    // 尝试连接服务器
    QTcpSocket socket;
    socket.connectToHost(ipAddress, port);

    if (!socket.waitForConnected()) {
        qWarning() << "连接服务器失败: " << socket.errorString();
        return false;
    }

    QString sql = QString("INSERT INTO finance "
                          "VALUES ('%1', %2, %3, %4, '%5')").arg(
                          fin.getId(),
                          QString::number(fin.getDeposit(), 'f', 2),
                          QString::number(fin.getCost(), 'f', 2),
                          QString::number(fin.getAmount(), 'f', 2),
                          fin.getProjId());
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

bool FinanceModel::remove(Finance &fin)
{
    // 尝试连接服务器
    QTcpSocket socket;
    socket.connectToHost(ipAddress, port);

    if (!socket.waitForConnected()) {
        qWarning() << "连接服务器失败: " << socket.errorString();
        return false;
    }

    QString sql = QString("DELETE FROM finance "
                          "WHERE id = '%1'").arg(fin.getId());
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

bool FinanceModel::update(Finance &fin)
{
    // 尝试连接服务器
    QTcpSocket socket;
    socket.connectToHost(ipAddress, port);

    if (!socket.waitForConnected()) {
        qWarning() << "连接服务器失败: " << socket.errorString();
        return false;
    }

    QString sql = QString("UPDATE finance "
                          "SET "
                          "deposit = %1, "
                          "cost =    %2, "
                          "amount =  %3 "
                          "WHERE id = '%4'").arg(
                          QString::number(fin.getDeposit()),
                          QString::number(fin.getCost()),
                          QString::number(fin.getAmount()),
                          fin.getId());
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

QVector<Finance> FinanceModel::queryAll()
{
    QVector<Finance> finVec{};

    // 尝试连接服务器
    QTcpSocket socket;
    socket.connectToHost(ipAddress, port);

    if (!socket.waitForConnected()) {
        qWarning() << "连接服务器失败: " << socket.errorString();
        return finVec;
    }

    QString sql = QString("SELECT * "
                          "FROM finance");
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
        return finVec;
    }

    QByteArray responseData = socket.readAll();

    // 解析 Json 数据
    QJsonDocument jsonResponse = QJsonDocument::fromJson(responseData);
    if (!jsonResponse.isArray()) {
        qWarning() << "无效的 Json 数据!";
        return finVec;
    }

    QJsonArray jsonArray = jsonResponse.array();
    for (const auto &jsonObj : jsonArray) {
        if (jsonObj.isObject()) {
            QJsonObject obj = jsonObj.toObject();

            // 处理查询结果
            Finance fin;
            fin.setId(obj.value(FIN_ID).toString());
            fin.setDeposit(obj.value(FIN_DEPOSIT).toDouble());
            fin.setCost(obj.value(FIN_COST).toDouble());
            fin.setAmount(obj.value(FIN_AMOUNT).toDouble());
            fin.setProjId(obj.value(FIN_PROJ_ID).toString());
            finVec.push_back(fin);
        }
    }

    return finVec;
}

QVector<Finance> FinanceModel::queryAllUnSolved()
{   
    QVector<Finance> finVec{};

    // 尝试连接服务器
    QTcpSocket socket;
    socket.connectToHost(ipAddress, port);

    if (!socket.waitForConnected()) {
        qWarning() << "连接服务器失败: " << socket.errorString();
        return finVec;
    }

    QString sql = QString("SELECT A.id, A.deposit, A.cost, A.amount, A.proj_id "
                          "FROM finance AS A "
                          "INNER JOIN project AS B ON A.proj_id = B.id "
                          "WHERE B.progress IN ('业务员沟通', '设计总监分配', '量房设计', "
                          "'平面布置图设计', '合同设计', '定金交付')");
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
        return finVec;
    }

    QByteArray responseData = socket.readAll();

    // 解析 Json 数据
    QJsonDocument jsonResponse = QJsonDocument::fromJson(responseData);
    if (!jsonResponse.isArray()) {
        qWarning() << "无效的 Json 数据!";
        return finVec;
    }

    QJsonArray jsonArray = jsonResponse.array();
    for (const auto &jsonObj : jsonArray) {
        if (jsonObj.isObject()) {
            QJsonObject obj = jsonObj.toObject();

            // 处理查询结果
            Finance fin;
            fin.setId(obj.value(FIN_ID).toString());
            fin.setDeposit(obj.value(FIN_DEPOSIT).toDouble());
            fin.setCost(obj.value(FIN_COST).toDouble());
            fin.setAmount(obj.value(FIN_AMOUNT).toDouble());
            fin.setProjId(obj.value(FIN_PROJ_ID).toString());
            finVec.push_back(fin);
        }
    }

    return finVec;
}

