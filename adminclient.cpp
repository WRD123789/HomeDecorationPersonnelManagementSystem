#include "adminclient.h"
#include "ui_client.h"
#include "accountinstance.h"
#include "employeeinfo.h"
#include "admincustomertable.h"
#include "adminemployeetable.h"
#include "adminprojecttable.h"

AdminClient::AdminClient(QWidget *parent)
    : Client(parent)
{
    init();
}

QString AdminClient::getClientTitle()
{
    return QString("管理员端");
}

QString AdminClient::getUserTitle()
{
    return QString("您好, %1").arg(AccountInstance::instance().getName());
}

void AdminClient::addTreeItems(QTreeWidgetItem *root)
{
    root->addChild(new QTreeWidgetItem(root, QStringList("个人信息")));
    root->addChild(new QTreeWidgetItem(root, QStringList("员工管理")));
    root->addChild(new QTreeWidgetItem(root, QStringList("客户管理")));
    root->addChild(new QTreeWidgetItem(root, QStringList("项目管理")));
}

void AdminClient::addWidgets()
{
    ui->stackedWidget->addWidget(new EmployeeInfo(this));
    ui->stackedWidget->addWidget(new AdminEmployeeTable(this));
    ui->stackedWidget->addWidget(new AdminCustomerTable(this));
    ui->stackedWidget->addWidget(new AdminProjectTable(this));
}
