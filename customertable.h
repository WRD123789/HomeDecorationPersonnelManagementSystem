#ifndef CUSTOMERTABLE_H
#define CUSTOMERTABLE_H

#include "infotable.h"
#include "customermodel.h"

#include <QMap>

class CustomerTable : public InfoTable
{
public:
    CustomerTable(QWidget *parent = nullptr);

private:
    QVector<QString> setColName() override;
    void showData() override;
    void addBtn() override;
    void loadData() override;

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void onProjInfoBtnClicked();
    void onCommitBtnClicked();
    void onDelCusBtnClicked();
    void onAddCusBtnClicked();
    void onModifyCusBtnClicked();

private:
    QMap<QString, Customer> cusMap;
    CustomerModel cusModel;
};

#endif // CUSTOMERTABLE_H
