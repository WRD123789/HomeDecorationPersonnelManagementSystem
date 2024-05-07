#include "projectmodel.h"
#include "accountmodel.h"
#include "accountinstance.h"

#include <QSqlQuery>
#include <QVariant>

#define PROJ_ID          0
#define PROJ_NAME        1
#define PROJ_CONTENT     2
#define PROJ_START_TIME  3
#define PROJ_PROGRESS    4
#define PROJ_UPDATE_TIME 5
#define PROJ_SALESMAN_ID 6
#define PROJ_DESIGNER_ID 7
#define PROJ_MANAGER_ID  8

ProjectModel::ProjectModel() {}

Project ProjectModel::queryById(QString id)
{
    QSqlQuery query;
    QString sql = QString("SELECT * "
                          "FROM project "
                          "WHERE id = '%1'").arg(id);
    query.exec(sql);

    if (query.next()) {
        Project proj;
        proj.setId(query.value(PROJ_ID).toString());
        proj.setName(query.value(PROJ_NAME).toString());
        proj.setContent(query.value(PROJ_CONTENT).toString());
        proj.setStartTime(query.value(PROJ_START_TIME).toDateTime());
        proj.setProgress(query.value(PROJ_PROGRESS).toString());
        proj.setUpdateTime(query.value(PROJ_UPDATE_TIME).toDateTime());
        proj.setSalesmanId(query.value(PROJ_SALESMAN_ID).toString());
        proj.setDesignerId(query.value(PROJ_DESIGNER_ID).toString());
        proj.setProjManagerId(query.value(PROJ_MANAGER_ID).toString());
        return proj;
    } else {
        return Project();
    }
}

bool ProjectModel::insert(Project &proj)
{
    QSqlQuery query;
    QString sql = QString("INSERT INTO project "
                          "VALUES ('%1', '%2', '%3', '%4', '%5', '%6', '%7', '%8', '%9')").arg(
                          proj.getId(),
                          proj.getName(),
                          proj.getContent(),
                          proj.getStartTime().toString("yyyy-MM-dd HH:mm"),
                          proj.getProgress(),
                          proj.getUpdateTime().toString("yyyy-MM-dd HH:mm"),
                          proj.getSalesmanId(),
                          proj.getDesignerId(),
                          proj.getProjManagerId());
    return query.exec(sql);
}

bool ProjectModel::remove(Project &proj)
{
    QSqlQuery query;
    QString sql = QString("DELETE FROM project "
                          "WHERE id = '%1'").arg(proj.getId());
    return query.exec(sql);
}

bool ProjectModel::update(Project &proj)
{
    QSqlQuery query;
    QString sql = QString("UPDATE project "
                          "SET "
                              "`name` =               '%1', "
                              "`content` =            '%2', "
                              "`start_time` =         '%3', "
                              "`progress` =           '%4', "
                              "`update_time` =        '%5', "
                              "`salesman_id` =        '%6', "
                              "`designer_id` =        '%7', "
                              "`project_manager_id` = '%8' "
                          "WHERE id = '%9'").arg(
                          proj.getName(),
                          proj.getContent(),
                          proj.getStartTime().toString("yyyy-MM-dd HH:mm"),
                          proj.getProgress(),
                          proj.getUpdateTime().toString("yyyy-MM-dd HH:mm"),
                          proj.getSalesmanId(),
                          proj.getDesignerId(),
                          proj.getProjManagerId(),
                          proj.getId());
    return query.exec(sql);
}

QVector<Project> ProjectModel::queryAll()
{
    QVector<Project> projVec{};

    QSqlQuery query;
    QString sql = QString("SELECT * "
                          "FROM project");
    query.exec(sql);

    while(query.next()) {
        Project proj;
        proj.setId(query.value(PROJ_ID).toString());
        proj.setName(query.value(PROJ_NAME).toString());
        proj.setContent(query.value(PROJ_CONTENT).toString());
        proj.setStartTime(query.value(PROJ_START_TIME).toDateTime());
        proj.setProgress(query.value(PROJ_PROGRESS).toString());
        proj.setUpdateTime(query.value(PROJ_UPDATE_TIME).toDateTime());
        proj.setSalesmanId(query.value(PROJ_SALESMAN_ID).toString());
        proj.setDesignerId(query.value(PROJ_DESIGNER_ID).toString());
        proj.setProjManagerId(query.value(PROJ_MANAGER_ID).toString());
        projVec.push_back(proj);
    }
    return projVec;
}

QVector<Project> ProjectModel::queryAllByProgress(QString prog)
{
    QVector<Project> projVec{};

    QSqlQuery query;
    QString sql = QString("SELECT * "
                          "FROM project "
                          "WHERE progress = '%1'").arg(prog);
    query.exec(sql);

    while(query.next()) {
        Project proj;
        proj.setId(query.value(PROJ_ID).toString());
        proj.setName(query.value(PROJ_NAME).toString());
        proj.setContent(query.value(PROJ_CONTENT).toString());
        proj.setStartTime(query.value(PROJ_START_TIME).toDateTime());
        proj.setProgress(query.value(PROJ_PROGRESS).toString());
        proj.setUpdateTime(query.value(PROJ_UPDATE_TIME).toDateTime());
        proj.setSalesmanId(query.value(PROJ_SALESMAN_ID).toString());
        proj.setDesignerId(query.value(PROJ_DESIGNER_ID).toString());
        proj.setProjManagerId(query.value(PROJ_MANAGER_ID).toString());
        projVec.push_back(proj);
    }
    return projVec;
}

QVector<Project> ProjectModel::queryAllByEmpId(QString empId)
{
    QVector<Project> projVec{};
    QString identity = AccountModel().queryById(empId).getIdentity();

    QSqlQuery query;
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

    query.exec(sql);

    while(query.next()) {
        Project proj;
        proj.setId(query.value(PROJ_ID).toString());
        proj.setName(query.value(PROJ_NAME).toString());
        proj.setContent(query.value(PROJ_CONTENT).toString());
        proj.setStartTime(query.value(PROJ_START_TIME).toDateTime());
        proj.setProgress(query.value(PROJ_PROGRESS).toString());
        proj.setUpdateTime(query.value(PROJ_UPDATE_TIME).toDateTime());
        proj.setSalesmanId(query.value(PROJ_SALESMAN_ID).toString());
        proj.setDesignerId(query.value(PROJ_DESIGNER_ID).toString());
        proj.setProjManagerId(query.value(PROJ_MANAGER_ID).toString());
        projVec.push_back(proj);
    }
    return projVec;
}

QVector<Project> ProjectModel::queryAllSolved()
{
    Account acc = AccountModel().queryById(AccountInstance::instance().getId());
    QString identity = acc.getIdentity();
    QVector<Project> projVec{};

    QSqlQuery query;
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

    query.exec(sql);

    while(query.next()) {
        Project proj;
        proj.setId(query.value(PROJ_ID).toString());
        proj.setName(query.value(PROJ_NAME).toString());
        proj.setContent(query.value(PROJ_CONTENT).toString());
        proj.setStartTime(query.value(PROJ_START_TIME).toDateTime());
        proj.setProgress(query.value(PROJ_PROGRESS).toString());
        proj.setUpdateTime(query.value(PROJ_UPDATE_TIME).toDateTime());
        proj.setSalesmanId(query.value(PROJ_SALESMAN_ID).toString());
        proj.setDesignerId(query.value(PROJ_DESIGNER_ID).toString());
        proj.setProjManagerId(query.value(PROJ_MANAGER_ID).toString());
        projVec.push_back(proj);
    }
    return projVec;
}
