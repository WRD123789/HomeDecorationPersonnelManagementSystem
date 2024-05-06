#include "projectdirectorprojtable.h"
#include "ui_infotable.h"
#include "employeemodel.h"
#include "projectinfo.h"

#include <QComboBox>
#include <QMessageBox>

ProjectDirectorProjTable::ProjectDirectorProjTable(QWidget *parent)
    : InfoTable(parent)
{
    init();
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
}

QVector<QString> ProjectDirectorProjTable::setColName()
{
    QVector<QString> nameVec;
    nameVec.push_back("编号");
    nameVec.push_back("项目");
    nameVec.push_back("查看");
    nameVec.push_back("进度");
    nameVec.push_back("开始时间");
    nameVec.push_back("更新时间");
    nameVec.push_back("项目经理");
    nameVec.push_back("分配");
    nameVec.push_back("取消");
    return nameVec;
}

void ProjectDirectorProjTable::loadData()
{
    projMap.clear();
    auto projVec = projModel.queryAllByProgress(QString("项目总经理分配"));
    for (auto& proj : projVec) {
        projMap.insert(proj.getId(), proj);
    }
}

void ProjectDirectorProjTable::showData()
{
    int row = 0;
    ui->tableWidget->setRowCount(projMap.size());

    QVector<Employee> managers = EmployeeModel().queryAllByIdentity(QString("项目经理"));

    for (auto& [projId, proj] : projMap.toStdMap()) {
        QPushButton* button2 = nullptr;

        if (proj.getProgress() == "项目总经理分配") {
            button2 = new QPushButton("分配", ui->tableWidget);
            connect(button2, &QPushButton::clicked,
                    this, &ProjectDirectorProjTable::onAllocationBtnClicked);
        } else {
            button2 = new QPushButton("已分配", ui->tableWidget);
            button2->setEnabled(false);
        }

        QPushButton* button1 = new QPushButton("查看", ui->tableWidget);
        QPushButton* button3 = new QPushButton("取消", ui->tableWidget);
        connect(button1, &QPushButton::clicked,
                this, &ProjectDirectorProjTable::onProjDetailBtnClicked);
        connect(button3, &QPushButton::clicked,
                this, &ProjectDirectorProjTable::onCancelBtnClicked);
        QTableWidgetItem* item1 = new QTableWidgetItem(projId);
        QTableWidgetItem* item2 = new QTableWidgetItem(proj.getName());
        QTableWidgetItem* item3 = new QTableWidgetItem(proj.getProgress());
        QTableWidgetItem* item4 = new QTableWidgetItem(proj.getStartTime()
                                                           .toString("yyyy-MM-dd HH:mm"));
        QTableWidgetItem* item5 = new QTableWidgetItem(proj.getUpdateTime()
                                                           .toString("yyyy-MM-dd HH:mm"));

        QComboBox* box = new QComboBox(ui->tableWidget);
        for (int i = 0; i < managers.size(); i += 1) {
            box->addItem(managers[i].getName());
        }

        item1->setTextAlignment(Qt::AlignCenter);
        item2->setTextAlignment(Qt::AlignCenter);
        item3->setTextAlignment(Qt::AlignCenter);
        item4->setTextAlignment(Qt::AlignCenter);
        item5->setTextAlignment(Qt::AlignCenter);
        item1->setFlags(item1->flags() & ~Qt::ItemIsEditable);
        item2->setFlags(item2->flags() & ~Qt::ItemIsEditable);
        item3->setFlags(item3->flags() & ~Qt::ItemIsEditable);
        item4->setFlags(item4->flags() & ~Qt::ItemIsEditable);
        item5->setFlags(item5->flags() & ~Qt::ItemIsEditable);
        ui->tableWidget->setItem(row, 0, item1);
        ui->tableWidget->setItem(row, 1, item2);
        ui->tableWidget->setItem(row, 3, item3);
        ui->tableWidget->setItem(row, 4, item4);
        ui->tableWidget->setItem(row, 5, item5);
        ui->tableWidget->setCellWidget(row, 2, button1);
        ui->tableWidget->setCellWidget(row, 7, button2);
        ui->tableWidget->setCellWidget(row, 8, button3);
        ui->tableWidget->setCellWidget(row, 6, box);
        ui->tableWidget->setVerticalHeaderItem(row, new QTableWidgetItem(QString::number(row + 1)));
        ++row;
    }
}

void ProjectDirectorProjTable::onProjDetailBtnClicked()
{
    QPushButton* clickedBtn = qobject_cast<QPushButton*>(sender());
    if (clickedBtn) {
        int row = ui->tableWidget->indexAt(clickedBtn->pos()).row();
        QString projId = ui->tableWidget->item(row, 0)->text();
        ProjectInfo* projInfo = new ProjectInfo(projId);
        projInfo->show();
    }
}

void ProjectDirectorProjTable::onAllocationBtnClicked()
{
    QPushButton *clickedBtn = qobject_cast<QPushButton *>(sender());
    if (clickedBtn) {
        auto reply = QMessageBox::information(
            this, "提示", "是否分配项目给该项目经理？",
            QMessageBox::StandardButtons(QMessageBox::Yes | QMessageBox::No)
            );

        if (reply == QMessageBox::Yes) {
            int row = ui->tableWidget->indexAt(clickedBtn->pos()).row();
            QString projId = ui->tableWidget->item(row, 0)->text();
            QString managerName = qobject_cast<QComboBox*>(
                                       ui->tableWidget->cellWidget(row, 6))->currentText();
            QString managerId = EmployeeModel().queryByName(managerName).getId();

            Project proj = projModel.queryById(projId);
            proj.setProgress(QString("施工"));
            proj.setUpdateTime(QDateTime::currentDateTime());
            proj.setProjManagerId(managerId);
            ProjectModel().update(proj);

            on_refreshPushButton_clicked();
        }
    }
}

void ProjectDirectorProjTable::onCancelBtnClicked()
{
    QPushButton *clickedBtn = qobject_cast<QPushButton *>(sender());
    if (clickedBtn) {
        auto reply = QMessageBox::information(
            this, "提示", "是否取消该项目？",
            QMessageBox::StandardButtons(QMessageBox::Yes | QMessageBox::No)
            );

        if (reply == QMessageBox::Yes) {
            int row = ui->tableWidget->indexAt(clickedBtn->pos()).row();
            QString projId = ui->tableWidget->item(row, 0)->text();

            Project proj = projModel.queryById(projId);
            proj.setProgress(QString("已取消"));
            proj.setUpdateTime(QDateTime::currentDateTime());
            ProjectModel().update(proj);

            on_refreshPushButton_clicked();
        }
    }
}
