#ifndef FINANCEPROJTABLE_H
#define FINANCEPROJTABLE_H

#include "infotable.h"
#include "financemodel.h"
#include "projectmodel.h"

class FinanceProjTable : public InfoTable
{
public:
    FinanceProjTable(QWidget *parent = nullptr);

private:
    QVector<QString> setColName() override;
    void showData() override;
    void loadData() override;

private slots:
    void onCommitBtnClicked();
    void onCancelBtnClicked();
    void onModifyBtnClicked();
    void onProjDetailBtnClicked();
    void onDetailBtnClicked();

private:
    QMap<QString, Project> projMap;
    ProjectModel projModel;

    QMap<QString, Finance> finMap;
    FinanceModel finModel;
};

#endif // FINANCEPROJTABLE_H
