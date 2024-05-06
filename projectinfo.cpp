#include "projectinfo.h"
#include "ui_projectinfo.h"
#include "customermodel.h"
#include "projectmodel.h"
#include "employeemodel.h"

ProjectInfo::ProjectInfo(QWidget *parent)
    : QWidget{parent}
    , ui(new Ui::ProjectInfo)
{
    ui->setupUi(this);

    setAttribute(Qt::WA_DeleteOnClose);
    setWindowTitle(QString("项目详情"));
}

ProjectInfo::ProjectInfo(QString projId, QWidget *parent)
    : ProjectInfo(parent)
{
    Customer cus = CustomerModel().queryByProjId(projId);
    Project proj = ProjectModel().queryById(projId);
    EmployeeModel empModel;
    ui->cusLineEdit->setText(cus.getName());
    ui->pNameLineEdit->setText(proj.getName());
    ui->salesmanLineEdit->setText(empModel.queryById(proj.getSalesmanId()).getName());
    ui->designerLineEdit->setText(empModel.queryById(proj.getDesignerId()).getName());
    ui->managerLineEdit->setText(empModel.queryById(proj.getProjManagerId()).getName());
    ui->progLineEdit->setText(proj.getProgress());
    ui->descTextEdit->setText(proj.getContent());
}

ProjectInfo::~ProjectInfo()
{
    delete ui;
}

