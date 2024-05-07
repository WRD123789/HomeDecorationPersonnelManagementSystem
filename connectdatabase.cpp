#include "connectdatabase.h"
#include "ui_connectdatabase.h"

#include <QMessageBox>
#include <QException>
#include <QSqlDatabase>

ConnectDataBase::ConnectDataBase(QDialog *parent)
    : QDialog(parent)
    , ui(new Ui::ConnectDataBase)
{
    ui->setupUi(this);
}

ConnectDataBase::~ConnectDataBase()
{
    delete ui;
}

void ConnectDataBase::on_connectPushButton_clicked()
{
    if (ui->ipLineEdit->text().isEmpty()
        || ui->portLineEdit->text().isEmpty()
        || ui->accountLineEdit->text().isEmpty()
        || ui->pwdLineEdit->text().isEmpty()) {
        QMessageBox::warning(this, "提示", "内容不能为空！");
    } else {
        QString ip = ui->ipLineEdit->text();
        int port = ui->portLineEdit->text().toInt();
        QString account = ui->accountLineEdit->text();
        QString pwd = ui->pwdLineEdit->text();

        // 连接
        QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
        db.setHostName(ip);
        db.setPort(port);
        db.setDatabaseName("home_decoration");
        db.setUserName(account);
        db.setPassword(pwd);
        if(!db.open()){
            QMessageBox::critical(this, "错误", "数据库连接失败!");
            reject();
        }
        accept();
    }
}

void ConnectDataBase::on_cancelPushButton_clicked()
{
    reject();
}
