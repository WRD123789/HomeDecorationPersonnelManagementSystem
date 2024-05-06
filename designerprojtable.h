#ifndef DESIGNERPROJTABLE_H
#define DESIGNERPROJTABLE_H

#include "infotable.h"
#include "projectmodel.h"

class DesignerProjTable : public InfoTable
{
public:
    DesignerProjTable(QWidget *parent = nullptr);

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

#endif // DESIGNERPROJTABLE_H
