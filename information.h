#ifndef INFORMATION_H
#define INFORMATION_H

#include <QWidget>

namespace Ui {
class Information;
}

/*
 * 信息基类
 * 客户端主页显示员工信息
 * 或在查看员工详细信息时展示
 */
class Information : public QWidget
{
    Q_OBJECT
public:
    // 设置 ui、关闭窗口时自动释放资源
    explicit Information(QWidget *parent = nullptr);
    virtual ~Information();

    Information* init();

    // 隐藏所有按钮, 作为客户端自己的个人信息时不使用
    Information* hideAllBtn();

    // 隐藏修改密码按钮
    Information* hideModifyPwdBtn();

protected:
    // 开启或关闭修改模式, 即输入栏开启或禁用
    virtual void modifyMode(bool mode);

    // 按下提交后获取输入栏信息并修改数据库
    virtual void commit() = 0;

    // 按下修改密码后弹出修改窗口
    virtual void modifyPwd() = 0;

    // 将查询的信息加载到输入框中
    virtual void loadInfo() = 0;

    Ui::Information *ui;

private slots:
    // 修改信息按钮槽函数
    void on_modifyPushButton_clicked();

    // 提交按钮槽函数
    void on_commitPushButton_clicked();

    // 取消按钮槽函数
    void on_cancelPushButton_clicked();

    // 修改密码按钮槽函数
    void on_modifyPwdPushButton_clicked();
};


#endif // INFORMATION_H
