#include "financeclient.h"
#include "ui_client.h"
#include "accountinstance.h"
#include "employeeinfo.h"
#include "financeprojtable.h"
#include "solvedprojecttable.h"

FinanceClient::FinanceClient(QWidget *parent)
    : Client(parent)
{
    init();
}

QString FinanceClient::getClientTitle()
{
    return QString("财务端");
}

QString FinanceClient::getUserTitle()
{
    return QString("您好, %1").arg(AccountInstance::instance().getName());
}

void FinanceClient::addTreeItems(QTreeWidgetItem *root)
{
    root->addChild(new QTreeWidgetItem(root, QStringList("个人信息")));
    root->addChild(new QTreeWidgetItem(root, QStringList("待处理项目管理")));
    root->addChild(new QTreeWidgetItem(root, QStringList("已处理项目管理")));
}

void FinanceClient::addWidgets()
{
    ui->stackedWidget->addWidget(new EmployeeInfo(this));
    ui->stackedWidget->addWidget(new FinanceProjTable(this));
    ui->stackedWidget->addWidget(new SolvedProjectTable(this));
}
