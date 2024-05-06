#ifndef PROJECT_H
#define PROJECT_H

#include <QString>
#include <QDateTime>

class Project
{
public:
    Project() = default;

    QString getId() const
    {
        return id;
    }

    void setId(QString id)
    {
        this->id = id;
    }

    QString getName() const
    {
        return name;
    }

    void setName(QString name)
    {
        this->name = name;
    }

    QString getContent() const
    {
        return content;
    }

    void setContent(QString content)
    {
        this->content = content;
    }

    QDateTime getStartTime() const
    {
        return startTime;
    }

    void setStartTime(QDateTime startTime)
    {
        this->startTime = startTime;
    }

    QString getProgress() const
    {
        return progress;
    }

    void setProgress(QString progress)
    {
        this->progress = progress;
    }

    QDateTime getUpdateTime() const
    {
        return updateTime;
    }

    void setUpdateTime(QDateTime updateTime)
    {
        this->updateTime = updateTime;
    }

    QString getSalesmanId() const
    {
        return salesmanId;
    }

    void setSalesmanId(QString id)
    {
        this->salesmanId = id;
    }

    QString getDesignerId() const
    {
        return designerId;
    }

    void setDesignerId(QString id)
    {
        this->designerId = id;
    }

    QString getProjManagerId() const
    {
        return projManagerId;
    }

    void setProjManagerId(QString id)
    {
        this->projManagerId = id;
    }

private:
    QString id;
    QString name;
    QString content;
    QDateTime startTime;
    QString progress;
    QDateTime updateTime;
    QString salesmanId;
    QString designerId;
    QString projManagerId;
};

#endif // PROJECT_H
