#ifndef DESIGNDIRECTORCLIENT_H
#define DESIGNDIRECTORCLIENT_H

#include "client.h"

class DesignDirectorClient : public Client
{
public:
    DesignDirectorClient(QWidget *parent = nullptr);
    QString getClientTitle() override;
    QString getUserTitle() override;
    void addTreeItems(QTreeWidgetItem *root) override;
    void addWidgets() override;
};

#endif // DESIGNDIRECTORCLIENT_H
