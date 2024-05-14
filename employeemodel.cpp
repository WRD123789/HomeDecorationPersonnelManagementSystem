#include "employeemodel.h"
#include "globalvariable.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTcpSocket>
#include <QVariant>

#define EMP_ID       "id"
#define EMP_NAME     "name"
#define EMP_AGE      "age"
#define EMP_GENDER   "gender"
#define EMP_PHONE    "phone"
#define EMP_EMAIL    "email"


EmployeeModel::EmployeeModel() {}

Employee EmployeeModel::queryById(QString id)
{
    // 尝试连接服务器
    QTcpSocket socket;
    socket.connectToHost(ipAddress, port);

    if (!socket.waitForConnected()) {
        qWarning() << "连接服务器失败: " << socket.errorString();
        return Employee();
    }

    QString sql = QString("SELECT * "
                          "FROM employee "
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
        return Employee();
    }

    QByteArray responseData = socket.readAll();

    // 解析 Json 数据
    QJsonDocument jsonResponse = QJsonDocument::fromJson(responseData);
    if (!jsonResponse.isArray()) {
        qWarning() << "无效的 Json 数据!";
        return Employee();
    }

    QJsonArray jsonArray = jsonResponse.array();
    for (const auto &jsonObj : jsonArray) {
        if (jsonObj.isObject()) {
            QJsonObject obj = jsonObj.toObject();

            // 处理查询结果
            Employee emp;
            emp.setId(obj.value(EMP_ID).toString());
            emp.setName(obj.value(EMP_NAME).toString());
            emp.setAge(obj.value(EMP_AGE).toInt());
            emp.setGender(obj.value(EMP_GENDER).toString());
            emp.setPhone(obj.value(EMP_PHONE).toString());
            emp.setEmail(obj.value(EMP_EMAIL).toString());
            return emp;
        }
    }
    return Employee();
}

Employee EmployeeModel::queryByName(QString name)
{
    // 尝试连接服务器
    QTcpSocket socket;
    socket.connectToHost(ipAddress, port);

    if (!socket.waitForConnected()) {
        qWarning() << "连接服务器失败: " << socket.errorString();
        return Employee();
    }

    QString sql = QString("SELECT * "
                          "FROM employee "
                          "WHERE name = '%1'").arg(name);
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
        return Employee();
    }

    QByteArray responseData = socket.readAll();

    // 解析 Json 数据
    QJsonDocument jsonResponse = QJsonDocument::fromJson(responseData);
    if (!jsonResponse.isArray()) {
        qWarning() << "无效的 Json 数据!";
        return Employee();
    }

    QJsonArray jsonArray = jsonResponse.array();
    for (const auto &jsonObj : jsonArray) {
        if (jsonObj.isObject()) {
            QJsonObject obj = jsonObj.toObject();

            // 处理查询结果
            Employee emp;
            emp.setId(obj.value(EMP_ID).toString());
            emp.setName(obj.value(EMP_NAME).toString());
            emp.setAge(obj.value(EMP_AGE).toInt());
            emp.setGender(obj.value(EMP_GENDER).toString());
            emp.setPhone(obj.value(EMP_PHONE).toString());
            emp.setEmail(obj.value(EMP_EMAIL).toString());
            return emp;
        }
    }
    return Employee();
}

