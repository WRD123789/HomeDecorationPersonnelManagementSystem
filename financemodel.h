#ifndef FINANCEMODEL_H
#define FINANCEMODEL_H

#include "finance.h"

#include <QVector>

class FinanceModel
{
public:
    FinanceModel();

    // 根据 `id` 查询财务
    Finance queryById(QString id);

    // 根据项目编号查询财务
    Finance queryByProjId(QString projId);

    // 插入记录
    bool insert(Finance &fin);

    // 删除记录
    bool remove(Finance &fin);

    // 更新记录
    bool update(Finance &fin);

    QVector<Finance> queryAll();

    QVector<Finance> queryAllUnSolved();
};

#endif // FINANCEMODEL_H
