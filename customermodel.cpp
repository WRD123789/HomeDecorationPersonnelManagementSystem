#include "customermodel.h"
#include "accountinstance.h"
#include "projectmodel.h"

#include <QSqlQuery>
#include <QVariant>

#define CUS_ID      0
#define CUS_NAME    1
#define CUS_AGE     2
#define CUS_GENDER  3
#define CUS_PHONE   4
#define CUS_PROJ_ID 5

CustomerModel::CustomerModel() {}

Customer CustomerModel::queryById(QString id)
{
    QSqlQuery query;
    QString sql = QString("SELECT * "
                          "FROM customer "
                          "WHERE id = '%1'").arg(id);
    query.exec(sql);

    if (query.next()) {
        Customer cus;
        cus.setId(query.value(CUS_ID).toString());
        cus.setName(query.value(CUS_NAME).toString());
        cus.setAge(query.value(CUS_AGE).toInt());
        cus.setGender(query.value(CUS_GENDER).toString());
        cus.setPhone(query.value(CUS_PHONE).toString());
        cus.setProjId(query.value(CUS_PROJ_ID).toString());
        return cus;
    } else {
        return Customer();
    }
}

Customer CustomerModel::queryByProjId(QString id)
{
    QSqlQuery query;
    QString sql = QString("SELECT * "
                          "FROM customer "
                          "WHERE `proj_id` = '%1'").arg(id);
    query.exec(sql);

    if (query.next()) {
        Customer cus;
        cus.setId(query.value(CUS_ID).toString());
        cus.setName(query.value(CUS_NAME).toString());
        cus.setAge(query.value(CUS_AGE).toInt());
        cus.setGender(query.value(CUS_GENDER).toString());
        cus.setPhone(query.value(CUS_PHONE).toString());
        cus.setProjId(query.value(CUS_PROJ_ID).toString());
        return cus;
    } else {
        return Customer();
    }
}

bool CustomerModel::insert(Customer &cus)
{
    QSqlQuery query;
    QString sql = QString("INSERT INTO customer "
                          "VALUES ('%1', '%2', %3, '%4', '%5', '%6')").arg(
                          cus.getId(),
                          cus.getName(),
                          QString::number(cus.getAge()),
                          cus.getGender(),
                          cus.getPhone(),
                          cus.getProjId());
    return query.exec(sql);
}

bool CustomerModel::remove(Customer &cus)
{
    QSqlQuery query;
    QString sql = QString("DELETE FROM customer "
                          "WHERE id = '%1'").arg(cus.getId());
    return query.exec(sql);
}

bool CustomerModel::update(Customer &cus)
{
    QSqlQuery query;
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
    return query.exec(sql);
}

QVector<Customer> CustomerModel::queryAll()
{
    QVector<Customer> cusVec{};

    QSqlQuery query;
    QString sql = QString("SELECT * "
                          "FROM customer");
    query.exec(sql);

    while(query.next()) {
        Customer cus;
        cus.setId(query.value(CUS_ID).toString());
        cus.setName(query.value(CUS_NAME).toString());
        cus.setAge(query.value(CUS_AGE).toInt());
        cus.setGender(query.value(CUS_GENDER).toString());
        cus.setPhone(query.value(CUS_PHONE).toString());
        cus.setProjId(query.value(CUS_PROJ_ID).toString());
        cusVec.push_back(cus);
    }
    return cusVec;
}

QVector<Customer> CustomerModel::queryAllByCurId()
{
    QVector<Customer> cusVec{};

    QString curId = AccountInstance::instance().getId();

    QSqlQuery query;
    QString sql = QString("SELECT A.id, "
                          "A.name, "
                          "A.age, "
                          "A.gender, "
                          "A.phone, "
                          "A.proj_id "
                          "FROM customer AS A "
                          "INNER JOIN project AS B ON A.proj_id = B.id "
                          "WHERE B.salesman_id = '%1'").arg(curId);
    query.exec(sql);

    while(query.next()) {
        Customer cus;
        cus.setId(query.value(CUS_ID).toString());
        cus.setName(query.value(CUS_NAME).toString());
        cus.setAge(query.value(CUS_AGE).toInt());
        cus.setGender(query.value(CUS_GENDER).toString());
        cus.setPhone(query.value(CUS_PHONE).toString());
        cus.setProjId(query.value(CUS_PROJ_ID).toString());
        cusVec.push_back(cus);
    }
    return cusVec;
}
