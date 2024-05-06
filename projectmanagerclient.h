#ifndef PROJECTMANAGERCLIENT_H
#define PROJECTMANAGERCLIENT_H

#include "client.h"

class ProjectManagerClient : public Client
{
public:
    ProjectManagerClient(QWidget *parent = nullptr);
    QString getClientTitle() override;
    QString getUserTitle() override;
    void addTreeItems(QTreeWidgetItem *root) override;
    void addWidgets() override;
};

#endif // PROJECTMANAGERCLIENT_H
