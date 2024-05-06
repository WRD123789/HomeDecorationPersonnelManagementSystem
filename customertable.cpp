#include "customertable.h"
#include "ui_infotable.h"
#include "projectmodel.h"
#include "projectinfo.h"
#include "addcustomer.h"
#include "financemodel.h"
#include "modifycustomer.h"

#include <QMessageBox>

CustomerTable::CustomerTable(QWidget *parent)
    : InfoTable(parent)
{
    init();
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
}

QVector<QString> CustomerTable::setColName()
{
    QVector<QString> nameVec;
    nameVec.push_back("编号");
    nameVec.push_back("姓名");
    nameVec.push_back("年龄");
    nameVec.push_back("性别");
    nameVec.push_back("手机号");
    nameVec.push_back("项目");
    nameVec.push_back("查看");
    nameVec.push_back("开始时间");
    nameVec.push_back("更新时间");
    nameVec.push_back("修改");
    nameVec.push_back("提交");
    nameVec.push_back("删除");
    return nameVec;
}

void CustomerTable::loadData()
{
    cusMap.clear();
    auto cusVec = cusModel.queryAllByCurId();
    for (auto& cus : cusVec) {
        cusMap.insert(cus.getId(), cus);
    }
}

void CustomerTable::showData()
{
    int row = 0;
    ui->tableWidget->setRowCount(cusMap.size());

    for (auto& [cusId, cus] : cusMap.toStdMap()) {
        Project proj = ProjectModel().queryById(cus.getProjId());

        QPushButton* button2 = nullptr;

        if (proj.getProgress() == "业务员沟通") {
            button2 = new QPushButton("提交", ui->tableWidget);
            connect(button2, &QPushButton::clicked, this, &CustomerTable::onCommitBtnClicked);
        } else {
            button2 = new QPushButton("已提交", ui->tableWidget);
            button2->setEnabled(false);
        }

        QPushButton* button1 = new QPushButton("查看", ui->tableWidget);
        QPushButton* button3 = new QPushButton("删除", ui->tableWidget);
        QPushButton* button4 = new QPushButton("修改", ui->tableWidget);
        connect(button1, &QPushButton::clicked, this, &CustomerTable::onProjInfoBtnClicked);
        connect(button3, &QPushButton::clicked, this, &CustomerTable::onDelCusBtnClicked);
        connect(button4, &QPushButton::clicked, this, &CustomerTable::onModifyCusBtnClicked);
        QTableWidgetItem* item1 = new QTableWidgetItem(cusId);
        QTableWidgetItem* item2 = new QTableWidgetItem(cus.getName());
        QTableWidgetItem* item3 = new QTableWidgetItem(QString::number(cus.getAge()));
        QTableWidgetItem* item4 = new QTableWidgetItem(cus.getGender());
        QTableWidgetItem* item5 = new QTableWidgetItem(cus.getPhone());
        QTableWidgetItem* item6 = new QTableWidgetItem(proj.getName());
        QTableWidgetItem* item7 = new QTableWidgetItem(proj.getStartTime()
                                                           .toString("yyyy-MM-dd HH:mm"));
        QTableWidgetItem* item8 = new QTableWidgetItem(proj.getUpdateTime()
                                                           .toString("yyyy-MM-dd HH:mm"));
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
        ui->tableWidget->setItem(row, 2, item3);
        ui->tableWidget->setItem(row, 3, item4);
        ui->tableWidget->setItem(row, 4, item5);
        ui->tableWidget->setItem(row, 5, item6);
        ui->tableWidget->setItem(row, 7, item7);
        ui->tableWidget->setItem(row, 8, item8);
        ui->tableWidget->setCellWidget(row, 6, button1);
        ui->tableWidget->setCellWidget(row, 9, button4);
        ui->tableWidget->setCellWidget(row, 10, button2);
        ui->tableWidget->setCellWidget(row, 11, button3);
        ui->tableWidget->setVerticalHeaderItem(row, new QTableWidgetItem(QString::number(row + 1)));
        ++row;
    }
}

