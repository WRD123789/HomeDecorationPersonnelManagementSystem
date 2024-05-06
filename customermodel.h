#ifndef CUSTOMERMODEL_H
#define CUSTOMERMODEL_H

#include "customer.h"

class CustomerModel
{
public:
    CustomerModel();

    // 根据 `id` 查询客户信息
    Customer queryById(QString id);

    // 根据项目 `id` 查询客户信息
    Customer queryByProjId(QString id);

    // 插入记录
    bool insert(Customer &cus);

    // 删除记录
    bool remove(Customer &cus);

    // 更新记录
    bool update(Customer &cus);

    QVector<Customer> queryAll();
    // 根据当前登录用户的 `id` 获取所有对应的客户信息, 业务员端使用
    QVector<Customer> queryAllByCurId();
};

#endif // CUSTOMERMODEL_H
