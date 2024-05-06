#ifndef PROJECTDIRECTORPROJTABLE_H
#define PROJECTDIRECTORPROJTABLE_H

#include "infotable.h"
#include "projectmodel.h"

class ProjectDirectorProjTable : public InfoTable
{
public:
    ProjectDirectorProjTable(QWidget *parent = nullptr);

private:
    QVector<QString> setColName() override;
    void showData() override;
    void loadData() override;

private slots:
    void onAllocationBtnClicked();
    void onCancelBtnClicked();
    void onProjDetailBtnClicked();

private:
    QMap<QString, Project> projMap;
    ProjectModel projModel;
};

#endif // PROJECTDIRECTORPROJTABLE_H
