#ifndef PROJECTMODEL_H
#define PROJECTMODEL_H

#include "project.h"

class ProjectModel
{
public:
    ProjectModel();

    // 根据项目的 `id` 查询项目信息
    Project queryById(QString id);

    // 插入记录
    bool insert(Project &proj);

    // 删除记录
    bool remove(Project &proj);

    // 更新记录
    bool update(Project &proj);

    QVector<Project> queryAll();

    // 查询处于某一进度的所有项目
    // 设计师总监、项目总经理、财务使用
    QVector<Project> queryAllByProgress(QString prog);

    // 根据员工 `id` 查询它负责的项目, 仅用于设计师和项目经理
    QVector<Project> queryAllByEmpId(QString empId);

    // 根据当前登录用户查询该用户已经处理过的所有项目
    QVector<Project> queryAllSolved();
};

#endif // PROJECTMODEL_H
