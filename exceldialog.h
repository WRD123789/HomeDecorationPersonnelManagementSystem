#ifndef EXCELDIALOG_H
#define EXCELDIALOG_H

#include <QtWidgets>
#include <QAxObject>
#include <QBuffer>
#include <QTemporaryFile>

class ExcelDialog : public QDialog {
    Q_OBJECT

public:
    ExcelDialog(const QByteArray &excelData, QWidget *parent = nullptr) : QDialog(parent) {
        setWindowTitle("Excel Viewer");
        resize(600, 400);

        QVBoxLayout *layout = new QVBoxLayout(this);
        tableView = new QTableView(this);
        layout->addWidget(tableView);

        // 加载 Excel 数据
        loadExcelData(excelData);
    }

private:
    QTableView *tableView;

    void loadExcelData(const QByteArray &excelData) {
        // 将 QByteArray 数据写入临时文件
        QTemporaryFile tempFile;
        if (!tempFile.open()) {
            QMessageBox::critical(this, "Error", "Failed to create temporary file.");
            return;
        }
        tempFile.write(excelData);
        tempFile.close();

        QAxObject excel("Excel.Application", this);
        excel.setProperty("Visible", false); // 不显示 Excel 窗口

        QAxObject *workbooks = excel.querySubObject("Workbooks");
        QAxObject *workbook = workbooks->querySubObject("Open(const QString&)", tempFile.fileName());

        if (!workbook) {
            QMessageBox::critical(this, "Error", "Failed to open Excel data.");
            return;
        }

        QAxObject *sheets = workbook->querySubObject("Worksheets");
        int sheetCount = sheets->property("Count").toInt();

        // 假设只有一个表格，加载第一个表格的数据
        if (sheetCount > 0) {
            QAxObject *sheet = sheets->querySubObject("Item(int)", 1); // 第一个表格
            QAxObject *usedRange = sheet->querySubObject("UsedRange");
            QAxObject *rows = usedRange->querySubObject("Rows");
            QAxObject *columns = usedRange->querySubObject("Columns");
            int rowCount = rows->property("Count").toInt();
            int columnCount = columns->property("Count").toInt();

            // 读取 Excel 数据到 QStandardItemModel
            QStandardItemModel *model = new QStandardItemModel(rowCount, columnCount, this);
            for (int row = 1; row <= rowCount; ++row) {
                for (int col = 1; col <= columnCount; ++col) {
                    QAxObject *cell = sheet->querySubObject("Cells(int, int)", row, col);
                    QString value = cell->dynamicCall("Value()").toString();
                    model->setItem(row - 1, col - 1, new QStandardItem(value));
                    delete cell;
                }
            }

            tableView->setModel(model);
            tableView->resizeColumnsToContents();
            tableView->resizeRowsToContents();
        }

        // 关闭 Excel
        excel.dynamicCall("Quit()");
    }
};

#endif // EXCELDIALOG_H
