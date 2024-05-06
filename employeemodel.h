#ifndef EMPLOYEEMODEL_H
#define EMPLOYEEMODEL_H

#include "employee.h"

class EmployeeModel
{
public:
    EmployeeModel();

    // 根据 `id` 查询员工信息
    Employee queryById(QString id);

    // 根据姓名查询员工信息
    Employee queryByName(QString name);

    // 插入记录
    bool insert(Employee &acc);

    // 删除记录
    bool remove(Employee &acc);

    // 更新记录
    bool update(Employee &acc);

    QVector<Employee> queryAll();

    // 查询某一职位的所有员工
    QVector<Employee> queryAllByIdentity(QString identity);
};

#endif // EMPLOYEEMODEL_H
