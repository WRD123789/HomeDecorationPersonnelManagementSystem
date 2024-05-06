#include "projectdirectorclient.h"
#include "accountinstance.h"
#include "ui_client.h"
#include "employeeinfo.h"
#include "projectdirectorprojtable.h"
#include "projectmanagertable.h"
#include "solvedprojecttable.h"

ProjectDirectorClient::ProjectDirectorClient(QWidget *parent)
    : Client(parent)
{
    init();
}

QString ProjectDirectorClient::getClientTitle()
{
    return QString("项目总经理端");
}

QString ProjectDirectorClient::getUserTitle()
{
    return QString("您好, %1").arg(AccountInstance::instance().getName());
}

void ProjectDirectorClient::addTreeItems(QTreeWidgetItem *root)
{
    root->addChild(new QTreeWidgetItem(root, QStringList("个人信息")));
    root->addChild(new QTreeWidgetItem(root, QStringList("待处理项目管理")));
    root->addChild(new QTreeWidgetItem(root, QStringList("已处理项目管理")));
    root->addChild(new QTreeWidgetItem(root, QStringList("项目经理管理")));
}

void ProjectDirectorClient::addWidgets()
{
    ui->stackedWidget->addWidget(new EmployeeInfo(this));
    ui->stackedWidget->addWidget(new ProjectDirectorProjTable(this));
    ui->stackedWidget->addWidget(new SolvedProjectTable(this));
    ui->stackedWidget->addWidget(new ProjectManagerTable(this));
}
