#ifndef ADMINCLIENT_H
#define ADMINCLIENT_H

#include "client.h"

class AdminClient : public Client
{
public:
    AdminClient(QWidget *parent = nullptr);
    QString getClientTitle() override;
    QString getUserTitle() override;
    void addTreeItems(QTreeWidgetItem *root) override;
    void addWidgets() override;
};

#endif // ADMINCLIENT_H
