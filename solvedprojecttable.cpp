#include "solvedprojecttable.h"
#include "ui_infotable.h"
#include "projectinfo.h"
#include "recvfile.h"
#include "imageviewerdialog.h"
#include "exceldialog.h"

#include <QAxObject>
#include <QAxWidget>
#include <QBuffer>
#include <QMessageBox>

SolvedProjectTable::SolvedProjectTable(QWidget *parent)
    : InfoTable(parent)
{
    init();
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
}

QVector<QString> SolvedProjectTable::setColName()
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
    nameVec.push_back("预算表");
    return nameVec;
}

void SolvedProjectTable::loadData()
{
    projMap.clear();
    auto projVec = projModel.queryAllSolved();
    for (auto& proj : projVec) {
        projMap.insert(proj.getId(), proj);
    }
}

void SolvedProjectTable::showData()
{
    int row = 0;
    ui->tableWidget->setRowCount(projMap.size());

    for (auto& [projId, proj] : projMap.toStdMap()) {
        QPushButton* button1 = new QPushButton("查看", ui->tableWidget);
        QPushButton* button2 = new QPushButton("查看", ui->tableWidget);
        QPushButton* button3 = new QPushButton("查看", ui->tableWidget);
        QPushButton* button4 = new QPushButton("查看", ui->tableWidget);
        QPushButton* button5 = new QPushButton("查看", ui->tableWidget);
        QPushButton* button6 = new QPushButton("查看", ui->tableWidget);
        connect(button1, &QPushButton::clicked,
                this, &SolvedProjectTable::onProjDetailBtnClicked);
        connect(button2, &QPushButton::clicked,
                this, &SolvedProjectTable::onDetailBtnClicked);
        connect(button3, &QPushButton::clicked,
                this, &SolvedProjectTable::onDetailBtnClicked);
        connect(button4, &QPushButton::clicked,
                this, &SolvedProjectTable::onDetailBtnClicked);
        connect(button5, &QPushButton::clicked,
                this, &SolvedProjectTable::onDetailBtnClicked);
        connect(button6, &QPushButton::clicked,
                this, &SolvedProjectTable::onDetailBtnClicked);
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
        ui->tableWidget->setCellWidget(row, 8, button4);
        ui->tableWidget->setCellWidget(row, 9, button5);
        ui->tableWidget->setCellWidget(row, 10, button6);
        ui->tableWidget->setVerticalHeaderItem(row, new QTableWidgetItem(QString::number(row + 1)));
        ++row;
    }
}

void SolvedProjectTable::onProjDetailBtnClicked()
{
    QPushButton* clickedBtn = qobject_cast<QPushButton*>(sender());
    if (clickedBtn) {
        int row = ui->tableWidget->indexAt(clickedBtn->pos()).row();
        QString projId = ui->tableWidget->item(row, 0)->text();
        ProjectInfo* projInfo = new ProjectInfo(projId);
        projInfo->show();
    }
}

void SolvedProjectTable::onDetailBtnClicked()
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
        else if (column == 10)
            sPath = proj.getTablePath();
        else
            return;

        RecvFile *recv = new RecvFile(sPath);
        QByteArray data = recv->recvFile();

        if (column == 10) {
            if (data != "") {
                ExcelDialog dialog(data);
                dialog.exec();
            } else {
                QMessageBox::information(this, "提示", "文件未上传!");
            }
        } else {
            if (data != "") {
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
}
