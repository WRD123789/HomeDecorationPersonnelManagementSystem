#ifndef ADMINEMPLOYEETABLE_H
#define ADMINEMPLOYEETABLE_H

#include "infotable.h"
#include "employeemodel.h"

class AdminEmployeeTable : public InfoTable
{
public:
    AdminEmployeeTable(QWidget *parent = nullptr);

private:
    QVector<QString> setColName() override;
    void showData() override;
    void loadData() override;
    void addBtn() override;

private slots:
    void onAddEmpBtnClicked();
    void onModifyEmpBtnClicked();
    void onDelEmpBtnClicked();
    void onResetPwdBtnClicked();

private:
    QMap<QString, Employee> empMap;
    EmployeeModel empModel;
};

#endif // ADMINEMPLOYEETABLE_H
