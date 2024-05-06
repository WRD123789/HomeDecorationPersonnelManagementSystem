#ifndef ACCOUNTMODEL_H
#define ACCOUNTMODEL_H

#include "account.h"

#include <QVector>

class AccountModel
{
public:
    AccountModel();

    // 根据 `account_number` 查询账号
    Account queryByNumber(QString &num);

    // 根据 `id` 查询账号
    Account queryById(QString id);

    // 插入记录
    bool insert(Account &acc);

    // 删除记录
    bool remove(Account &acc);

    // 更新记录
    bool update(Account &acc);

    QVector<Account> queryAll();
};

#endif // ACCOUNTMODEL_H
