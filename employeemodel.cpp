#include "employeemodel.h"

#include <QSqlQuery>
#include <QVariant>

#define EMP_ID       0
#define EMP_NAME     1
#define EMP_AGE      2
#define EMP_GENDER   3
#define EMP_PHONE    4
#define EMP_EMAIL    5


EmployeeModel::EmployeeModel() {}

Employee EmployeeModel::queryById(QString id)
{
    QSqlQuery query;
    QString sql = QString("SELECT * "
                          "FROM employee "
                          "WHERE id = '%1'").arg(id);
    query.exec(sql);

    if (query.next()) {
        Employee emp;
        emp.setId(query.value(EMP_ID).toString());
        emp.setName(query.value(EMP_NAME).toString());
        emp.setAge(query.value(EMP_AGE).toInt());
        emp.setGender(query.value(EMP_GENDER).toString());
        emp.setPhone(query.value(EMP_PHONE).toString());
        emp.setEmail(query.value(EMP_EMAIL).toString());
        return emp;
    } else {
        return Employee();
    }
}

Employee EmployeeModel::queryByName(QString name)
{
    QSqlQuery query;
    QString sql = QString("SELECT * "
                          "FROM employee "
                          "WHERE name = '%1'").arg(name);
    query.exec(sql);

    if (query.next()) {
        Employee emp;
        emp.setId(query.value(EMP_ID).toString());
        emp.setName(query.value(EMP_NAME).toString());
        emp.setAge(query.value(EMP_AGE).toInt());
        emp.setGender(query.value(EMP_GENDER).toString());
        emp.setPhone(query.value(EMP_PHONE).toString());
        emp.setEmail(query.value(EMP_EMAIL).toString());
        return emp;
    } else {
        return Employee();
    }
}

bool EmployeeModel::insert(Employee &emp)
{
    QSqlQuery query;
    QString sql = QString("INSERT INTO employee "
                          "VALUES ('%1', '%2', %3, '%4', '%5', '%6')").arg(
                          emp.getId(),
                          emp.getName(),
                          QString::number(emp.getAge()),
                          emp.getGender(),
                          emp.getPhone(),
                          emp.getEmail());
    return query.exec(sql);
}

bool EmployeeModel::remove(Employee &emp)
{
    QSqlQuery query;
    QString sql = QString("DELETE FROM employee "
                          "WHERE id = '%1'").arg(emp.getId());
    return query.exec(sql);
}

bool EmployeeModel::update(Employee &emp)
{
    QSqlQuery query;
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
    qDebug() << sql;
    return query.exec(sql);
}

QVector<Employee> EmployeeModel::queryAll()
{
    QVector<Employee> empVec{};

    QSqlQuery query;
    QString sql = QString("SELECT * "
                          "FROM employee");
    query.exec(sql);

    while(query.next()) {
        Employee emp;
        emp.setId(query.value(EMP_ID).toString());
        emp.setName(query.value(EMP_NAME).toString());
        emp.setAge(query.value(EMP_AGE).toInt());
        emp.setGender(query.value(EMP_GENDER).toString());
        emp.setPhone(query.value(EMP_PHONE).toString());
        emp.setEmail(query.value(EMP_EMAIL).toString());
        empVec.push_back(emp);
    }
    return empVec;
}

QVector<Employee> EmployeeModel::queryAllByIdentity(QString identity)
{
    QVector<Employee> empVec{};

    QSqlQuery query;
    QString sql = QString("SELECT A.id, "
                          "A.name, "
                          "A.age, "
                          "A.gender, "
                          "A.phone, "
                          "A.email "
                          "FROM employee AS A "
                          "INNER JOIN account AS B ON A.id = B.id "
                          "WHERE B.identity = '%1'").arg(identity);
    query.exec(sql);

    while(query.next()) {
        Employee emp;
        emp.setId(query.value(EMP_ID).toString());
        emp.setName(query.value(EMP_NAME).toString());
        emp.setAge(query.value(EMP_AGE).toInt());
        emp.setGender(query.value(EMP_GENDER).toString());
        emp.setPhone(query.value(EMP_PHONE).toString());
        emp.setEmail(query.value(EMP_EMAIL).toString());
        empVec.push_back(emp);
    }
    return empVec;
}
