#ifndef PROJECTINFO_H
#define PROJECTINFO_H

#include <QWidget>

namespace Ui {
class ProjectInfo;
}

class ProjectInfo : public QWidget
{
    Q_OBJECT
public:
    explicit ProjectInfo(QWidget *parent = nullptr);

    // 根据项目 `id` 显示对应的项目信息
    explicit ProjectInfo(QString projId, QWidget *parent = nullptr);

    ~ProjectInfo();

private:
    Ui::ProjectInfo *ui;
};

#endif // PROJECTINFO_H
