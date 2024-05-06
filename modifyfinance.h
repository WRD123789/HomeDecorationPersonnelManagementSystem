#ifndef MODIFYFINANCE_H
#define MODIFYFINANCE_H

#include "finance.h"

#include <QDialog>

namespace Ui {
class ModifyFinance;
}
class ModifyFinance : public QDialog
{
    Q_OBJECT
public:
    explicit ModifyFinance(QDialog *parent = nullptr);
    explicit ModifyFinance(Finance &fin, QDialog *parent = nullptr);
    ~ModifyFinance();

private slots:
    void on_commitPushButton_clicked();
    void on_cancelPushButton_clicked();

private:
    Ui::ModifyFinance *ui;
    Finance fin;
};

#endif // MODIFYFINANCE_H
