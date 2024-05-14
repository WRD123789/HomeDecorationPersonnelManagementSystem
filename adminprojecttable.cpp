#include "adminprojecttable.h"
#include "ui_infotable.h"
#include "employeemodel.h"
#include "projectinfo.h"
#include "exceldialog.h"
#include "imageviewerdialog.h"
#include "recvfile.h"

#include <QComboBox>
#include <QMessageBox>

AdminProjectTable::AdminProjectTable(QWidget *parent)
    : InfoTable(parent)
{
    init();
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
}

QVector<QString> AdminProjectTable::setColName()
{
    QVector<QString> nameVec;
    nameVec.push_back("编号");
    nameVec.push_back("项目");
    nameVec.push_back("查看");
    nameVec.push_back("进度");
    nameVec.push_back("开始时间");
    nameVec.push_back("更新时间");
    nameVec.push_back("业务员");
    nameVec.push_back("设计师");
    nameVec.push_back("项目经理");
    nameVec.push_back("量房设计图");
    nameVec.push_back("平面设计图");
    nameVec.push_back("深入图");
    nameVec.push_back("效果图");
    nameVec.push_back("预算表");
    nameVec.push_back("修改");
    nameVec.push_back("取消");
    return nameVec;
}

void AdminProjectTable::loadData()
{
    projMap.clear();
    auto projVec = projModel.queryAll();
    for (auto& proj : projVec) {
        projMap.insert(proj.getId(), proj);
    }
}

void AdminProjectTable::showData()
{
    int row = 0;
    ui->tableWidget->setRowCount(projMap.size());

    QVector<Employee> salesmans = EmployeeModel().queryAllByIdentity(QString("业务员"));
    QVector<Employee> designers = EmployeeModel().queryAllByIdentity(QString("设计师"));
    QVector<Employee> managers = EmployeeModel().queryAllByIdentity(QString("项目经理"));

    for (auto& [projId, proj] : projMap.toStdMap()) {
        QPushButton* button1 = new QPushButton("查看", ui->tableWidget);
        QPushButton* button2 = new QPushButton("修改", ui->tableWidget);
        QPushButton* button3 = new QPushButton("取消", ui->tableWidget);
        QPushButton* button4 = new QPushButton("查看", ui->tableWidget);
        QPushButton* button5 = new QPushButton("查看", ui->tableWidget);
        QPushButton* button6 = new QPushButton("查看", ui->tableWidget);
        QPushButton* button7 = new QPushButton("查看", ui->tableWidget);
        QPushButton* button8 = new QPushButton("查看", ui->tableWidget);
        connect(button1, &QPushButton::clicked,
                this, &AdminProjectTable::onProjDetailBtnClicked);
        connect(button2, &QPushButton::clicked,
                this, &AdminProjectTable::onModifyBtnClicked);
        connect(button3, &QPushButton::clicked,
                this, &AdminProjectTable::onCancelBtnClicked);
        connect(button4, &QPushButton::clicked,
                this, &AdminProjectTable::onDetailBtnClicked);
        connect(button5, &QPushButton::clicked,
                this, &AdminProjectTable::onDetailBtnClicked);
        connect(button6, &QPushButton::clicked,
                this, &AdminProjectTable::onDetailBtnClicked);
        connect(button7, &QPushButton::clicked,
                this, &AdminProjectTable::onDetailBtnClicked);
        connect(button8, &QPushButton::clicked,
                this, &AdminProjectTable::onDetailBtnClicked);
        QTableWidgetItem* item1 = new QTableWidgetItem(projId);
        QTableWidgetItem* item2 = new QTableWidgetItem(proj.getName());
        QTableWidgetItem* item3 = new QTableWidgetItem(proj.getProgress());
        QTableWidgetItem* item4 = new QTableWidgetItem(proj.getStartTime()
                                                           .toString("yyyy-MM-dd HH:mm"));
        QTableWidgetItem* item5 = new QTableWidgetItem(proj.getUpdateTime()
                                                           .toString("yyyy-MM-dd HH:mm"));

        QComboBox* box1 = new QComboBox(ui->tableWidget);
        box1->addItem("");
        for (int i = 0; i < salesmans.size(); i += 1) {
            box1->addItem(salesmans[i].getName());
        }
        box1->setCurrentText(proj.getSalesmanId() == "" ?
                                 "" :
                                 EmployeeModel().queryById(proj.getSalesmanId()).getName());

        QComboBox* box2 = new QComboBox(ui->tableWidget);
        box2->addItem("");
        for (int i = 0; i < designers.size(); i += 1) {
            box2->addItem(designers[i].getName());
        }
        box2->setCurrentText(proj.getDesignerId() == "" ?
                                 "" :
                                 EmployeeModel().queryById(proj.getDesignerId()).getName());

        QComboBox* box3 = new QComboBox(ui->tableWidget);
        box3->addItem("");
        for (int i = 0; i < managers.size(); i += 1) {
            box3->addItem(managers[i].getName());
        }
        box3->setCurrentText(proj.getProjManagerId() == "" ?
                                 "" :
                                 EmployeeModel().queryById(proj.getProjManagerId()).getName());

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
        ui->tableWidget->setCellWidget(row, 9, button4);
        ui->tableWidget->setCellWidget(row, 10, button5);
        ui->tableWidget->setCellWidget(row, 11, button6);
        ui->tableWidget->setCellWidget(row, 12, button7);
        ui->tableWidget->setCellWidget(row, 13, button8);
        ui->tableWidget->setCellWidget(row, 14, button2);
        ui->tableWidget->setCellWidget(row, 15, button3);
        ui->tableWidget->setCellWidget(row, 6, box1);
        ui->tableWidget->setCellWidget(row, 7, box2);
        ui->tableWidget->setCellWidget(row, 8, box3);
        ui->tableWidget->setVerticalHeaderItem(row, new QTableWidgetItem(QString::number(row + 1)));
        ++row;
    }
}

