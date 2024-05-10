#include "financemodel.h"

#include <QSqlQuery>
#include <QVariant>

#define FIN_ID      0
#define FIN_DEPOSIT 1
#define FIN_COST    2
#define FIN_AMOUNT  3
#define FIN_PROJ_ID 4

FinanceModel::FinanceModel() {}

Finance FinanceModel::queryById(QString id)
{
    QSqlQuery query;
    QString sql = QString("SELECT * "
                          "FROM finance "
                          "WHERE id = '%1'").arg(id);
    query.exec(sql);

    if (query.next()) {
        Finance fin;
        fin.setId(query.value(FIN_ID).toString());
        fin.setDeposit(query.value(FIN_DEPOSIT).toDouble());
        fin.setCost(query.value(FIN_COST).toDouble());
        fin.setAmount(query.value(FIN_AMOUNT).toDouble());
        fin.setProjId(query.value(FIN_PROJ_ID).toString());
        return fin;
    } else {
        return Finance();
    }
}

Finance FinanceModel::queryByProjId(QString projId)
{
    QSqlQuery query;
    QString sql = QString("SELECT * "
                          "FROM finance "
                          "WHERE `proj_id` = '%1'").arg(projId);
    query.exec(sql);

    if (query.next()) {
        Finance fin;
        fin.setId(query.value(FIN_ID).toString());
        fin.setDeposit(query.value(FIN_DEPOSIT).toDouble());
        fin.setCost(query.value(FIN_COST).toDouble());
        fin.setProjId(query.value(FIN_PROJ_ID).toString());
        return fin;
    } else {
        return Finance();
    }
}

bool FinanceModel::insert(Finance &fin)
{
    QSqlQuery query;
    QString sql = QString("INSERT INTO finance "
                          "VALUES ('%1', %2, %3, %4, '%5')").arg(
                          fin.getId(),
                          QString::number(fin.getDeposit(), 'f', 2),
                          QString::number(fin.getCost(), 'f', 2),
                          QString::number(fin.getAmount(), 'f', 2),
                          fin.getProjId());
    qDebug() << sql;
    return query.exec(sql);
}

bool FinanceModel::remove(Finance &fin)
{
    QSqlQuery query;
    QString sql = QString("DELETE FROM finance "
                          "WHERE id = '%1'").arg(fin.getId());
    return query.exec(sql);
}

bool FinanceModel::update(Finance &fin)
{
    QSqlQuery query;
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
    return query.exec(sql);
}

QVector<Finance> FinanceModel::queryAll()
{
    QVector<Finance> finVec{};

    QSqlQuery query;
    QString sql = QString("SELECT * "
                          "FROM finance");
    query.exec(sql);

    while(query.next()) {
        Finance fin;
        fin.setId(query.value(FIN_ID).toString());
        fin.setDeposit(query.value(FIN_DEPOSIT).toDouble());
        fin.setCost(query.value(FIN_COST).toDouble());
        fin.setAmount(query.value(FIN_AMOUNT).toDouble());
        fin.setProjId(query.value(FIN_PROJ_ID).toString());
        finVec.push_back(fin);
    }
    return finVec;
}

QVector<Finance> FinanceModel::queryAllUnSolved()
{
    QVector<Finance> finVec{};

    QSqlQuery query;
    QString sql = QString("SELECT A.id, A.deposit, A.cost, A.amount, A.proj_id "
                          "FROM finance AS A "
                          "INNER JOIN project AS B ON A.proj_id = B.id "
                          "WHERE B.progress IN ('业务员沟通', '设计总监分配', '量房设计', "
                          "'平面布置图设计', '合同设计', '定金交付')");
    query.exec(sql);

    while(query.next()) {
        Finance fin;
        fin.setId(query.value(FIN_ID).toString());
        fin.setDeposit(query.value(FIN_DEPOSIT).toDouble());
        fin.setCost(query.value(FIN_COST).toDouble());
        fin.setAmount(query.value(FIN_AMOUNT).toDouble());
        fin.setProjId(query.value(FIN_PROJ_ID).toString());
        finVec.push_back(fin);
    }
    return finVec;
}

