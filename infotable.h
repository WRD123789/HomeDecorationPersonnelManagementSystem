#ifndef INFOTABLE_H
#define INFOTABLE_H

#include <QWidget>

// 单列的宽度
constexpr int TABLE_WIDGET_COLUMN_WIDTH = 100;
constexpr int TABLE_WIDGET_VERTICAL_HEADER_WIDTH = 60;

namespace Ui {
class InfoTable;
}

// 信息表抽象基类
class InfoTable : public QWidget
{
    Q_OBJECT
public:
    // 用于连接一些信号和槽函数
    explicit InfoTable(QWidget *parent = nullptr);
    virtual ~InfoTable();

    InfoTable* init();

    // 根据成员变量 `sortCol` 排序某列
    virtual void sortTable();

private:
    // 添加按钮
    virtual void addBtn();

    // 设置表中每一列的名字
    virtual QVector<QString> setColName() = 0;

    // 查询数据库并将数据存储到内存中
    virtual void loadData() = 0;

    // 将存储的数据显示到表中
    virtual void showData() = 0;

protected slots:
    // 按下搜索按钮的槽函数
    virtual void on_searchPushButton_clicked();

    // 按下刷新按钮的槽函数
    virtual void on_refreshPushButton_clicked();

    // 按下取消按钮的槽函数
    virtual void on_cancelPushButton_clicked();

protected:
    Ui::InfoTable *ui;
    Qt::SortOrder order; // 排序的规则, 用于点击同一个按钮升降序切换
    int sortCol;         // 排序的列, 在刷新后用于获取上一次排序的列
};

#endif // INFOTABLE_H
