#ifndef EMPLOYEEINFO_H
#define EMPLOYEEINFO_H

#include "information.h"
#include "employeemodel.h"

class EmployeeInfo : public Information
{
public:
    EmployeeInfo(QWidget *parent = nullptr);

    EmployeeInfo(Employee &emp, QWidget *parent = nullptr);

protected:
    void commit() override;
    void modifyPwd() override;
    void loadInfo() override;

private:
    Employee self;
    EmployeeModel empModel;
};

#endif // EMPLOYEEINFO_H
