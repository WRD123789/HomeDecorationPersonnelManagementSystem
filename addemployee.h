#ifndef ADDEMPLOYEE_H
#define ADDEMPLOYEE_H

#include "employeemodel.h"
#include "accountmodel.h"

#include <QDialog>

namespace Ui {
class AddEmployee;
}

class AddEmployee : public QDialog
{
    Q_OBJECT
public:
    explicit AddEmployee(QWidget *parent = nullptr);

    ~AddEmployee();

private slots:
    // 提交按钮槽函数
    void on_commitPushButton_clicked();
    // 取消按钮槽函数
    void on_cancelPushButton_clicked();

private:
    Ui::AddEmployee *ui;
    EmployeeModel empModel;
    AccountModel accModel;
};

#endif // ADDEMPLOYEE_H
