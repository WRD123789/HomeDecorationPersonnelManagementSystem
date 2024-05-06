#include "modifypassword.h"
#include "ui_modifypassword.h"
#include "accountmodel.h"

#include <QMessageBox>
#include <QException>

ModifyPassword::ModifyPassword(QDialog *parent)
    : QDialog(parent)
    , ui(new Ui::ModifyPassword)
{
    ui->setupUi(this);
}

ModifyPassword::~ModifyPassword()
{
    delete ui;
}

ModifyPassword::ModifyPassword(Account &acc, QDialog *parent)
    : ModifyPassword(parent)
{
    this->acc = acc;
    oldPwd = acc.getPassword();
}

void ModifyPassword::on_commitPushButton_clicked()
{
    if (ui->oldPwdLineEdit->text().isEmpty()
        || ui->newPwdLineEdit->text().isEmpty()
        || ui->confirmPwdLineEdit->text().isEmpty()) {
        QMessageBox::warning(this, "提示", "密码不能为空！");
    } else if (ui->confirmPwdLineEdit->text() != ui->newPwdLineEdit->text()) {
        QMessageBox::warning(this, "提示", "两次密码不一致！");
    } else if (ui->oldPwdLineEdit->text() != oldPwd) {
        QMessageBox::warning(this, "提示", "旧密码不一致！");
    } else {
        try {
            QString&& newPwd = ui->newPwdLineEdit->text();
            modifyPwd(newPwd);
            QMessageBox::information(this, "提示", "修改成功!");
            accept();
        } catch (const QException& e) {
            QMessageBox::warning(this, "提示", e.what());
        } catch (...) {
            QMessageBox::warning(this, "提示", "未知错误!");
        }
    }
}

void ModifyPassword::on_cancelPushButton_clicked()
{
    reject();
}

void ModifyPassword::modifyPwd(QString newPwd)
{
    acc.setPassword(newPwd);
    AccountModel().update(acc);
}

