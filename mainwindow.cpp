#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "accountinstance.h"
#include "accountmodel.h"
#include "employeemodel.h"
#include "salesmanclient.h"
#include "designdirectorclient.h"
#include "designerclient.h"
#include "financeclient.h"
#include "projectdirectorclient.h"
#include "projectmanagerclient.h"
#include "adminclient.h"

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowIcon(QIcon(":/icon.png"));
    // 窗口固定大小为 1280 * 720
    setFixedSize(1280, 720);
    ui->centralwidget->setFixedSize(width(), height());
    // 账号输入栏设置焦点
    ui->accountLineEdit->setFocus();

    // 设置背景图片
    QPixmap pixmap(":/background.png");
    QPalette palette;
    pixmap = pixmap.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    palette.setBrush(QPalette::Window, pixmap);
    // 背景自动填充
    setAutoFillBackground(true);
    setPalette(palette);

    // 居中显示
    int x = (this->width()  - ui->frame->width())  >> 1;
    int y = (this->height() - ui->frame->height()) >> 1;
    ui->frame->setGeometry(x, y + 50, ui->frame->width(), ui->frame->height());

    // 在输入密码完密码按下回车后直接登录
    connect(ui->pwdLineEdit, &QLineEdit::returnPressed,
            this, &MainWindow::on_loginBtn_clicked);
    // 登录验证成功后发出 `succ` 信号
    connect(this, &MainWindow::succ, this, [this](Client* client){
        // 显示客户端
        client->show();
        // 登录窗口隐藏
        this->hide();
        this->client = client;
        // 客户端关闭后执行
        connect(client, &Client::destroyed, this, [this](){
            // 客户端关闭后显示登录界面
            this->show();
        });
    });

    // 登录失败后发射fail信号
    connect(this, &MainWindow::fail, this, [this](){
        // 提示密码错误
        QMessageBox::warning(this, "提示", "密码错误！");
        // 密码输入栏清空
        ui->pwdLineEdit->clear();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loginBtn_clicked()
{
    // 根据账号和密码栏获取输入的字符串
    QString num = ui->accountLineEdit->text();
    QString pwd = ui->pwdLineEdit->text();

    // 输入为空的提示
    if (num.isEmpty() || pwd.isEmpty())
    {
        QMessageBox::warning(this, "提示", "账号或密码不能为空!");
        return;
    }

    // 连接数据库
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setPort(3306);
    db.setDatabaseName("home_decoration");
    db.setUserName("root");
    db.setPassword("12345678");
    if(!db.open()){
        QMessageBox::critical(this, "错误", "数据库连接失败!");
        return;
    }

    AccountModel accModel;
    Account acc = accModel.queryByNumber(num);

    if (pwd == acc.getPassword()) {
        // 获取到 `AccountInstance` 单例，设置 `id` 和 `name`
        auto& account = AccountInstance::instance();
        account.setId(acc.getId());
        EmployeeModel empModel;
        Employee emp = empModel.queryById(account.getId());
        account.setName(emp.getName());

        // 发射登录成功信号, 根据身份创建客户端
        QString identity = acc.getIdentity();
        if (identity == "业务员")
            emit succ(new SalesmanClient());
        else if (identity == "设计师总监")
            emit succ(new DesignDirectorClient());
        else if (identity == "设计师")
            emit succ(new DesignerClient());
        else if (identity == "项目总经理")
            emit succ(new ProjectDirectorClient());
        else if (identity == "项目经理")
            emit succ(new ProjectManagerClient());
        else if (identity == "财务")
            emit succ(new FinanceClient());
        else if (identity == "管理员")
            emit succ(new AdminClient());
    } else {
        emit fail();
    }
}

void MainWindow::on_exitBtn_clicked()
{
    // 按下退出按钮直接关闭程序
    exit(0);
}
