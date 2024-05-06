#ifndef CLIENT_H
#define CLIENT_H

#include <QWidget>
#include <QTreeWidgetItem>

namespace Ui {
class Client;
}

// 客户端抽象基类, 登录成功后显示的客户端
class Client : public QWidget
{
    Q_OBJECT
public:
    // 设置 ui、关闭窗口自动释放资源、居中显示等
    explicit Client(QWidget *parent = nullptr);
    virtual ~Client();

    // 获取客户端大标题
    virtual QString getClientTitle() = 0;

    // 获取客户端用户名和称呼
    virtual QString getUserTitle() = 0;

protected:
    // 初始化函数, 初始化客户端的菜单、大标题、用户称呼等
    void init();

    // 菜单栏添加条目
    virtual void addTreeItems(QTreeWidgetItem* root) = 0;

    // 在 `stackedWidget` 中添加窗口, 即按下菜单选项跳转到的窗口
    virtual void addWidgets() = 0;

    // 最大化时重新设置背景
    void resizeEvent(QResizeEvent* event) override;

    Ui::Client *ui;

private slots:
    // 按下退出按钮后直接关闭程序
    void on_exitPushButton_clicked();

private:
    QPixmap bgImage;
};

#endif // CLIENT_H
