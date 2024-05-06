#include "infotable.h"
#include "ui_infotable.h"

InfoTable::InfoTable(QWidget *parent)
    : QWidget{parent}
    , ui(new Ui::InfoTable)
{
    ui->setupUi(this);

    this->setStyleSheet("background-color: rgba(255, 255, 255, 128);");

    // 搜索栏文本改变直接显示搜索内容
    connect(ui->searchLineEdit, &QLineEdit::textChanged,
            this, &InfoTable::on_searchPushButton_clicked);

    // 某列列头被点击
    connect(ui->tableWidget->horizontalHeader(), &QHeaderView::sectionClicked,
            ui->tableWidget, [&](int logicalIndex) {
        // 升降序交替
        static bool currentOrder = true;
        order = currentOrder ? Qt::DescendingOrder : Qt::AscendingOrder;
        currentOrder = !currentOrder;
        // 排序列为所点击的列
        sortCol = logicalIndex;
        sortTable();

        int showCount = 1;
        // 遍历所有行
        for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
            // 由于搜索后可能存在隐藏的记录, 因此需要重新设置行数值
            if (!ui->tableWidget->isRowHidden(row))
                ui->tableWidget->verticalHeaderItem(row)->setText(QString::number(showCount++));
        }
    });
}

InfoTable::~InfoTable()
{
    delete ui;
}

void InfoTable::addBtn() {}

InfoTable *InfoTable::init()
{
    addBtn();

    // 获取所有列名
    auto tableColNames = setColName();
    // 设置列数
    ui->tableWidget->setColumnCount(tableColNames.size());

    for (int i = 0; i < tableColNames.size(); ++i) {
        // 将列名加入到表中
        QTableWidgetItem* item = new QTableWidgetItem(tableColNames[i]);
        ui->tableWidget->setHorizontalHeaderItem(i, item);
    }
    // 将表设置为自适应窗口大小模式
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // 加载数据
    loadData();

    // 显示数据
    showData();

    return this;
}

// 模糊搜索表中的内容
void InfoTable::on_searchPushButton_clicked()
{
    // 获取搜索栏输入内容
    QString condition = ui->searchLineEdit->text();
    // 如果为空, 将全部内容显示
    if (condition.isEmpty()) {
        for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
            ui->tableWidget->setRowHidden(row, false);
            // 显示第 `row` 行
            ui->tableWidget->verticalHeaderItem(row)->setText(QString::number(row + 1));
        }
        return;
    }

    int count = 1;
    for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
        bool hide = true;
        for (int col = 0; col < ui->tableWidget->columnCount(); ++col) {
            auto item = ui->tableWidget->item(row, col);
            // 表中的内容包含搜索条件
            if (item && item->text().contains(condition)) {
                // 不隐藏这一行
                hide = false;
                // 重新设置行数值
                ui->tableWidget->verticalHeaderItem(row)->setText(QString::number(count++));
                break;
            }
        }
        // 设置隐藏
        ui->tableWidget->setRowHidden(row, hide);
    }
}

// 刷新显示的数据
void InfoTable::on_refreshPushButton_clicked()
{
    // 重新加载
    loadData();

    // 清空内容并设为 0 行
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);

    // 显示加载的数据
    showData();

    // 若搜索栏还有条件, 则显示搜索内容
    if (!ui->searchLineEdit->text().isEmpty())
        on_searchPushButton_clicked();
}

// 取消
void InfoTable::on_cancelPushButton_clicked()
{
    // 清空搜索栏
    if (ui->searchLineEdit->text().isEmpty())
        return;
    ui->searchLineEdit->clear();
}

void InfoTable::sortTable()
{
    // 以第 `sortCol` 列为基准, 根据 `order` 进行升降序
    ui->tableWidget->sortItems(sortCol, order);
}
