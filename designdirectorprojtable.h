#ifndef DESIGNDIRECTORPROJTABLE_H
#define DESIGNDIRECTORPROJTABLE_H

#include "infotable.h"
#include "projectmodel.h"

#include <QMap>

class DesignDirectorProjTable : public InfoTable
{
public:
    DesignDirectorProjTable(QWidget *parent = nullptr);

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

#endif // DESIGNDIRECTORPROJTABLE_H
