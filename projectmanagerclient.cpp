#include "projectmanagerclient.h"
#include "ui_client.h"
#include "accountinstance.h"
#include "employeeinfo.h"
#include "managerprojtable.h"
#include "solvedprojecttable.h"

ProjectManagerClient::ProjectManagerClient(QWidget *parent)
    : Client(parent)
{
    init();
}

QString ProjectManagerClient::getClientTitle()
{
    return QString("项目经理端");
}

QString ProjectManagerClient::getUserTitle()
{
    return QString("您好, %1").arg(AccountInstance::instance().getName());
}

void ProjectManagerClient::addTreeItems(QTreeWidgetItem *root)
{
    root->addChild(new QTreeWidgetItem(root, QStringList("个人信息")));
    root->addChild(new QTreeWidgetItem(root, QStringList("待处理项目管理")));
    root->addChild(new QTreeWidgetItem(root, QStringList("已处理项目管理")));
}

void ProjectManagerClient::addWidgets()
{
    ui->stackedWidget->addWidget(new EmployeeInfo(this));
    ui->stackedWidget->addWidget(new ManagerProjTable(this));
    ui->stackedWidget->addWidget(new SolvedProjectTable(this));
}