bool EmployeeModel::insert(Employee &emp)
{
    // 尝试连接服务器
    QTcpSocket socket;
    socket.connectToHost(ipAddress, port);

    if (!socket.waitForConnected()) {
        qWarning() << "连接服务器失败: " << socket.errorString();
        return false;
    }

    QString sql = QString("INSERT INTO employee "
                          "VALUES ('%1', '%2', %3, '%4', '%5', '%6')").arg(
                          emp.getId(),
                          emp.getName(),
                          QString::number(emp.getAge()),
                          emp.getGender(),
                          emp.getPhone(),
                          emp.getEmail());
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

bool EmployeeModel::remove(Employee &emp)
{
    // 尝试连接服务器
    QTcpSocket socket;
    socket.connectToHost(ipAddress, port);

    if (!socket.waitForConnected()) {
        qWarning() << "连接服务器失败: " << socket.errorString();
        return false;
    }

    QString sql = QString("DELETE FROM employee "
                          "WHERE id = '%1'").arg(emp.getId());
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

bool EmployeeModel::update(Employee &emp)
{
    // 尝试连接服务器
    QTcpSocket socket;
    socket.connectToHost(ipAddress, port);

    if (!socket.waitForConnected()) {
        qWarning() << "连接服务器失败: " << socket.errorString();
        return false;
    }

    QString sql = QString("UPDATE employee "
                          "SET "
                          "name =     '%1', "
                          "age =       %2, "
                          "gender =   '%3', "
                          "phone =    '%4', "
                          "email =    '%5' "
                          "WHERE id = '%7'").arg(
                          emp.getName(),
                          QString::number(emp.getAge()),
                          emp.getGender(),
                          emp.getPhone(),
                          emp.getEmail(),
                          emp.getId());
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

QVector<Employee> EmployeeModel::queryAll()
{
    QVector<Employee> empVec{};

    // 尝试连接服务器
    QTcpSocket socket;
    socket.connectToHost(ipAddress, port);

    if (!socket.waitForConnected()) {
        qWarning() << "连接服务器失败: " << socket.errorString();
        return empVec;
    }

    QString sql = QString("SELECT * "
                          "FROM employee");
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
        return empVec;
    }

    QByteArray responseData = socket.readAll();

    // 解析 Json 数据
    QJsonDocument jsonResponse = QJsonDocument::fromJson(responseData);
    if (!jsonResponse.isArray()) {
        qWarning() << "无效的 Json 数据!";
        return empVec;
    }

    QJsonArray jsonArray = jsonResponse.array();
    for (const auto &jsonObj : jsonArray) {
        if (jsonObj.isObject()) {
            QJsonObject obj = jsonObj.toObject();

            // 处理查询结果
            Employee emp;
            emp.setId(obj.value(EMP_ID).toString());
            emp.setName(obj.value(EMP_NAME).toString());
            emp.setAge(obj.value(EMP_AGE).toInt());
            emp.setGender(obj.value(EMP_GENDER).toString());
            emp.setPhone(obj.value(EMP_PHONE).toString());
            emp.setEmail(obj.value(EMP_EMAIL).toString());
            empVec.push_back(emp);
        }
    }
    return empVec;
}

QVector<Employee> EmployeeModel::queryAllByIdentity(QString identity)
{
    QVector<Employee> empVec{};

    // 尝试连接服务器
    QTcpSocket socket;
    socket.connectToHost(ipAddress, port);

    if (!socket.waitForConnected()) {
        qWarning() << "连接服务器失败: " << socket.errorString();
        return empVec;
    }

    QString sql = QString("SELECT A.id, "
                          "A.name, "
                          "A.age, "
                          "A.gender, "
                          "A.phone, "
                          "A.email "
                          "FROM employee AS A "
                          "INNER JOIN account AS B ON A.id = B.id "
                          "WHERE B.identity = '%1'").arg(identity);
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
        return empVec;
    }

    QByteArray responseData = socket.readAll();

    // 解析 Json 数据
    QJsonDocument jsonResponse = QJsonDocument::fromJson(responseData);
    if (!jsonResponse.isArray()) {
        qWarning() << "无效的 Json 数据!";
        return empVec;
    }

    QJsonArray jsonArray = jsonResponse.array();
    for (const auto &jsonObj : jsonArray) {
        if (jsonObj.isObject()) {
            QJsonObject obj = jsonObj.toObject();

            // 处理查询结果
            Employee emp;
            emp.setId(obj.value(EMP_ID).toString());
            emp.setName(obj.value(EMP_NAME).toString());
            emp.setAge(obj.value(EMP_AGE).toInt());
            emp.setGender(obj.value(EMP_GENDER).toString());
            emp.setPhone(obj.value(EMP_PHONE).toString());
            emp.setEmail(obj.value(EMP_EMAIL).toString());
            empVec.push_back(emp);
        }
    }
    return empVec;
}