void CustomerTable::onProjInfoBtnClicked()
{
    QPushButton* clickedBtn = qobject_cast<QPushButton*>(sender());
    if (clickedBtn) {
        int row = ui->tableWidget->indexAt(clickedBtn->pos()).row();
        QString cusId = ui->tableWidget->item(row, 0)->text();
        QString projId = cusModel.queryById(cusId).getProjId();
        ProjectInfo* projInfo = new ProjectInfo(projId);
        projInfo->show();
    }
}

void CustomerTable::onCommitBtnClicked()
{
    QPushButton *clickedBtn = qobject_cast<QPushButton *>(sender());
    if (clickedBtn) {
        auto reply = QMessageBox::information(
            this, "提示", "是否提交该项目？",
            QMessageBox::StandardButtons(QMessageBox::Yes | QMessageBox::No)
            );

        if (reply == QMessageBox::Yes) {
            int row = ui->tableWidget->indexAt(clickedBtn->pos()).row();
            QString cusId = ui->tableWidget->item(row, 0)->text();
            Customer &cus = cusMap[cusId];
            Project proj = ProjectModel().queryById(cus.getProjId());
            proj.setProgress(QString("设计总监分配"));
            proj.setUpdateTime(QDateTime::currentDateTime());
            ProjectModel().update(proj);
            on_refreshPushButton_clicked();
        }
    }
}

void CustomerTable::onDelCusBtnClicked()
{
    QPushButton *clickedBtn = qobject_cast<QPushButton *>(sender());
    if (clickedBtn) {
        auto reply = QMessageBox::information(
            this, "提示", "是否删除该客户？",
            QMessageBox::StandardButtons(QMessageBox::Yes | QMessageBox::No)
            );

        if (reply == QMessageBox::Yes) {
            int row = ui->tableWidget->indexAt(clickedBtn->pos()).row();
            QString cusId = ui->tableWidget->item(row, 0)->text();
            Customer &cus = cusMap[cusId];
            Project proj = ProjectModel().queryById(cus.getProjId());
            Finance fin = FinanceModel().queryByProjId(proj.getId());
            FinanceModel().remove(fin);
            cusModel.remove(cus);
            ProjectModel().remove(proj);

            on_refreshPushButton_clicked();
        }
    }
}

void CustomerTable::addBtn()
{
    QPushButton *btn = new QPushButton("新增", this);
    QFont font("宋体", 12);
    font.setWeight(QFont::Bold);
    btn->setFont(font);
    btn->setFocusPolicy(Qt::StrongFocus);
    ui->horizontalLayout->addWidget(btn);
    connect(btn, &QPushButton::clicked,
            this, &CustomerTable::onAddCusBtnClicked);
}

void CustomerTable::onAddCusBtnClicked()
{
    AddCustomer addCustomer(this);
    if (addCustomer.exec())
        on_refreshPushButton_clicked();
}

void CustomerTable::onModifyCusBtnClicked()
{
    QPushButton *clickedBtn = qobject_cast<QPushButton *>(sender());
    if (clickedBtn)
    {
        int row = ui->tableWidget->indexAt(clickedBtn->pos()).row();
        QString cusId = ui->tableWidget->item(row, 0)->text();
        ModifyCustomer modifyCustomer(cusId);
        modifyCustomer.exec();
    }
}

void CustomerTable::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    static int showWidth = TABLE_WIDGET_COLUMN_WIDTH * ui->tableWidget->columnCount() + TABLE_WIDGET_VERTICAL_HEADER_WIDTH;
    if (size().width() < showWidth) {
        ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
        for (int i = 0; i < ui->tableWidget->columnCount(); ++i) {
            ui->tableWidget->setColumnWidth(i ,TABLE_WIDGET_COLUMN_WIDTH);
        }
    } else {
        ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    }
}
