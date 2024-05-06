#include "designdirectorclient.h"
#include "designdirectorprojtable.h"
#include "ui_client.h"
#include "accountinstance.h"
#include "employeeinfo.h"
#include "designertable.h"
#include "solvedprojecttable.h"

DesignDirectorClient::DesignDirectorClient(QWidget *parent)
    : Client(parent)
{
    init();
}

QString DesignDirectorClient::getClientTitle()
{
    return QString("设计师总监端");
}

QString DesignDirectorClient::getUserTitle()
{
    return QString("您好, %1").arg(AccountInstance::instance().getName());
}

void DesignDirectorClient::addTreeItems(QTreeWidgetItem *root)
{
    root->addChild(new QTreeWidgetItem(root, QStringList("个人信息")));
    root->addChild(new QTreeWidgetItem(root, QStringList("待处理项目管理")));
    root->addChild(new QTreeWidgetItem(root, QStringList("已处理项目管理")));
    root->addChild(new QTreeWidgetItem(root, QStringList("设计师管理")));
}

void DesignDirectorClient::addWidgets()
{
    ui->stackedWidget->addWidget(new EmployeeInfo(this));
    ui->stackedWidget->addWidget(new DesignDirectorProjTable(this));
    ui->stackedWidget->addWidget(new SolvedProjectTable(this));
    ui->stackedWidget->addWidget(new DesignerTable(this));
}
