#ifndef ACCOUNTINSTANCE_H
#define ACCOUNTINSTANCE_H

#include "employee.h"

#include <QString>

/*
 * 系统只能登录一个用户,
 * 为了随时能拿到登录用户的信息,
 * 创建一个账号类的单例
 */
class AccountInstance
{
public:
    // 弃置拷贝移动构造和等号赋值
    AccountInstance(const AccountInstance&) = delete;
    AccountInstance(const AccountInstance&&) = delete;
    AccountInstance& operator=(const AccountInstance&&) = delete;

    // 获取引用实例
    static AccountInstance& instance();

    // 获取指针实例
    static AccountInstance* pInstance();

    void setInfo(Employee&);

    QString getId() const;
    void setId(QString id);

    QString getName() const;
    void setName(QString name);

private:
    AccountInstance();
    static AccountInstance instance_;

    QString id;
    QString name;
};

#endif // ACCOUNTINSTANCE_H
