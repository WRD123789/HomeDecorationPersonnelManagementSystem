#ifndef ADMINCUSTOMERTABLE_H
#define ADMINCUSTOMERTABLE_H

#include "infotable.h"
#include "customermodel.h"

class AdminCustomerTable : public InfoTable
{
public:
    AdminCustomerTable(QWidget *parent = nullptr);

private:
    QVector<QString> setColName() override;
    void showData() override;
    void addBtn() override;
    void loadData() override;

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void onProjInfoBtnClicked();
    void onDelCusBtnClicked();
    void onAddCusBtnClicked();
    void onModifyCusBtnClicked();

private:
    QMap<QString, Customer> cusMap;
    CustomerModel cusModel;
};

#endif // ADMINCUSTOMERTABLE_H
