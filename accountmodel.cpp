#include "accountmodel.h"

#include <QSqlQuery>
#include <QVariant>

#define ACC_ID       0
#define ACC_NUMBER   1
#define ACC_PASSWORD 2
#define ACC_IDENTITY 3

AccountModel::AccountModel() {}

Account AccountModel::queryByNumber(QString &num)
{
    QSqlQuery query;
    QString sql = QString("SELECT * "
                          "FROM account "
                          "WHERE `account_number` = '%1'").arg(num);
    query.exec(sql);

    if (query.next()) {
        Account account;
        account.setId(query.value(ACC_ID).toString());
        account.setAccount(query.value(ACC_NUMBER).toString());
        account.setPassword(query.value(ACC_PASSWORD).toString());
        account.setIdentity(query.value(ACC_IDENTITY).toString());
        return account;
    } else {
        return Account();
    }
}

Account AccountModel::queryById(QString id)
{
    QSqlQuery query;
    QString sql = QString("SELECT * "
                          "FROM account "
                          "WHERE id = '%1'").arg(id);
    query.exec(sql);

    if (query.next()) {
        Account account;
        account.setId(query.value(ACC_ID).toString());
        account.setAccount(query.value(ACC_NUMBER).toString());
        account.setPassword(query.value(ACC_PASSWORD).toString());
        account.setIdentity(query.value(ACC_IDENTITY).toString());
        return account;
    } else {
        return Account();
    }
}

bool AccountModel::insert(Account &acc)
{
    QSqlQuery query;
    QString sql = QString("INSERT INTO account "
                          "VALUES ('%1', '%2', '%3', '%4')").arg(
                          acc.getId(),
                          acc.getAccount(),
                          acc.getPassword(),
                          acc.getIdentity());
    qDebug() << sql;
    return query.exec(sql);
}

bool AccountModel::remove(Account &acc)
{
    QSqlQuery query;
    QString sql = QString("DELETE FROM account "
                          "WHERE id = '%1'").arg(acc.getId());
    return query.exec(sql);
}

bool AccountModel::update(Account &acc)
{
    QSqlQuery query;
    QString sql = QString("UPDATE account "
                          "SET "
                              "password = '%1', "
                              "identity = '%2' "
                          "WHERE `account_number` = '%3'").arg(
                          acc.getPassword(),
                          acc.getIdentity(),
                          acc.getAccount());
    return query.exec(sql);
}

QVector<Account> AccountModel::queryAll()
{
    QVector<Account> accVec{};

    QSqlQuery query;
    QString sql = QString("SELECT * "
                          "FROM account");
    query.exec(sql);

    while(query.next()) {
        Account account;
        account.setId(query.value(ACC_ID).toString());
        account.setAccount(query.value(ACC_NUMBER).toString());
        account.setPassword(query.value(ACC_PASSWORD).toString());
        account.setIdentity(query.value(ACC_IDENTITY).toString());
        accVec.push_back(account);
    }
    return accVec;
}

