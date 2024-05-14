#include "projectmodel.h"
#include "accountmodel.h"
#include "accountinstance.h"
#include "globalvariable.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTcpSocket>
#include <QVariant>

#define PROJ_ID          "id"
#define PROJ_NAME        "name"
#define PROJ_CONTENT     "content"
#define PROJ_START_TIME  "start_time"
#define PROJ_PROGRESS    "progress"
#define PROJ_UPDATE_TIME "update_time"
#define PROJ_SALESMAN_ID "salesman_id"
#define PROJ_DESIGNER_ID "designer_id"
#define PROJ_MANAGER_ID  "project_manager_id"
#define PROJ_IMAGE0_ID   "image0_path"
#define PROJ_IMAGE1_ID   "image1_path"
#define PROJ_IMAGE2_ID   "image2_path"
#define PROJ_IMAGE3_ID   "image3_path"
#define PROJ_TABLE_ID    "table_path"

ProjectModel::ProjectModel() {}

Project ProjectModel::queryById(QString id)
{
    // 尝试连接服务器
    QTcpSocket socket;
    socket.connectToHost(ipAddress, port);

    if (!socket.waitForConnected()) {
        qWarning() << "连接服务器失败: " << socket.errorString();
        return Project();
    }

    QString sql = QString("SELECT * "
                          "FROM project "
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
        return Project();
    }

    QByteArray responseData = socket.readAll();

    // 解析 Json 数据
    QJsonDocument jsonResponse = QJsonDocument::fromJson(responseData);
    if (!jsonResponse.isArray()) {
        qWarning() << "无效的 Json 数据!";
        return Project();
    }

    QJsonArray jsonArray = jsonResponse.array();
    for (const auto &jsonObj : jsonArray) {
        if (jsonObj.isObject()) {
            QJsonObject obj = jsonObj.toObject();

            // 处理查询结果
            Project proj;
            proj.setId(obj.value(PROJ_ID).toString());
            proj.setName(obj.value(PROJ_NAME).toString());
            proj.setContent(obj.value(PROJ_CONTENT).toString());
            proj.setStartTime(QDateTime::fromString(
                obj.value(PROJ_START_TIME).toString(), Qt::ISODate));
            proj.setProgress(obj.value(PROJ_PROGRESS).toString());
            proj.setUpdateTime(QDateTime::fromString(
                obj.value(PROJ_UPDATE_TIME).toString(), Qt::ISODate));
            proj.setSalesmanId(obj.value(PROJ_SALESMAN_ID).toString());
            proj.setDesignerId(obj.value(PROJ_DESIGNER_ID).toString());
            proj.setProjManagerId(obj.value(PROJ_MANAGER_ID).toString());
            proj.setImage0Path(obj.value(PROJ_IMAGE0_ID).toString());
            proj.setImage1Path(obj.value(PROJ_IMAGE1_ID).toString());
            proj.setImage2Path(obj.value(PROJ_IMAGE2_ID).toString());
            proj.setImage3Path(obj.value(PROJ_IMAGE3_ID).toString());
            proj.setTablePath(obj.value(PROJ_TABLE_ID).toString());
            return proj;
        }
    }
    return Project();
}

