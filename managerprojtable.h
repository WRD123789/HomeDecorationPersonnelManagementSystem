#ifndef MANAGERPROJTABLE_H
#define MANAGERPROJTABLE_H

#include "infotable.h"
#include "projectmodel.h"

class ManagerProjTable : public InfoTable
{
public:
    ManagerProjTable(QWidget *parent = nullptr);

private:
    QVector<QString> setColName() override;
    void showData() override;
    void loadData() override;

private slots:
    void onCommitBtnClicked();
    void onCancelBtnClicked();
    void onProjDetailBtnClicked();

private:
    QMap<QString, Project> projMap;
    ProjectModel projModel;
};

#endif // MANAGERPROJTABLE_H
