#ifndef FINANCE_H
#define FINANCE_H

#include <QString>

class Finance
{
public:
    Finance() = default;

    QString getId() const
    {
        return id;
    }

    void setId(QString id)
    {
        this->id = id;
    }

    double getDeposit() const
    {
        return deposit;
    }

    void setDeposit(double deposit)
    {
        this->deposit = deposit;
    }

    double getCost() const
    {
        return cost;
    }

    void setCost(double cost)
    {
        this->cost = cost;
    }

    double getAmount() const
    {
        return amount;
    }

    void setAmount(double amount)
    {
        this->amount = amount;
    }

    QString getProjId() const
    {
        return projId;
    }

    void setProjId(QString projId)
    {
        this->projId = projId;
    }

private:
    QString id;
    double deposit;
    double cost;
    double amount;
    QString projId;
};

#endif // FINANCE_H
