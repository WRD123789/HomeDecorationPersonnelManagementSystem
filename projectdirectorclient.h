#ifndef PROJECTDIRECTORCLIENT_H
#define PROJECTDIRECTORCLIENT_H

#include "client.h"

class ProjectDirectorClient : public Client
{
public:
public:
    ProjectDirectorClient(QWidget *parent = nullptr);
    QString getClientTitle() override;
    QString getUserTitle() override;
    void addTreeItems(QTreeWidgetItem *root) override;
    void addWidgets() override;
};

#endif // PROJECTDIRECTORCLIENT_H
