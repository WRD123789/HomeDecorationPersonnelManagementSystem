#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "recvdata.h"

#include <QThread>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QThread>
#include <QTcpSocket>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    qDebug() << "主线程: " << QThread::currentThreadId();

    m_s = new MyTcpServer(this);

    connect(m_s, &MyTcpServer::newDescriptor, this, [=](qintptr sock){
        RecvData *subThread = new RecvData(sock);

        subThread->start();

        connect(subThread, &RecvData::over, this, [=]() {
            subThread->quit();
            subThread->wait();
            subThread->deleteLater();
        });
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_setListen_clicked()
{
    unsigned short port = ui->port->text().toUShort();
    m_s->listen(QHostAddress::Any, port);
}