bool ProjectModel::insert(Project &proj)
{
    // 尝试连接服务器
    QTcpSocket socket;
    socket.connectToHost(ipAddress, port);

    if (!socket.waitForConnected()) {
        qWarning() << "连接服务器失败: " << socket.errorString();
        return false;
    }

    QString sql = QString("INSERT INTO project "
                          "VALUES ('%1', '%2', '%3', '%4', '%5', '%6', "
                          "'%7', '%8', '%9', '%10', '%11', '%12', '%13', '%14')").arg(
                          proj.getId(),
                          proj.getName(),
                          proj.getContent(),
                          proj.getStartTime().toString("yyyy-MM-dd HH:mm"),
                          proj.getProgress(),
                          proj.getUpdateTime().toString("yyyy-MM-dd HH:mm"),
                          proj.getSalesmanId(),
                          proj.getDesignerId(),
                          proj.getProjManagerId(),
                          proj.getImage0Path(),
                          proj.getImage1Path(),
                          proj.getImage2Path(),
                          proj.getImage3Path(),
                          proj.getTablePath());
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

bool ProjectModel::remove(Project &proj)
{
    // 尝试连接服务器
    QTcpSocket socket;
    socket.connectToHost(ipAddress, port);

    if (!socket.waitForConnected()) {
        qWarning() << "连接服务器失败: " << socket.errorString();
        return false;
    }

    QString sql = QString("DELETE FROM project "
                          "WHERE id = '%1'").arg(proj.getId());
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

bool ProjectModel::update(Project &proj)
{
    // 尝试连接服务器
    QTcpSocket socket;
    socket.connectToHost(ipAddress, port);

    if (!socket.waitForConnected()) {
        qWarning() << "连接服务器失败: " << socket.errorString();
                                                   return false;
    }

    QString sql = QString("UPDATE project "
                          "SET "
                          "`name` =               '%1', "
                          "`content` =            '%2', "
                          "`start_time` =         '%3', "
                          "`progress` =           '%4', "
                          "`update_time` =        '%5', "
                          "`salesman_id` =        '%6', "
                          "`designer_id` =        '%7', "
                          "`project_manager_id` = '%8', "
                          "`image0_path` =        '%9', "
                          "`image1_path` =        '%10', "
                          "`image2_path` =        '%11', "
                          "`image3_path` =        '%12', "
                          "`table_path` =         '%13' "
                          "WHERE id = '%14'").arg(
                          proj.getName(),
                          proj.getContent(),
                          proj.getStartTime().toString("yyyy-MM-dd HH:mm"),
                          proj.getProgress(),
                          proj.getUpdateTime().toString("yyyy-MM-dd HH:mm"),
                          proj.getSalesmanId(),
                          proj.getDesignerId(),
                          proj.getProjManagerId(),
                          proj.getImage0Path(),
                          proj.getImage1Path(),
                          proj.getImage2Path(),
                          proj.getImage3Path(),
                          proj.getTablePath(),
                          proj.getId());
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

QVector<Project> ProjectModel::queryAll()
{
    QVector<Project> projVec{};

    // 尝试连接服务器
    QTcpSocket socket;
    socket.connectToHost(ipAddress, port);

    if (!socket.waitForConnected()) {
        qWarning() << "连接服务器失败: " << socket.errorString();
        return projVec;
    }

    QString sql = QString("SELECT * "
                          "FROM project");
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
        return projVec;
    }

    QByteArray responseData = socket.readAll();

    // 解析 Json 数据
    QJsonDocument jsonResponse = QJsonDocument::fromJson(responseData);
    if (!jsonResponse.isArray()) {
        qWarning() << "无效的 Json 数据!";
        return projVec;
    }

    QJsonArray jsonArray = jsonResponse.array();
    for (const auto &jsonObj : jsonArray) {
        if (jsonObj.isObject()) {
            QJsonObject obj = jsonObj.toObject();

            // 处理查询结果
            Project proj;
            proj.setId(obj.value(PROJ_ID).toString());
            proj.setName(obj.value(PROJ_NAME).toString());
            proj.setContent(obj.value(PROJ_CONTENT).toString());
            proj.setStartTime(QDateTime::fromString(
                obj.value(PROJ_START_TIME).toString(), Qt::ISODate));
            proj.setProgress(obj.value(PROJ_PROGRESS).toString());
            proj.setUpdateTime(QDateTime::fromString(
                obj.value(PROJ_UPDATE_TIME).toString(), Qt::ISODate));
            proj.setSalesmanId(obj.value(PROJ_SALESMAN_ID).toString());
            proj.setDesignerId(obj.value(PROJ_DESIGNER_ID).toString());
            proj.setProjManagerId(obj.value(PROJ_MANAGER_ID).toString());
            proj.setImage0Path(obj.value(PROJ_IMAGE0_ID).toString());
            proj.setImage1Path(obj.value(PROJ_IMAGE1_ID).toString());
            proj.setImage2Path(obj.value(PROJ_IMAGE2_ID).toString());
            proj.setImage3Path(obj.value(PROJ_IMAGE3_ID).toString());
            proj.setTablePath(obj.value(PROJ_TABLE_ID).toString());
            projVec.push_back(proj);
        }
    }

    return projVec;
}

QVector<Project> ProjectModel::queryAllByProgress(QString prog)
{
    QVector<Project> projVec{};

    // 尝试连接服务器
    QTcpSocket socket;
    socket.connectToHost(ipAddress, port);

    if (!socket.waitForConnected()) {
        qWarning() << "连接服务器失败: " << socket.errorString();
        return projVec;
    }

    QString sql = QString("SELECT * "
                          "FROM project "
                          "WHERE progress = '%1'").arg(prog);
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
        return projVec;
    }

    QByteArray responseData = socket.readAll();

    // 解析 Json 数据
    QJsonDocument jsonResponse = QJsonDocument::fromJson(responseData);
    if (!jsonResponse.isArray()) {
        qWarning() << "无效的 Json 数据!";
        return projVec;
    }

    QJsonArray jsonArray = jsonResponse.array();
    for (const auto &jsonObj : jsonArray) {
        if (jsonObj.isObject()) {
            QJsonObject obj = jsonObj.toObject();

            // 处理查询结果
            Project proj;
            proj.setId(obj.value(PROJ_ID).toString());
            proj.setName(obj.value(PROJ_NAME).toString());
            proj.setContent(obj.value(PROJ_CONTENT).toString());
            proj.setStartTime(QDateTime::fromString(
                obj.value(PROJ_START_TIME).toString(), Qt::ISODate));
            proj.setProgress(obj.value(PROJ_PROGRESS).toString());
            proj.setUpdateTime(QDateTime::fromString(
                obj.value(PROJ_UPDATE_TIME).toString(), Qt::ISODate));
            proj.setSalesmanId(obj.value(PROJ_SALESMAN_ID).toString());
            proj.setDesignerId(obj.value(PROJ_DESIGNER_ID).toString());
            proj.setProjManagerId(obj.value(PROJ_MANAGER_ID).toString());
            proj.setImage0Path(obj.value(PROJ_IMAGE0_ID).toString());
            proj.setImage1Path(obj.value(PROJ_IMAGE1_ID).toString());
            proj.setImage2Path(obj.value(PROJ_IMAGE2_ID).toString());
            proj.setImage3Path(obj.value(PROJ_IMAGE3_ID).toString());
            proj.setTablePath(obj.value(PROJ_TABLE_ID).toString());
            projVec.push_back(proj);
        }
    }

    return projVec;
}

QVector<Project> ProjectModel::queryAllByEmpId(QString empId)
{
    QVector<Project> projVec{};
    QString identity = AccountModel().queryById(empId).getIdentity();

    // 尝试连接服务器
    QTcpSocket socket;
    socket.connectToHost(ipAddress, port);

    if (!socket.waitForConnected()) {
        qWarning() << "连接服务器失败: " << socket.errorString();
        return projVec;
    }

    QString sql;
    if (identity == "设计师") {
        sql = QString("SELECT * "
                      "FROM project "
                      "WHERE `designer_id` = '%1' "
                      "AND (progress = '量房设计' "
                      "OR progress = '平面布置图设计' "
                      "OR progress = '深入图设计' "
                      "OR progress = '效果图设计' "
                      "OR progress = '预算表提交') ").arg(empId);
    } else if (identity == "项目经理") {
        sql = QString("SELECT * "
                      "FROM project "
                      "WHERE `project_manager_id` = '%1' "
                      "AND progress = '施工' ").arg(empId);
    }

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
        return projVec;
    }

    QByteArray responseData = socket.readAll();

    // 解析 Json 数据
    QJsonDocument jsonResponse = QJsonDocument::fromJson(responseData);
    if (!jsonResponse.isArray()) {
        qWarning() << "无效的 Json 数据!";
        return projVec;
    }

    QJsonArray jsonArray = jsonResponse.array();
    for (const auto &jsonObj : jsonArray) {
        if (jsonObj.isObject()) {
            QJsonObject obj = jsonObj.toObject();

            // 处理查询结果
            Project proj;
            proj.setId(obj.value(PROJ_ID).toString());
            proj.setName(obj.value(PROJ_NAME).toString());
            proj.setContent(obj.value(PROJ_CONTENT).toString());
            proj.setStartTime(QDateTime::fromString(
                obj.value(PROJ_START_TIME).toString(), Qt::ISODate));
            proj.setProgress(obj.value(PROJ_PROGRESS).toString());
            proj.setUpdateTime(QDateTime::fromString(
                obj.value(PROJ_UPDATE_TIME).toString(), Qt::ISODate));
            proj.setSalesmanId(obj.value(PROJ_SALESMAN_ID).toString());
            proj.setDesignerId(obj.value(PROJ_DESIGNER_ID).toString());
            proj.setProjManagerId(obj.value(PROJ_MANAGER_ID).toString());
            proj.setImage0Path(obj.value(PROJ_IMAGE0_ID).toString());
            proj.setImage1Path(obj.value(PROJ_IMAGE1_ID).toString());
            proj.setImage2Path(obj.value(PROJ_IMAGE2_ID).toString());
            proj.setImage3Path(obj.value(PROJ_IMAGE3_ID).toString());
            proj.setTablePath(obj.value(PROJ_TABLE_ID).toString());
            projVec.push_back(proj);
        }
    }

    return projVec;
}

