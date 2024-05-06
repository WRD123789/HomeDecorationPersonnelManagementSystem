#ifndef MODIFYPASSWORD_H
#define MODIFYPASSWORD_H

#include "account.h"

#include <QDialog>

namespace Ui {
class ModifyPassword;
}

// 修改密码对话框
class ModifyPassword : public QDialog
{
    Q_OBJECT

public:
    explicit ModifyPassword(QDialog *parent = nullptr);
    explicit ModifyPassword(Account &acc, QDialog *parent = nullptr);
    ~ModifyPassword();

private slots:
    void on_commitPushButton_clicked();
    void on_cancelPushButton_clicked();

private:
    void modifyPwd(QString newPwd);

    Ui::ModifyPassword *ui;
    QString oldPwd;
    Account acc;
};

#endif // MODIFYPASSWORD_H
