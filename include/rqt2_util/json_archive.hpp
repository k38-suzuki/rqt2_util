#ifndef RQT2_UTIL__JSON_ARCHIVE_HPP_
#define RQT2_UTIL__JSON_ARCHIVE_HPP_

#include <QJsonObject>
#include <QVector>
#include "rqt2_util/visibility_control.h"

namespace rqt2_util
{

class JsonArchive
{
public:
    JsonArchive();

    virtual ~JsonArchive();

    bool open();
    bool save();

    virtual void read(const QJsonObject& json) = 0;
    virtual void write(QJsonObject& json) = 0;

    void set(QJsonObject& json, const QString& key, const int& value);
    void set(QJsonObject& json, const QString& key, const double& value);
    void set(QJsonObject& json, const QString& key, const bool& value);
    void set(QJsonObject& json, const QString& key, const QString& value);

    int get(const QJsonObject& json, const QString& key, const int& init) const;
    double get(const QJsonObject& json, const QString& key, const double& init) const;
    bool get(const QJsonObject& json, const QString& key, const bool& init) const;
    QString get(const QJsonObject& json, const QString& key, const char* init) const;

    void set(QJsonObject& json, const QString& key, QVector<int>& vector);
    void set(QJsonObject& json, const QString& key, QVector<double>& vector);
    void set(QJsonObject& json, const QString& key, QVector<bool>& vector);
    void set(QJsonObject& json, const QString& key, QVector<QString>& vector);

    bool get(const QJsonObject& json, const QString& key, QVector<int>& vector);
    bool get(const QJsonObject& json, const QString& key, QVector<double>& vector);
    bool get(const QJsonObject& json, const QString& key, QVector<bool>& vector);
    bool get(const QJsonObject& json, const QString& key, QVector<QString>& vector);

private:
    bool loadFile(const QString& fileName);
    bool saveFile(const QString& fileName);

    QString directory_;
};

}  // namespace rqt2_util

#endif  // RQT2_UTIL__JSON_ARCHIVE_HPP_