QVector<Project> ProjectModel::queryAllSolved()
{
    Account acc = AccountModel().queryById(AccountInstance::instance().getId());
    QString identity = acc.getIdentity();
    QVector<Project> projVec{};

    // 尝试连接服务器
    QTcpSocket socket;
    socket.connectToHost(ipAddress, port);

    if (!socket.waitForConnected()) {
        qWarning() << "连接服务器失败: " << socket.errorString();
        return projVec;
    }

    QString sql;
    if (identity == "业务员") {
        sql = QString("SELECT * "
                      "FROM project "
                      "WHERE `salesman_id` = '%1' "
                      "AND progress <> '业务员沟通' ").arg(acc.getId());
    } else if (identity == "设计师总监") {
        sql = QString("SELECT * "
                      "FROM project "
                      "WHERE progress NOT IN ('业务员沟通', '设计总监分配')");
    } else if (identity == "设计师") {
        sql = QString("SELECT * "
                      "FROM project "
                      "WHERE `designer_id` = '%1' "
                      "AND progress NOT IN "
                      "('量房设计', '平面布置图设计', '深入图设计', '效果图设计', '预算表提交') ")
                  .arg(acc.getId());
    } else if (identity == "财务") {
        sql = QString("SELECT * "
                      "FROM project "
                      "WHERE progress NOT IN "
                      "('业务员沟通', '设计总监分配', '量房设计', '平面布置图设计', "
                      "'合同设计', '定金交付') ");
    } else if (identity == "项目总经理") {
        sql = QString("SELECT * "
                      "FROM project "
                      "WHERE progress IN ('施工', '已完成', '已取消')");
    } else if (identity == "项目经理") {
        sql = QString("SELECT * "
                      "FROM project "
                      "WHERE `project_manager_id` = '%1' "
                      "AND progress IN ('已完成', '已取消')").arg(acc.getId());
    }

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
        return projVec;
    }

    QByteArray responseData = socket.readAll();

    // 解析 Json 数据
    QJsonDocument jsonResponse = QJsonDocument::fromJson(responseData);
    if (!jsonResponse.isArray()) {
        qWarning() << "无效的 Json 数据!";
        return projVec;
    }

    QJsonArray jsonArray = jsonResponse.array();
    for (const auto &jsonObj : jsonArray) {
        if (jsonObj.isObject()) {
            QJsonObject obj = jsonObj.toObject();

            // 处理查询结果
            Project proj;
            proj.setId(obj.value(PROJ_ID).toString());
            proj.setName(obj.value(PROJ_NAME).toString());
            proj.setContent(obj.value(PROJ_CONTENT).toString());
            proj.setStartTime(QDateTime::fromString(
                obj.value(PROJ_START_TIME).toString(), Qt::ISODate));
            proj.setProgress(obj.value(PROJ_PROGRESS).toString());
            proj.setUpdateTime(QDateTime::fromString(
                obj.value(PROJ_UPDATE_TIME).toString(), Qt::ISODate));
            proj.setSalesmanId(obj.value(PROJ_SALESMAN_ID).toString());
            proj.setDesignerId(obj.value(PROJ_DESIGNER_ID).toString());
            proj.setProjManagerId(obj.value(PROJ_MANAGER_ID).toString());
            proj.setImage0Path(obj.value(PROJ_IMAGE0_ID).toString());
            proj.setImage1Path(obj.value(PROJ_IMAGE1_ID).toString());
            proj.setImage2Path(obj.value(PROJ_IMAGE2_ID).toString());
            proj.setImage3Path(obj.value(PROJ_IMAGE3_ID).toString());
            proj.setTablePath(obj.value(PROJ_TABLE_ID).toString());
            projVec.push_back(proj);
        }
    }

    return projVec;
}
