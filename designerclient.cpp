#include "designerclient.h"
#include "ui_client.h"
#include "accountinstance.h"
#include "employeeinfo.h"
#include "designerprojtable.h"
#include "solvedprojecttable.h"

DesignerClient::DesignerClient(QWidget *parent)
    : Client(parent)
{
    init();
}

QString DesignerClient::getClientTitle()
{
    return QString("设计师端");
}

QString DesignerClient::getUserTitle()
{
    return QString("您好, %1").arg(AccountInstance::instance().getName());
}

void DesignerClient::addTreeItems(QTreeWidgetItem *root)
{
    root->addChild(new QTreeWidgetItem(root, QStringList("个人信息")));
    root->addChild(new QTreeWidgetItem(root, QStringList("待处理项目管理")));
    root->addChild(new QTreeWidgetItem(root, QStringList("已处理项目管理")));
}

void DesignerClient::addWidgets()
{
    ui->stackedWidget->addWidget(new EmployeeInfo(this));
    ui->stackedWidget->addWidget(new DesignerProjTable(this));
    ui->stackedWidget->addWidget(new SolvedProjectTable(this));
}
