#ifndef PROJECTMANAGERTABLE_H
#define PROJECTMANAGERTABLE_H

#include "infotable.h"
#include "employeemodel.h"

class ProjectManagerTable : public InfoTable
{
public:
    ProjectManagerTable(QWidget *parent = nullptr);

private:
    QVector<QString> setColName() override;
    void showData() override;
    void loadData() override;

private slots:
    void onEmpInfoBtnClicked();

private:
    QMap<QString, Employee> empMap;
    EmployeeModel empModel;
};

#endif // PROJECTMANAGERTABLE_H
