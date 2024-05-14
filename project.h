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

    QString getImage0Path() const
    {
        return image0Path;
    }

    void setImage0Path(QString path)
    {
        this->image0Path = path;
    }

    QString getImage1Path() const
    {
        return image1Path;
    }

    void setImage1Path(QString path)
    {
        this->image1Path = path;
    }

    QString getImage2Path() const
    {
        return image2Path;
    }

    void setImage2Path(QString path)
    {
        this->image2Path = path;
    }

    QString getImage3Path() const
    {
        return image3Path;
    }

    void setImage3Path(QString path)
    {
        this->image3Path = path;
    }

    QString getTablePath() const
    {
        return tablePath;
    }

    void setTablePath(QString path)
    {
        this->tablePath = path;
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
    QString image0Path;
    QString image1Path;
    QString image2Path;
    QString image3Path;
    QString tablePath;
};

#endif // PROJECT_H
