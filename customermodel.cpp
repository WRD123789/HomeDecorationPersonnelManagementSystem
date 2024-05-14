#include "customermodel.h"
#include "accountinstance.h"
#include "globalvariable.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTcpSocket>
#include <QVariant>

#define CUS_ID      "id"
#define CUS_NAME    "name"
#define CUS_AGE     "age"
#define CUS_GENDER  "gender"
#define CUS_PHONE   "phone"
#define CUS_PROJ_ID "proj_id"

CustomerModel::CustomerModel() {}

Customer CustomerModel::queryById(QString id)
{
    // 尝试连接服务器
    QTcpSocket socket;
    socket.connectToHost(ipAddress, port);

    if (!socket.waitForConnected()) {
        qWarning() << "连接服务器失败: " << socket.errorString();
        return Customer();
    }

    QString sql = QString("SELECT * "
                          "FROM customer "
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
            return Customer();
    }

    QByteArray responseData = socket.readAll();

    // 解析 Json 数据
    QJsonDocument jsonResponse = QJsonDocument::fromJson(responseData);
    if (!jsonResponse.isArray()) {
        qWarning() << "无效的 Json 数据!";
        return Customer();
    }

    QJsonArray jsonArray = jsonResponse.array();
    for (const auto &jsonObj : jsonArray) {
        if (jsonObj.isObject()) {
            QJsonObject obj = jsonObj.toObject();

            // 处理查询结果
            Customer customer;
            customer.setId(obj.value(CUS_ID).toString());
            customer.setAge(obj.value(CUS_AGE).toInt());
            customer.setName(obj.value(CUS_NAME).toString());
            customer.setGender(obj.value(CUS_GENDER).toString());
            customer.setPhone(obj.value(CUS_PHONE).toString());
            customer.setProjId(obj.value(CUS_PROJ_ID).toString());
            return customer;
        }
    }
    return Customer();
}

Customer CustomerModel::queryByProjId(QString id)
{
    // 尝试连接服务器
    QTcpSocket socket;
    socket.connectToHost(ipAddress, port);

    if (!socket.waitForConnected()) {
        qWarning() << "连接服务器失败: " << socket.errorString();
        return Customer();
    }

    QString sql = QString("SELECT * "
                          "FROM customer "
                          "WHERE `proj_id` = '%1'").arg(id);
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
            return Customer();
    }

    QByteArray responseData = socket.readAll();

    // 解析 Json 数据
    QJsonDocument jsonResponse = QJsonDocument::fromJson(responseData);
    if (!jsonResponse.isArray()) {
        qWarning() << "无效的 Json 数据!";
        return Customer();
    }

    QJsonArray jsonArray = jsonResponse.array();
    for (const auto &jsonObj : jsonArray) {
        if (jsonObj.isObject()) {
            QJsonObject obj = jsonObj.toObject();

            // 处理查询结果
            Customer customer;
            customer.setId(obj.value(CUS_ID).toString());
            customer.setAge(obj.value(CUS_AGE).toInt());
            customer.setName(obj.value(CUS_NAME).toString());
            customer.setGender(obj.value(CUS_GENDER).toString());
            customer.setPhone(obj.value(CUS_PHONE).toString());
            customer.setProjId(obj.value(CUS_PROJ_ID).toString());
            return customer;
        }
    }
    return Customer();
}

