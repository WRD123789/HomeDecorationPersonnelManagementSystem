#include "managerprojtable.h"
#include "ui_infotable.h"
#include "accountinstance.h"
#include "projectinfo.h"
#include "recvfile.h"
#include "imageviewerdialog.h"

#include <QMessageBox>

ManagerProjTable::ManagerProjTable(QWidget *parent)
    : InfoTable(parent)
{
    init();
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
}

QVector<QString> ManagerProjTable::setColName()
{
    QVector<QString> nameVec;
    nameVec.push_back("编号");
    nameVec.push_back("项目");
    nameVec.push_back("查看");
    nameVec.push_back("进度");
    nameVec.push_back("开始时间");
    nameVec.push_back("更新时间");
    nameVec.push_back("量房设计图");
    nameVec.push_back("平面设计图");
    nameVec.push_back("深入图");
    nameVec.push_back("效果图");
    nameVec.push_back("提交");
    nameVec.push_back("取消");
    return nameVec;
}

void ManagerProjTable::loadData()
{
    projMap.clear();
    auto projVec0 = projModel.queryAllByEmpId(AccountInstance::instance().getId());
    for (auto& proj : projVec0) {
        projMap.insert(proj.getId(), proj);
    }
}

void ManagerProjTable::showData()
{
    int row = 0;
    ui->tableWidget->setRowCount(projMap.size());

    for (auto& [projId, proj] : projMap.toStdMap()) {
        QPushButton* button1 = new QPushButton("查看", ui->tableWidget);
        QPushButton* button2 = new QPushButton("项目完成", ui->tableWidget);
        QPushButton* button3 = new QPushButton("取消", ui->tableWidget);
        QPushButton* button4 = new QPushButton("查看", ui->tableWidget);
        QPushButton* button5 = new QPushButton("查看", ui->tableWidget);
        QPushButton* button6 = new QPushButton("查看", ui->tableWidget);
        QPushButton* button7 = new QPushButton("查看", ui->tableWidget);
        connect(button1, &QPushButton::clicked,
                this, &ManagerProjTable::onProjDetailBtnClicked);
        connect(button2, &QPushButton::clicked,
                this, &ManagerProjTable::onCommitBtnClicked);
        connect(button3, &QPushButton::clicked,
                this, &ManagerProjTable::onCancelBtnClicked);
        connect(button4, &QPushButton::clicked,
                this, &ManagerProjTable::onDetailBtnClicked);
        connect(button5, &QPushButton::clicked,
                this, &ManagerProjTable::onDetailBtnClicked);
        connect(button6, &QPushButton::clicked,
                this, &ManagerProjTable::onDetailBtnClicked);
        connect(button7, &QPushButton::clicked,
                this, &ManagerProjTable::onDetailBtnClicked);
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
        ui->tableWidget->setCellWidget(row, 6, button4);
        ui->tableWidget->setCellWidget(row, 7, button5);
        ui->tableWidget->setCellWidget(row, 8, button6);
        ui->tableWidget->setCellWidget(row, 9, button7);
        ui->tableWidget->setCellWidget(row, 10, button2);
        ui->tableWidget->setCellWidget(row, 11, button3);
        ui->tableWidget->setVerticalHeaderItem(row, new QTableWidgetItem(QString::number(row + 1)));
        ++row;
    }
}

void ManagerProjTable::onProjDetailBtnClicked()
{
    QPushButton* clickedBtn = qobject_cast<QPushButton*>(sender());
    if (clickedBtn) {
        int row = ui->tableWidget->indexAt(clickedBtn->pos()).row();
        QString projId = ui->tableWidget->item(row, 0)->text();
        ProjectInfo* projInfo = new ProjectInfo(projId);
        projInfo->show();
    }
}

void ManagerProjTable::onCommitBtnClicked()
{
    QPushButton *clickedBtn = qobject_cast<QPushButton *>(sender());
    if (clickedBtn) {
        auto reply = QMessageBox::information(
            this, "提示", QString("是否完成项目？"),
            QMessageBox::StandardButtons(QMessageBox::Yes | QMessageBox::No)
            );

        if (reply == QMessageBox::Yes) {
            int row = ui->tableWidget->indexAt(clickedBtn->pos()).row();
            QString projId = ui->tableWidget->item(row, 0)->text();
            Project proj = projModel.queryById(projId);
            proj.setProgress(QString("已完成"));
            proj.setUpdateTime(QDateTime::currentDateTime());
            ProjectModel().update(proj);

            on_refreshPushButton_clicked();
        }
    }
}

void ManagerProjTable::onCancelBtnClicked()
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

void ManagerProjTable::onDetailBtnClicked()
{
    QPushButton *clickedBtn = qobject_cast<QPushButton *>(sender());
    if (clickedBtn) {
        int row = ui->tableWidget->indexAt(clickedBtn->pos()).row();
        int column = ui->tableWidget->indexAt(clickedBtn->pos()).column();
        QString projId = ui->tableWidget->item(row, 0)->text();
        Project proj = projModel.queryById(projId);

        QString sPath = "";
        if (column == 6)
            sPath = proj.getImage0Path();
        else if (column == 7)
            sPath = proj.getImage1Path();
        else if (column == 8)
            sPath = proj.getImage2Path();
        else if (column == 9)
            sPath = proj.getImage3Path();
        else
            return;

        RecvFile *recv = new RecvFile(sPath);
        QByteArray data = recv->recvFile();

        if ((column == 6 || column == 7 ||
             column == 8 || column == 9) && data != "") {
            // 展示图片
            QPixmap image;
            image.loadFromData(data);

            ImageViewerDialog imageDialog;
            imageDialog.setImage(image);
            imageDialog.exec();
        } else {
            QMessageBox::information(this, "提示", "文件未上传!");
        }
    }
}
