#include "salesmanclient.h"
#include "ui_client.h"
#include "accountinstance.h"
#include "employeeinfo.h"
#include "customertable.h"
#include "solvedprojecttable.h"

SalesmanClient::SalesmanClient(QWidget *parent)
    : Client(parent)
{
    init();
}

QString SalesmanClient::getClientTitle()
{
    return QString("业务员端");
}

QString SalesmanClient::getUserTitle()
{
    return QString("您好, %1").arg(AccountInstance::instance().getName());
}

void SalesmanClient::addTreeItems(QTreeWidgetItem *root)
{
    root->addChild(new QTreeWidgetItem(root, QStringList("个人信息")));
    root->addChild(new QTreeWidgetItem(root, QStringList("客户管理")));
    root->addChild(new QTreeWidgetItem(root, QStringList("已处理项目管理")));
}

void SalesmanClient::addWidgets()
{
    ui->stackedWidget->addWidget(new EmployeeInfo(this));
    ui->stackedWidget->addWidget(new CustomerTable(this));
    ui->stackedWidget->addWidget(new SolvedProjectTable(this));
}
