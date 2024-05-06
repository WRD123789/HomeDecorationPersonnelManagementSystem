#ifndef DESIGNERCLIENT_H
#define DESIGNERCLIENT_H

#include "client.h"

class DesignerClient : public Client
{
public:
    DesignerClient(QWidget *parent = nullptr);
    QString getClientTitle() override;
    QString getUserTitle() override;
    void addTreeItems(QTreeWidgetItem *root) override;
    void addWidgets() override;
};

#endif // DESIGNERCLIENT_H
