#ifndef PROJECTLIST_H
#define PROJECTLIST_H

#include "infotable.h"
#include "projectmodel.h"

class ProjectList : public InfoTable
{
public:
    ProjectList(QString empId, QWidget *parent = nullptr);

private:
    QVector<QString> setColName() override;
    void showData() override;
    void loadData() override;

private slots:
    void onProjInfoBtnClicked();

private:
    QMap<QString, Project> projMap;
    ProjectModel projModel;
    QString id;
};

#endif // PROJECTLIST_H
