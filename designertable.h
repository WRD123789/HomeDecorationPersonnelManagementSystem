#ifndef DESIGNERTABLE_H
#define DESIGNERTABLE_H

#include "infotable.h"
#include "employeemodel.h"

class DesignerTable : public InfoTable
{
public:
    DesignerTable(QWidget *parent = nullptr);

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

#endif // DESIGNERTABLE_H
