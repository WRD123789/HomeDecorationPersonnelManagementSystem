#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QString>

class Account
{
public:
    Account() = default;

    QString getId() const
    {
        return id;
    }

    void setId(QString id)
    {
        this->id = id;
    }

    QString getAccount() const
    {
        return accountNumber;
    }

    void setAccount(QString account)
    {
        this->accountNumber = account;
    }

    QString getPassword() const
    {
        return password;
    }

    void setPassword(QString password)
    {
        this->password = password;
    }

    QString getIdentity() const
    {
        return identity;
    }

    void setIdentity(QString identity)
    {
        this->identity = identity;
    }

private:
    QString id;
    QString accountNumber;
    QString password;
    QString identity;
};

#endif // ACCOUNT_H