void AdminProjectTable::onProjDetailBtnClicked()
{
    QPushButton* clickedBtn = qobject_cast<QPushButton*>(sender());
    if (clickedBtn) {
        int row = ui->tableWidget->indexAt(clickedBtn->pos()).row();
        QString projId = ui->tableWidget->item(row, 0)->text();
        ProjectInfo* projInfo = new ProjectInfo(projId);
        projInfo->show();
    }
}

void AdminProjectTable::onModifyBtnClicked()
{
    QPushButton *clickedBtn = qobject_cast<QPushButton *>(sender());
    if (clickedBtn) {
        auto reply = QMessageBox::information(
            this, "提示", "是否修改项目？",
            QMessageBox::StandardButtons(QMessageBox::Yes | QMessageBox::No)
            );

        if (reply == QMessageBox::Yes) {
            int row = ui->tableWidget->indexAt(clickedBtn->pos()).row();
            QString projId = ui->tableWidget->item(row, 0)->text();

            QString salesmanName = qobject_cast<QComboBox*>(
                                       ui->tableWidget->cellWidget(row, 6))->currentText();
            QString salesmanId = EmployeeModel().queryByName(salesmanName).getId();
            QString designerName = qobject_cast<QComboBox*>(
                                       ui->tableWidget->cellWidget(row, 7))->currentText();
            QString designerId = EmployeeModel().queryByName(designerName).getId();
            QString managerName = qobject_cast<QComboBox*>(
                                       ui->tableWidget->cellWidget(row, 8))->currentText();
            QString managerId = EmployeeModel().queryByName(managerName).getId();

            Project proj = projModel.queryById(projId);
            proj.setSalesmanId(salesmanId);
            proj.setDesignerId(designerId);
            proj.setProjManagerId(managerId);
            ProjectModel().update(proj);

            on_refreshPushButton_clicked();
        }
    }
}

void AdminProjectTable::onCancelBtnClicked()
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

void AdminProjectTable::onDetailBtnClicked()
{
    QPushButton *clickedBtn = qobject_cast<QPushButton *>(sender());
    if (clickedBtn) {
        int row = ui->tableWidget->indexAt(clickedBtn->pos()).row();
        int column = ui->tableWidget->indexAt(clickedBtn->pos()).column();
        QString projId = ui->tableWidget->item(row, 0)->text();
        Project proj = projModel.queryById(projId);

        QString sPath = "";
        if (column == 9)
            sPath = proj.getImage0Path();
        else if (column == 10)
            sPath = proj.getImage1Path();
        else if (column == 11)
            sPath = proj.getImage2Path();
        else if (column == 12)
            sPath = proj.getImage3Path();
        else if (column == 13)
            sPath = proj.getTablePath();
        else
            return;

        RecvFile *recv = new RecvFile(sPath);
        QByteArray data = recv->recvFile();

        if (column == 13) {
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
