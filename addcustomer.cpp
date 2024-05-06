#include "addcustomer.h"
#include "ui_addcustomer.h"
#include "financemodel.h"

#include <QException>
#include <QMessageBox>
#include <QDateTime>
#include <QRandomGenerator>
#include <accountinstance.h>

AddCustomer::AddCustomer(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddCustomer)
{
    ui->setupUi(this);
    setWindowTitle(QString("添加客户"));
}

AddCustomer::~AddCustomer()
{
    delete ui;
}

void AddCustomer::on_commitPushButton_clicked()
{
    try {
        // 更新项目信息至数据库中
        Project proj;
        QDateTime curTime = QDateTime::currentDateTime();
        // 根据时间戳和随机数来生成唯一编号
        QString projId = QString("%1%2").arg(QDateTime::currentDateTime().toMSecsSinceEpoch())
                             .arg(QRandomGenerator::global()->generate());
        proj.setId(projId);
        proj.setName(ui->projLineEdit->text());
        proj.setContent(ui->contentLineEdit->text());
        proj.setStartTime(curTime);
        proj.setProgress(QString("业务员沟通"));
        proj.setUpdateTime(curTime);
        proj.setSalesmanId(AccountInstance::instance().getId());
        proj.setDesignerId(QString(""));
        proj.setProjManagerId(QString(""));
        projModel.insert(proj);

        // 更新客户信息至数据库中
        Customer cus;
        cus.setId(QString("%1%2").arg(QDateTime::currentDateTime().toMSecsSinceEpoch())
                      .arg(QRandomGenerator::global()->generate()));
        cus.setName(ui->nameLineEdit->text());
        cus.setAge(ui->ageLineEdit->text().toInt());
        cus.setGender(ui->genderComboBox->currentText());
        cus.setPhone(ui->phoneLineEdit->text());
        cus.setProjId(projId);
        cusModel.insert(cus);

        // 更新财务信息至数据库中
        Finance fin;
        fin.setId(QString("%1%2").arg(QDateTime::currentDateTime().toMSecsSinceEpoch())
                      .arg(QRandomGenerator::global()->generate()));
        fin.setDeposit(0);
        fin.setCost(0);
        fin.setAmount(0);
        fin.setProjId(projId);
        FinanceModel().insert(fin);

        QMessageBox::information(this, "提示", "添加成功");
        accept();
    } catch (const QException& e) {
        QMessageBox::warning(this, "提示", e.what());
    } catch (...) {
        QMessageBox::warning(this, "提示", "未知错误");
    }
}

void AddCustomer::on_cancelPushButton_clicked()
{
    reject();
}

