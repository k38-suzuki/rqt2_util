#ifndef RQT2_UTIL__JSON_ARCHIVE_HPP_
#define RQT2_UTIL__JSON_ARCHIVE_HPP_

#include <QJsonObject>
#include <QVector>
#include "rqt2_util/visibility_control.h"

namespace rqt2_util
{

class JsonArchiveInterface
{
public:
    virtual void read(const QJsonObject& json) = 0;
    virtual void write(QJsonObject& json) = 0;
    virtual ~JsonArchiveInterface(){}

protected:
    JsonArchiveInterface(){}
};

class JsonArchive : public JsonArchiveInterface
{
public:
    JsonArchive();

    virtual ~JsonArchive();

    bool open(QWidget* parent = nullptr);
    bool save(QWidget* parent = nullptr);

    virtual void read(const QJsonObject& json) override;
    virtual void write(QJsonObject& json) override;

private:
    bool loadFile(const QString& fileName);
    bool saveFile(const QString& fileName);

    QString directory_;
};

void set(QJsonObject& json, const QString& key, const int& value);
void set(QJsonObject& json, const QString& key, const double& value);
void set(QJsonObject& json, const QString& key, const bool& value);
void set(QJsonObject& json, const QString& key, const QString& value);

int get(const QJsonObject& json, const QString& key, const int& init);
double get(const QJsonObject& json, const QString& key, const double& init);
bool get(const QJsonObject& json, const QString& key, const bool& init);
QString get(const QJsonObject& json, const QString& key, const char* init);

void set(QJsonObject& json, const QString& key, QVector<int>& vector);
void set(QJsonObject& json, const QString& key, QVector<double>& vector);
void set(QJsonObject& json, const QString& key, QVector<bool>& vector);
void set(QJsonObject& json, const QString& key, QVector<QString>& vector);

bool get(const QJsonObject& json, const QString& key, QVector<int>& vector);
bool get(const QJsonObject& json, const QString& key, QVector<double>& vector);
bool get(const QJsonObject& json, const QString& key, QVector<bool>& vector);
bool get(const QJsonObject& json, const QString& key, QVector<QString>& vector);

}  // namespace rqt2_util

#endif  // RQT2_UTIL__JSON_ARCHIVE_HPP_
