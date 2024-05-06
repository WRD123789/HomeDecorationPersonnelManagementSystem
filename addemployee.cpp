#include "addemployee.h"
#include "ui_addemployee.h"

#include <QMessageBox>
#include <QDateTime>
#include <QRandomGenerator>
#include <QException>

AddEmployee::AddEmployee(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddEmployee)
{
    ui->setupUi(this);
    setWindowTitle(QString("添加员工"));
}

AddEmployee::~AddEmployee()
{
    delete ui;
}

void AddEmployee::on_commitPushButton_clicked()
{
    try {
        // 更新员工信息至数据库中
        Employee emp;
        emp.setId(QString("%1%2").arg(QDateTime::currentDateTime().toMSecsSinceEpoch())
                      .arg(QRandomGenerator::global()->generate()));
        emp.setName(ui->nameLineEdit->text());
        emp.setAge(ui->ageLineEdit->text().toInt());
        emp.setGender(ui->genderComboBox->currentText());
        emp.setPhone(ui->phoneLineEdit->text());
        emp.setEmail(ui->emailLineEdit->text());
        empModel.insert(emp);

        Account acc;
        acc.setId(emp.getId());
        acc.setAccount(ui->accountLineEdit->text());
        acc.setPassword(ui->passwordLineEdit->text());
        acc.setIdentity(ui->identityLineEdit->text());
        accModel.insert(acc);

        QMessageBox::information(this, "提示", "添加成功");
        accept();
    } catch (const QException& e) {
        QMessageBox::warning(this, "提示", e.what());
    } catch (...) {
        QMessageBox::warning(this, "提示", "未知错误");
    }
}

void AddEmployee::on_cancelPushButton_clicked()
{
    reject();
}
