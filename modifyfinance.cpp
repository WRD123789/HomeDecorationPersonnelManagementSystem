#include "modifyfinance.h"
#include "ui_modifyfinance.h"
#include "financemodel.h"

#include <QMessageBox>
#include <QException>

ModifyFinance::ModifyFinance(QDialog *parent)
    : QDialog(parent)
    , ui(new Ui::ModifyFinance)
{
    ui->setupUi(this);
}

ModifyFinance::~ModifyFinance()
{
    delete ui;
}

ModifyFinance::ModifyFinance(Finance &fin, QDialog *parent)
    : ModifyFinance(parent)
{
    this->fin = fin;
}

void ModifyFinance::on_commitPushButton_clicked()
{
    try {
        double deposit = ui->depositLineEdit->text().toDouble();
        double cost = ui->costLineEdit->text().toDouble();
        double amount = ui->amountLineEdit->text().toDouble();
        if (!ui->depositLineEdit->text().isEmpty()) {
            fin.setDeposit(deposit);
        }
        if (!ui->costLineEdit->text().isEmpty()) {
            fin.setCost(cost);
        }
        if (!ui->amountLineEdit->text().isEmpty()) {
            fin.setAmount(amount);
        }
        FinanceModel().update(fin);

        QMessageBox::information(this, "提示", "修改成功!");

        accept();
    } catch (const QException& e) {
        QMessageBox::warning(this, "提示", e.what());
    } catch (...) {
        QMessageBox::warning(this, "提示", "未知错误!");
    }
}

void ModifyFinance::on_cancelPushButton_clicked()
{
    reject();
}
