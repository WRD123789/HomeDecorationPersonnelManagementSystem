#include "financeprojtable.h"
#include "ui_infotable.h"
#include "projectinfo.h"
#include "modifyfinance.h"

#include <QMessageBox>

FinanceProjTable::FinanceProjTable(QWidget *parent)
    : InfoTable(parent)
{
    init();
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
}

QVector<QString> FinanceProjTable::setColName()
{
    QVector<QString> nameVec;
    nameVec.push_back("项目编号");
    nameVec.push_back("项目");
    nameVec.push_back("查看");
    nameVec.push_back("进度");
    nameVec.push_back("开始时间");
    nameVec.push_back("更新时间");
    nameVec.push_back("定金");
    nameVec.push_back("成本");
    nameVec.push_back("总金");
    nameVec.push_back("提交");
    nameVec.push_back("修改");
    nameVec.push_back("取消");
    return nameVec;
}

void FinanceProjTable::loadData()
{
    projMap.clear();
    auto projVec = projModel.queryAll();
    for (auto& proj : projVec) {
        projMap.insert(proj.getId(), proj);
    }

    finMap.clear();
    auto finVec = finModel.queryAllUnSolved();
    for (auto& fin : finVec) {
        finMap.insert(fin.getId(), fin);
    }
}

void FinanceProjTable::showData()
{
    int row = 0;
    ui->tableWidget->setRowCount(finMap.size());

    for (auto& [finId, fin] : finMap.toStdMap()) {
        Project proj = projMap[fin.getProjId()];
        qDebug() << "id: " << finId;

        QPushButton* button2 = nullptr;

        if (proj.getProgress() == "合同设计") {
            button2 = new QPushButton("提交合同", ui->tableWidget);
            button2->setEnabled(true);
        } else if (proj.getProgress() == "定金交付") {
            button2 = new QPushButton("定金交付", ui->tableWidget);
            button2->setEnabled(true);
        } else if (proj.getProgress() == "业务员沟通"
                   || proj.getProgress() == "设计总监分配"
                   || proj.getProgress() == "量房设计"
                   || proj.getProgress() == "平面布置图设计") {
            button2 = new QPushButton("定金未交付", ui->tableWidget);
            button2->setEnabled(false);
        } else {
            button2 = new QPushButton("定金已交付", ui->tableWidget);
            button2->setEnabled(false);
        }

        connect(button2, &QPushButton::clicked,
                this, &FinanceProjTable::onCommitBtnClicked);

        QPushButton* button1 = new QPushButton("查看", ui->tableWidget);
        QPushButton* button3 = new QPushButton("修改", ui->tableWidget);
        QPushButton* button4 = new QPushButton("取消", ui->tableWidget);
        connect(button1, &QPushButton::clicked,
                this, &FinanceProjTable::onProjDetailBtnClicked);
        connect(button3, &QPushButton::clicked,
                this, &FinanceProjTable::onModifyBtnClicked);
        connect(button4, &QPushButton::clicked,
                this, &FinanceProjTable::onCancelBtnClicked);
        QTableWidgetItem* item1 = new QTableWidgetItem(proj.getId());
        QTableWidgetItem* item2 = new QTableWidgetItem(proj.getName());
        QTableWidgetItem* item3 = new QTableWidgetItem(proj.getProgress());
        QTableWidgetItem* item4 = new QTableWidgetItem(proj.getStartTime()
                                                           .toString("yyyy-MM-dd HH:mm"));
        QTableWidgetItem* item5 = new QTableWidgetItem(proj.getUpdateTime()
                                                           .toString("yyyy-MM-dd HH:mm"));
        QTableWidgetItem* item6 = new QTableWidgetItem(QString::number(
                                                            fin.getDeposit(), 'f', 2));
        QTableWidgetItem* item7 = new QTableWidgetItem(QString::number(
                                                            fin.getCost(), 'f', 2));
        QTableWidgetItem* item8 = new QTableWidgetItem(QString::number(
                                                            fin.getAmount(), 'f', 2));
        item1->setTextAlignment(Qt::AlignCenter);
        item2->setTextAlignment(Qt::AlignCenter);
        item3->setTextAlignment(Qt::AlignCenter);
        item4->setTextAlignment(Qt::AlignCenter);
        item5->setTextAlignment(Qt::AlignCenter);
        item6->setTextAlignment(Qt::AlignCenter);
        item7->setTextAlignment(Qt::AlignCenter);
        item8->setTextAlignment(Qt::AlignCenter);
        item1->setFlags(item1->flags() & ~Qt::ItemIsEditable);
        item2->setFlags(item2->flags() & ~Qt::ItemIsEditable);
        item3->setFlags(item3->flags() & ~Qt::ItemIsEditable);
        item4->setFlags(item4->flags() & ~Qt::ItemIsEditable);
        item5->setFlags(item5->flags() & ~Qt::ItemIsEditable);
        item6->setFlags(item6->flags() & ~Qt::ItemIsEditable);
        item7->setFlags(item7->flags() & ~Qt::ItemIsEditable);
        item8->setFlags(item8->flags() & ~Qt::ItemIsEditable);
        ui->tableWidget->setItem(row, 0, item1);
        ui->tableWidget->setItem(row, 1, item2);
        ui->tableWidget->setItem(row, 3, item3);
        ui->tableWidget->setItem(row, 4, item4);
        ui->tableWidget->setItem(row, 5, item5);
        ui->tableWidget->setItem(row, 6, item6);
        ui->tableWidget->setItem(row, 7, item7);
        ui->tableWidget->setItem(row, 8, item8);
        ui->tableWidget->setCellWidget(row, 2, button1);
        ui->tableWidget->setCellWidget(row, 9, button2);
        ui->tableWidget->setCellWidget(row, 10, button3);
        ui->tableWidget->setCellWidget(row, 11, button4);
        ui->tableWidget->setVerticalHeaderItem(
            row, new QTableWidgetItem(QString::number(row + 1)));
        ++row;
    }
}

void FinanceProjTable::onProjDetailBtnClicked()
{
    QPushButton* clickedBtn = qobject_cast<QPushButton*>(sender());
    if (clickedBtn) {
        int row = ui->tableWidget->indexAt(clickedBtn->pos()).row();
        QString projId = ui->tableWidget->item(row, 0)->text();
        ProjectInfo* projInfo = new ProjectInfo(projId);
        projInfo->show();
    }
}

void FinanceProjTable::onCommitBtnClicked()
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
            if (btnText == "提交合同") {
                proj.setProgress(QString("定金交付"));
            } else if (btnText == "定金交付") {
                proj.setProgress(QString("深入图设计"));
            }
            proj.setUpdateTime(QDateTime::currentDateTime());
            ProjectModel().update(proj);

            on_refreshPushButton_clicked();
        }
    }
}

void FinanceProjTable::onCancelBtnClicked()
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

void FinanceProjTable::onModifyBtnClicked()
{
    QPushButton* clickedBtn = qobject_cast<QPushButton*>(sender());
    if (clickedBtn) {
        int row = ui->tableWidget->indexAt(clickedBtn->pos()).row();
        QString projId = ui->tableWidget->item(row, 0)->text();
        Finance fin = finModel.queryByProjId(projId);
        ModifyFinance modifyFin(fin);
        modifyFin.exec();
    }
}
