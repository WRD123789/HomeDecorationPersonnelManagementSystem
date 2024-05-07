#ifndef CONNECTDATABASE_H
#define CONNECTDATABASE_H

#include <QDialog>

namespace Ui {
class ConnectDataBase;
}

class ConnectDataBase : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectDataBase(QDialog *parent = nullptr);
    ~ConnectDataBase();

private slots:
    void on_connectPushButton_clicked();
    void on_cancelPushButton_clicked();

private:
    Ui::ConnectDataBase *ui;
};


#endif // CONNECTDATABASE_H
