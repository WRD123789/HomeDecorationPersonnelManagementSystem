#include "adminemployeetable.h"
#include "ui_infotable.h"
#include "addemployee.h"
#include "employeeinfo.h"

#include <QMessageBox>

AdminEmployeeTable::AdminEmployeeTable(QWidget *parent)
    : InfoTable(parent)
{
    init();
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
}

QVector<QString> AdminEmployeeTable::setColName()
{
    QVector<QString> nameVec;
    nameVec.push_back("编号");
    nameVec.push_back("姓名");
    nameVec.push_back("年龄");
    nameVec.push_back("性别");
    nameVec.push_back("职位");
    nameVec.push_back("手机号");
    nameVec.push_back("邮箱");
    nameVec.push_back("修改");
    nameVec.push_back("操作");
    nameVec.push_back("删除");
    return nameVec;
}

void AdminEmployeeTable::loadData()
{
    empMap.clear();
    auto empVec = empModel.queryAll();
    for (auto& emp : empVec) {
        empMap.insert(emp.getId(), emp);
    }
}

void AdminEmployeeTable::showData()
{
    int row = 0;
    ui->tableWidget->setRowCount(empMap.size());

    for (auto& [empId, emp] : empMap.toStdMap()) {
        Account acc = AccountModel().queryById(empId);
        QPushButton* button1 = new QPushButton("修改", ui->tableWidget);
        QPushButton* button2 = new QPushButton("重置密码", ui->tableWidget);
        QPushButton* button3 = new QPushButton("删除", ui->tableWidget);
        connect(button1, &QPushButton::clicked,
                this, &AdminEmployeeTable::onModifyEmpBtnClicked);
        connect(button2, &QPushButton::clicked,
                this, &AdminEmployeeTable::onResetPwdBtnClicked);
        connect(button3, &QPushButton::clicked,
                this, &AdminEmployeeTable::onDelEmpBtnClicked);
        QTableWidgetItem* item1 = new QTableWidgetItem(empId);
        QTableWidgetItem* item2 = new QTableWidgetItem(emp.getName());
        QTableWidgetItem* item3 = new QTableWidgetItem(QString::number(emp.getAge()));
        QTableWidgetItem* item4 = new QTableWidgetItem(emp.getGender());
        QTableWidgetItem* item5 = new QTableWidgetItem(emp.getPhone());
        QTableWidgetItem* item6 = new QTableWidgetItem(emp.getEmail());
        QTableWidgetItem* item7 = new QTableWidgetItem(acc.getIdentity());
        item1->setTextAlignment(Qt::AlignCenter);
        item2->setTextAlignment(Qt::AlignCenter);
        item3->setTextAlignment(Qt::AlignCenter);
        item4->setTextAlignment(Qt::AlignCenter);
        item5->setTextAlignment(Qt::AlignCenter);
        item6->setTextAlignment(Qt::AlignCenter);
        item7->setTextAlignment(Qt::AlignCenter);
        item1->setFlags(item1->flags() & ~Qt::ItemIsEditable);
        item2->setFlags(item2->flags() & ~Qt::ItemIsEditable);
        item3->setFlags(item3->flags() & ~Qt::ItemIsEditable);
        item4->setFlags(item4->flags() & ~Qt::ItemIsEditable);
        item5->setFlags(item5->flags() & ~Qt::ItemIsEditable);
        item6->setFlags(item6->flags() & ~Qt::ItemIsEditable);
        item7->setFlags(item7->flags() & ~Qt::ItemIsEditable);
        ui->tableWidget->setItem(row, 0, item1);
        ui->tableWidget->setItem(row, 1, item2);
        ui->tableWidget->setItem(row, 2, item3);
        ui->tableWidget->setItem(row, 3, item4);
        ui->tableWidget->setItem(row, 4, item7);
        ui->tableWidget->setItem(row, 5, item5);
        ui->tableWidget->setItem(row, 6, item6);
        ui->tableWidget->setCellWidget(row, 7, button1);
        ui->tableWidget->setCellWidget(row, 8, button2);
        ui->tableWidget->setCellWidget(row, 9, button3);
        ui->tableWidget->setVerticalHeaderItem(row, new QTableWidgetItem(QString::number(row + 1)));
        ++row;
    }
}

void AdminEmployeeTable::addBtn()
{
    QPushButton *btn = new QPushButton("新增", this);
    QFont font("宋体", 12);
    font.setWeight(QFont::Bold);
    btn->setFont(font);
    btn->setFocusPolicy(Qt::StrongFocus);
    ui->horizontalLayout->addWidget(btn);
    connect(btn,
            &QPushButton::clicked,
            this,
            &AdminEmployeeTable::onAddEmpBtnClicked
    );
}

void AdminEmployeeTable::onAddEmpBtnClicked()
{
    AddEmployee addEmployee(this);
    if (addEmployee.exec())
        on_refreshPushButton_clicked();
}

void AdminEmployeeTable::onModifyEmpBtnClicked()
{
    QPushButton *clickedBtn = qobject_cast<QPushButton *>(sender());
    if (clickedBtn)
    {
        int row = ui->tableWidget->indexAt(clickedBtn->pos()).row();
        QString empId = ui->tableWidget->item(row, 0)->text();
        Employee &emp = empMap[empId];
        EmployeeInfo* employeeInfo = new EmployeeInfo(emp);
        employeeInfo->hideModifyPwdBtn()->show();
    }
}

void AdminEmployeeTable::onDelEmpBtnClicked()
{
    QPushButton *clickedBtn = qobject_cast<QPushButton *>(sender());
    if (clickedBtn)
    {
        auto reply = QMessageBox::information(
            this, "提示", "是否删除该员工？",
            QMessageBox::StandardButtons(QMessageBox::Yes | QMessageBox::No)
            );

        if (reply == QMessageBox::Yes)
        {
            int row = ui->tableWidget->indexAt(clickedBtn->pos()).row();
            QString empId = ui->tableWidget->item(row, 0)->text();
            Employee &emp = empMap[empId];
            empModel.remove(emp);

            Account acc = AccountModel().queryById(empId);
            AccountModel().remove(acc);

            on_refreshPushButton_clicked();
        }
    }
}

void AdminEmployeeTable::onResetPwdBtnClicked()
{
    QPushButton *clickedBtn = qobject_cast<QPushButton *>(sender());
    if (clickedBtn)
    {
        QMessageBox msgBox;
        msgBox.setStyleSheet("background-color: white;");
        auto reply = msgBox.information(
            this, "提示", "是否重置密码？",
            QMessageBox::StandardButtons(QMessageBox::Yes | QMessageBox::No)
            );
        if (reply == QMessageBox::Yes)
        {
            int row = ui->tableWidget->indexAt(clickedBtn->pos()).row();
            QString empId = ui->tableWidget->item(row, 0)->text();
            Account acc = AccountModel().queryById(empId);
            acc.setPassword("123456");
            AccountModel().update(acc);
        }
    }
}
