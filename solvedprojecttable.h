#ifndef SOLVEDPROJECTTABLE_H
#define SOLVEDPROJECTTABLE_H

#include "infotable.h"

#include "projectmodel.h"

class SolvedProjectTable : public InfoTable
{
public:
    SolvedProjectTable(QWidget *parent = nullptr);

private:
    QVector<QString> setColName() override;
    void showData() override;
    void loadData() override;

private slots:
    void onProjDetailBtnClicked();

private:
    QMap<QString, Project> projMap;
    ProjectModel projModel;
};

#endif // SOLVEDPROJECTTABLE_H
