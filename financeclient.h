#ifndef FINANCECLIENT_H
#define FINANCECLIENT_H

#include "client.h"

class FinanceClient : public Client
{
public:
    FinanceClient(QWidget *parent = nullptr);
    QString getClientTitle() override;
    QString getUserTitle() override;
    void addTreeItems(QTreeWidgetItem *root) override;
    void addWidgets() override;
};

#endif // FINANCECLIENT_H
