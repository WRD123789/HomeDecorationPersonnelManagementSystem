#include "employeeinfo.h"
#include "accountinstance.h"
#include "ui_information.h"
#include "modifypassword.h"
#include "account.h"
#include "accountmodel.h"

#include <QException>
#include <QMessageBox>

EmployeeInfo::EmployeeInfo(QWidget *parent)
    : Information(parent)
{
    self = empModel.queryById(AccountInstance::instance().getId());
    init();
}

EmployeeInfo::EmployeeInfo(Employee &emp, QWidget *parent)
    : Information(parent)
{
    self = emp;
    init();
}

void EmployeeInfo::commit()
{
    Employee temp = self;
    self.setName (ui->nameLineEdit ->text());
    self.setAge(ui->ageLineEdit->text().toInt());
    self.setGender(ui->genderLineEdit->text());
    self.setPhone(ui->phoneLineEdit->text());
    self.setGender(ui->genderLineEdit->text());
    try {
        empModel.update(self);
    } catch (const QException& e) {
        QMessageBox::warning(this, "错误", e.what());
        self = temp;
        loadInfo();
    } catch (...) {
        QMessageBox::warning(this, "提示", "未知错误!");
    }
}

void EmployeeInfo::modifyPwd()
{
    Account acc = AccountModel().queryById(self.getId());
    ModifyPassword modifyPassword(acc);
    modifyPassword.exec();
}

void EmployeeInfo::loadInfo()
{
    ui->numberLineEdit->setText(self.getId());
    ui->nameLineEdit->setText(self.getName());
    ui->genderLineEdit->setText(self.getGender());
    ui->ageLineEdit->setText(QString::number(self.getAge()));
    ui->phoneLineEdit ->setText(self.getPhone());
    ui->emailLineEdit ->setText(self.getEmail());
}
