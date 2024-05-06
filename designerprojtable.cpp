#include "designerprojtable.h"
#include "ui_infotable.h"
#include "projectinfo.h"
#include "accountinstance.h"

#include <QMessageBox>

DesignerProjTable::DesignerProjTable(QWidget *parent)
    : InfoTable(parent)
{
    init();
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
}

QVector<QString> DesignerProjTable::setColName()
{
    QVector<QString> nameVec;
    nameVec.push_back("编号");
    nameVec.push_back("项目");
    nameVec.push_back("查看");
    nameVec.push_back("进度");
    nameVec.push_back("开始时间");
    nameVec.push_back("更新时间");
    nameVec.push_back("提交");
    nameVec.push_back("取消");
    return nameVec;
}

void DesignerProjTable::loadData()
{
    projMap.clear();
    auto projVec0 = projModel.queryAllByEmpId(AccountInstance::instance().getId());
    for (auto& proj : projVec0) {
        projMap.insert(proj.getId(), proj);
    }
}

void DesignerProjTable::showData()
{
    int row = 0;
    ui->tableWidget->setRowCount(projMap.size());

    for (auto& [projId, proj] : projMap.toStdMap()) {
        QPushButton* button2 = nullptr;

        if (proj.getProgress() == "量房设计") {
            button2 = new QPushButton("提交量房设计图", ui->tableWidget);
        } else if (proj.getProgress() == "平面布置图设计") {
            button2 = new QPushButton("提交平面设计图", ui->tableWidget);
        } else if (proj.getProgress() == "深入图设计") {
            button2 = new QPushButton("提交深入图", ui->tableWidget);
        } else if (proj.getProgress() == "效果图设计") {
            button2 = new QPushButton("提交效果图", ui->tableWidget);
        } else if (proj.getProgress() == "预算表提交") {
            button2 = new QPushButton("提交预算表", ui->tableWidget);
        }

        connect(button2, &QPushButton::clicked,
                this, &DesignerProjTable::onCommitBtnClicked);

        QPushButton* button1 = new QPushButton("查看", ui->tableWidget);
        QPushButton* button3 = new QPushButton("取消", ui->tableWidget);
        connect(button1, &QPushButton::clicked,
                this, &DesignerProjTable::onProjDetailBtnClicked);
        connect(button3, &QPushButton::clicked,
                this, &DesignerProjTable::onCancelBtnClicked);
        QTableWidgetItem* item1 = new QTableWidgetItem(projId);
        QTableWidgetItem* item2 = new QTableWidgetItem(proj.getName());
        QTableWidgetItem* item3 = new QTableWidgetItem(proj.getProgress());
        QTableWidgetItem* item4 = new QTableWidgetItem(proj.getStartTime()
                                                           .toString("yyyy-MM-dd HH:mm"));
        QTableWidgetItem* item5 = new QTableWidgetItem(proj.getUpdateTime()
                                                           .toString("yyyy-MM-dd HH:mm"));
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
        ui->tableWidget->setCellWidget(row, 6, button2);
        ui->tableWidget->setCellWidget(row, 7, button3);
        ui->tableWidget->setVerticalHeaderItem(row, new QTableWidgetItem(QString::number(row + 1)));
        ++row;
    }
}

void DesignerProjTable::onProjDetailBtnClicked()
{
    QPushButton* clickedBtn = qobject_cast<QPushButton*>(sender());
    if (clickedBtn) {
        int row = ui->tableWidget->indexAt(clickedBtn->pos()).row();
        QString projId = ui->tableWidget->item(row, 0)->text();
        ProjectInfo* projInfo = new ProjectInfo(projId);
        projInfo->show();
    }
}

void DesignerProjTable::onCommitBtnClicked()
{
    QPushButton *clickedBtn = qobject_cast<QPushButton *>(sender());
    if (clickedBtn) {
        auto reply = QMessageBox::information(
            this, "提示", QString("是否%1？").arg(clickedBtn->text()),
            QMessageBox::StandardButtons(QMessageBox::Yes | QMessageBox::No)
            );

        if (reply == QMessageBox::Yes) {
            int row = ui->tableWidget->indexAt(clickedBtn->pos()).row();
            QString projId = ui->tableWidget->item(row, 0)->text();
            Project proj = projModel.queryById(projId);
            QString btnText = clickedBtn->text();
            if (btnText == "提交量房设计图") {
                proj.setProgress(QString("平面布置图设计"));
            } else if (btnText == "提交平面设计图") {
                proj.setProgress(QString("合同设计"));
            } else if (btnText == "提交深入图") {
                proj.setProgress(QString("效果图设计"));
            } else if (btnText == "提交效果图") {
                proj.setProgress(QString("预算表提交"));
            } else if (btnText == "提交预算表") {
                proj.setProgress(QString("项目总经理分配"));
            }
            proj.setUpdateTime(QDateTime::currentDateTime());
            ProjectModel().update(proj);

            on_refreshPushButton_clicked();
        }
    }
}

void DesignerProjTable::onCancelBtnClicked()
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
