#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "client.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // 登录按钮槽函数
    void on_loginBtn_clicked();

    // 退出按钮槽函数
    void on_exitBtn_clicked();

signals:
    // 登录成功信号
    void succ(Client*);
    // 登录失败信号
    void fail();

private:
    Ui::MainWindow *ui;
    Client* client;
};
#endif // MAINWINDOW_H
