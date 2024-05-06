#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <QString>

class Employee
{
public:
    Employee() = default;

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

    QString getEmail() const
    {
        return email;
    }

    void setEmail(QString email)
    {
        this->email = email;
    }

private:
    QString id;
    int age;
    QString name;
    QString gender;
    QString phone;
    QString email;
};

#endif // EMPLOYEE_H
