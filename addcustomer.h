#ifndef ADDCUSTOMER_H
#define ADDCUSTOMER_H

#include "customermodel.h"
#include "projectmodel.h"

#include <QDialog>

namespace Ui {
class AddCustomer;
}

class AddCustomer : public QDialog
{
    Q_OBJECT
public:
    explicit AddCustomer(QWidget *parent = nullptr);

    ~AddCustomer();

private slots:
    // 提交按钮槽函数
    void on_commitPushButton_clicked();
    // 取消按钮槽函数
    void on_cancelPushButton_clicked();

private:
    Ui::AddCustomer *ui;
    CustomerModel cusModel;
    ProjectModel projModel;
};

#endif // ADDCUSTOMER_H
