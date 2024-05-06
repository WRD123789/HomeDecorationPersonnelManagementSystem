#ifndef MODIFYCUSTOMER_H
#define MODIFYCUSTOMER_H

#include "customermodel.h"
#include "projectmodel.h"

namespace Ui{
class ModifyCustomer;
}

#include <QDialog>

class ModifyCustomer : public QDialog
{
    Q_OBJECT
public:
    explicit ModifyCustomer(QString cusId, QWidget *parent = nullptr);

    ~ModifyCustomer();

private slots:
    // 提交按钮槽函数
    void on_commitPushButton_clicked();
    // 取消按钮槽函数
    void on_cancelPushButton_clicked();

private:
    Ui::ModifyCustomer *ui;
    CustomerModel cusModel;
    ProjectModel projModel;
    QString cusId;
};

#endif // MODIFYCUSTOMER_H