bool CustomerModel::insert(Customer &cus)
{
    // 尝试连接服务器
    QTcpSocket socket;
    socket.connectToHost(ipAddress, port);

    if (!socket.waitForConnected()) {
        qWarning() << "连接服务器失败: " << socket.errorString();
        return false;
    }

    QString sql = QString("INSERT INTO customer "
                          "VALUES ('%1', '%2', %3, '%4', '%5', '%6')").arg(
                          cus.getId(),
                          cus.getName(),
                          QString::number(cus.getAge()),
                          cus.getGender(),
                          cus.getPhone(),
                          cus.getProjId());
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

bool CustomerModel::remove(Customer &cus)
{
    // 尝试连接服务器
    QTcpSocket socket;
    socket.connectToHost(ipAddress, port);

    if (!socket.waitForConnected()) {
        qWarning() << "连接服务器失败: " << socket.errorString();
        return false;
    }

    QString sql = QString("DELETE FROM customer "
                          "WHERE id = '%1'").arg(cus.getId());
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

bool CustomerModel::update(Customer &cus)
{
    // 尝试连接服务器
    QTcpSocket socket;
    socket.connectToHost(ipAddress, port);

    if (!socket.waitForConnected()) {
        qWarning() << "连接服务器失败: " << socket.errorString();
        return false;
    }

    QString sql = QString("UPDATE customer "
                          "SET "
                          "`name` =     '%1', "
                          "`age` =       %2, "
                          "`gender` =   '%3', "
                          "`phone` =    '%4', "
                          "`proj_id` =  '%5' "
                          "WHERE id = '%6'").arg(
                          cus.getName(),
                          QString::number(cus.getAge()),
                          cus.getGender(),
                          cus.getPhone(),
                          cus.getProjId(),
                          cus.getId());
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

QVector<Customer> CustomerModel::queryAll()
{
    QVector<Customer> cusVec{};

    // 尝试连接服务器
    QTcpSocket socket;
    socket.connectToHost(ipAddress, port);

    if (!socket.waitForConnected()) {
        qWarning() << "连接服务器失败: " << socket.errorString();
        return cusVec;
    }

    QString sql = QString("SELECT * "
                          "FROM customer");
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
        return cusVec;
    }

    QByteArray responseData = socket.readAll();

    // 解析 Json 数据
    QJsonDocument jsonResponse = QJsonDocument::fromJson(responseData);
    if (!jsonResponse.isArray()) {
        qWarning() << "无效的 Json 数据!";
        return cusVec;
    }

    QJsonArray jsonArray = jsonResponse.array();
    for (const auto &jsonObj : jsonArray) {
        if (jsonObj.isObject()) {
            QJsonObject obj = jsonObj.toObject();

            // 处理查询结果
            Customer customer;
            customer.setId(obj.value(CUS_ID).toString());
            customer.setAge(obj.value(CUS_AGE).toInt());
            customer.setName(obj.value(CUS_NAME).toString());
            customer.setGender(obj.value(CUS_GENDER).toString());
            customer.setPhone(obj.value(CUS_PHONE).toString());
            customer.setProjId(obj.value(CUS_PROJ_ID).toString());
            cusVec.push_back(customer);
        }
    }

    return cusVec;
}

QVector<Customer> CustomerModel::queryAllByCurId()
{
    QVector<Customer> cusVec{};

    QString curId = AccountInstance::instance().getId();

    // 尝试连接服务器
    QTcpSocket socket;
    socket.connectToHost(ipAddress, port);

    if (!socket.waitForConnected()) {
        qWarning() << "连接服务器失败: " << socket.errorString();
        return cusVec;
    }

    QString sql = QString("SELECT A.id, "
                          "A.name, "
                          "A.age, "
                          "A.gender, "
                          "A.phone, "
                          "A.proj_id "
                          "FROM customer AS A "
                          "INNER JOIN project AS B ON A.proj_id = B.id "
                          "WHERE B.salesman_id = '%1'").arg(curId);
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
        return cusVec;
    }

    QByteArray responseData = socket.readAll();

    // 解析 Json 数据
    QJsonDocument jsonResponse = QJsonDocument::fromJson(responseData);
    if (!jsonResponse.isArray()) {
        qWarning() << "无效的 Json 数据!";
        return cusVec;
    }

    QJsonArray jsonArray = jsonResponse.array();
    for (const auto &jsonObj : jsonArray) {
        if (jsonObj.isObject()) {
            QJsonObject obj = jsonObj.toObject();

            // 处理查询结果
            Customer customer;
            customer.setId(obj.value(CUS_ID).toString());
            customer.setAge(obj.value(CUS_AGE).toInt());
            customer.setName(obj.value(CUS_NAME).toString());
            customer.setGender(obj.value(CUS_GENDER).toString());
            customer.setPhone(obj.value(CUS_PHONE).toString());
            customer.setProjId(obj.value(CUS_PROJ_ID).toString());
            cusVec.push_back(customer);
        }
    }

    return cusVec;
}
