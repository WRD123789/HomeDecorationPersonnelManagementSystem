#ifndef SALESMANCLIENT_H
#define SALESMANCLIENT_H

#include "client.h"

// 业务员端
class SalesmanClient : public Client
{
public:
    SalesmanClient(QWidget *parent = nullptr);
    QString getClientTitle() override;
    QString getUserTitle() override;
    void addTreeItems(QTreeWidgetItem *root) override;
    void addWidgets() override;
};

#endif // SALESMANCLIENT_H
