#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <QString>

class Customer
{
public:
    Customer() = default;

    QString getId() const
    {
        return id;
    }

    void setId(QString id)
    {
        this->id = id;
    }

    int getAge() const
    {
        return age;
    }

    void setAge(int age)
    {
        this->age = age;
    }

    QString getName() const
    {
        return name;
    }

    void setName(const QString name)
    {
        this->name = name;
    }

    QString getGender() const
    {
        return gender;
    }

    void setGender(const QString gender)
    {
        this->gender = gender;
    }

    QString getPhone() const
    {
        return phone;
    }

    void setPhone(QString phone)
    {
        this->phone = phone;
    }

    QString getProjId() const
    {
        return projId;
    }

    void setProjId(QString id)
    {
        this->projId = id;
    }

private:
    QString id;
    int age;
    QString name;
    QString gender;
    QString phone;
    QString projId;
};

#endif // CUSTOMER_H
