#ifndef ADMINPROJECTTABLE_H
#define ADMINPROJECTTABLE_H

#include "infotable.h"
#include "projectmodel.h"

class AdminProjectTable : public InfoTable
{
public:
    AdminProjectTable(QWidget *parent = nullptr);

private:
    QVector<QString> setColName() override;
    void showData() override;
    void loadData() override;

private slots:
    void onModifyBtnClicked();
    void onCancelBtnClicked();
    void onProjDetailBtnClicked();

private:
    QMap<QString, Project> projMap;
    ProjectModel projModel;
};

#endif // ADMINPROJECTTABLE_H
