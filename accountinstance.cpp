#include "accountinstance.h"

AccountInstance AccountInstance::instance_ = AccountInstance();

AccountInstance::AccountInstance() {}

AccountInstance &AccountInstance::instance()
{
    return instance_;
}

void AccountInstance::setInfo(Employee &employee)
{
    id = employee.getId();
}

AccountInstance *AccountInstance::pInstance()
{
    return &instance_;
}

QString AccountInstance::getId() const
{
    return id;
}

void AccountInstance::setId(QString id)
{
    this->id = id;
}


QString AccountInstance::getName() const
{
    return name;
}

void AccountInstance::setName(QString name)
{
    this->name = name;
}
