#include "modifycustomer.h"
#include "ui_modifycustomer.h"

#include <QMessageBox>
#include <QException>

ModifyCustomer::ModifyCustomer(QString cusId, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ModifyCustomer)
{
    ui->setupUi(this);
    setWindowTitle(QString("修改客户"));
    this->cusId = cusId;

    Customer cus = cusModel.queryById(cusId);
    Project proj = projModel.queryById(cus.getProjId());
    ui->nameLineEdit->setText(cus.getName());
    ui->ageLineEdit->setText(QString::number(cus.getAge()));
    ui->genderComboBox->setCurrentText(cus.getGender());
    ui->phoneLineEdit->setText(cus.getPhone());
    ui->projLineEdit->setText(proj.getName());
    ui->contentLineEdit->setText(proj.getContent());
}

ModifyCustomer::~ModifyCustomer()
{
    delete ui;
}

void ModifyCustomer::on_commitPushButton_clicked()
{
    try {
        // 更新项目信息至数据库中
        Customer customer = cusModel.queryById(cusId);
        customer.setName(ui->nameLineEdit->text());
        customer.setAge(ui->ageLineEdit->text().toInt());
        customer.setGender(ui->genderComboBox->currentText());
        customer.setPhone(ui->phoneLineEdit->text());
        cusModel.update(customer);

        Project project = projModel.queryById(customer.getProjId());
        project.setName(ui->projLineEdit->text());
        project.setContent(ui->contentLineEdit->text());
        projModel.update(project);

        QMessageBox::information(this, "提示", "添加成功");
        accept();
    } catch (const QException& e) {
        QMessageBox::warning(this, "提示", e.what());
    } catch (...) {
        QMessageBox::warning(this, "提示", "未知错误");
    }
}

void ModifyCustomer::on_cancelPushButton_clicked()
{
    reject();
}
