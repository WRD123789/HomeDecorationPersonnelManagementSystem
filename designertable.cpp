#include "designertable.h"
#include "ui_infotable.h"
#include "projectlist.h"

#include <QMessageBox>

DesignerTable::DesignerTable(QWidget *parent)
    : InfoTable(parent)
{
    init();
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
}

QVector<QString> DesignerTable::setColName()
{
    QVector<QString> nameVec;
    nameVec.push_back("编号");
    nameVec.push_back("姓名");
    nameVec.push_back("年龄");
    nameVec.push_back("性别");
    nameVec.push_back("手机号");
    nameVec.push_back("邮箱");
    nameVec.push_back("查看");
    return nameVec;
}

void DesignerTable::loadData()
{
    empMap.clear();
    auto empVec = empModel.queryAllByIdentity(QString("设计师"));
    for (auto& emp : empVec) {
        empMap.insert(emp.getId(), emp);
    }
}

void DesignerTable::showData()
{
    int row = 0;
    ui->tableWidget->setRowCount(empMap.size());

    for (auto& [empId, emp] : empMap.toStdMap()) {
        QPushButton* button1 = new QPushButton("查看", ui->tableWidget);
        connect(button1, &QPushButton::clicked, this, &DesignerTable::onEmpInfoBtnClicked);
        QTableWidgetItem* item1 = new QTableWidgetItem(empId);
        QTableWidgetItem* item2 = new QTableWidgetItem(emp.getName());
        QTableWidgetItem* item3 = new QTableWidgetItem(QString::number(emp.getAge()));
        QTableWidgetItem* item4 = new QTableWidgetItem(emp.getGender());
        QTableWidgetItem* item5 = new QTableWidgetItem(emp.getPhone());
        QTableWidgetItem* item6 = new QTableWidgetItem(emp.getEmail());
        item1->setTextAlignment(Qt::AlignCenter);
        item2->setTextAlignment(Qt::AlignCenter);
        item3->setTextAlignment(Qt::AlignCenter);
        item4->setTextAlignment(Qt::AlignCenter);
        item5->setTextAlignment(Qt::AlignCenter);
        item6->setTextAlignment(Qt::AlignCenter);
        item1->setFlags(item1->flags() & ~Qt::ItemIsEditable);
        item2->setFlags(item2->flags() & ~Qt::ItemIsEditable);
        item3->setFlags(item3->flags() & ~Qt::ItemIsEditable);
        item4->setFlags(item4->flags() & ~Qt::ItemIsEditable);
        item5->setFlags(item5->flags() & ~Qt::ItemIsEditable);
        item6->setFlags(item6->flags() & ~Qt::ItemIsEditable);
        ui->tableWidget->setItem(row, 0, item1);
        ui->tableWidget->setItem(row, 1, item2);
        ui->tableWidget->setItem(row, 2, item3);
        ui->tableWidget->setItem(row, 3, item4);
        ui->tableWidget->setItem(row, 4, item5);
        ui->tableWidget->setItem(row, 5, item6);
        ui->tableWidget->setCellWidget(row, 6, button1);
        ui->tableWidget->setVerticalHeaderItem(row, new QTableWidgetItem(QString::number(row + 1)));
        ++row;
    }
}

void DesignerTable::onEmpInfoBtnClicked()
{
    QPushButton* clickedBtn = qobject_cast<QPushButton*>(sender());
    if (clickedBtn) {
        int row = ui->tableWidget->indexAt(clickedBtn->pos()).row();
        QString empId = ui->tableWidget->item(row, 0)->text();
        ProjectList* projList = new ProjectList(empId);
        projList->show();
    }
}
