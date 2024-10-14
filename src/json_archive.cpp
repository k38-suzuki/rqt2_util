#include "rqt2_util/json_archive.hpp"

#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QJsonArray>
#include <QJsonDocument>

namespace rqt2_util
{

JsonArchive::JsonArchive()
    : directory_("/home")
{

}

JsonArchive::~JsonArchive()
{

}

bool JsonArchive::open(QWidget* parent)
{
    QString fileName = QFileDialog::getOpenFileName(parent, "Open File",
        directory_,
        "JSON Files (*.json);;All Files (*)");

    if(fileName.isEmpty()) {
        return false;
    } else {
        QFileInfo info(fileName);
        directory_ = info.absolutePath();
        loadFile(fileName);
    }

    return true;
}

bool JsonArchive::save(QWidget* parent)
{
    QString fileName = QFileDialog::getSaveFileName(parent, "Save File",
        directory_,
        "JSON Files (*.json);;All Files (*)");

    if(fileName.isEmpty()) {
        return false;
    } else {
        QFileInfo info(fileName);
        QString ext = info.suffix();
        if(ext.isEmpty()) {
            fileName += ".json";
        }
        directory_ = info.absolutePath();
        saveFile(fileName);
    }

    return true;
}

void JsonArchive::set(QJsonObject& json, const QString& key, const int& value)
{
    json[key] = value;
}

void JsonArchive::set(QJsonObject& json, const QString& key, const double& value)
{
    json[key] = value;
}

void JsonArchive::set(QJsonObject& json, const QString& key, const bool& value)
{
    json[key] = value;
}

void JsonArchive::set(QJsonObject& json, const QString& key, const QString& value)
{
    json[key] = value;
}

int JsonArchive::get(const QJsonObject& json, const QString& key, const int& init) const
{
    int ret = init;
    if(const QJsonValue v = json[key]; v.isDouble()) {
        ret = v.toInt();
    }
    return ret;
}

double JsonArchive::get(const QJsonObject& json, const QString& key, const double& init) const
{
    double ret = init;
    if(const QJsonValue v = json[key]; v.isDouble()) {
        ret = v.toDouble();
    }
    return ret;
}

bool JsonArchive::get(const QJsonObject& json, const QString& key, const bool& init) const
{
    bool ret = init;
    if(const QJsonValue v = json[key]; v.isBool()) {
        ret = v.toBool();
    }
    return ret;
}

QString JsonArchive::get(const QJsonObject& json, const QString& key, const char* init) const
{
    QString ret = init;
    if(const QJsonValue v = json[key]; v.isString()) {
        ret = v.toString();
    }
    return ret;
}

void JsonArchive::set(QJsonObject& json, const QString& key, QVector<int>& vector)
{
    QJsonArray array;
    for(const auto& value : vector) {
        array.append(value);
    }
    json[key] = array;
}

void JsonArchive::set(QJsonObject& json, const QString& key, QVector<double>& vector)
{
    QJsonArray array;
    for(const auto& value : vector) {
        array.append(value);
    }
    json[key] = array;
}

void JsonArchive::set(QJsonObject& json, const QString& key, QVector<bool>& vector)
{
    QJsonArray array;
    for(const auto& value : vector) {
        array.append(value);
    }
    json[key] = array;
}

void JsonArchive::set(QJsonObject& json, const QString& key, QVector<QString>& vector)
{
    QJsonArray array;
    for(const auto& value : vector) {
        array.append(value);
    }
    json[key] = array;
}

bool JsonArchive::get(const QJsonObject& json, const QString& key, QVector<int>& vector)
{
    vector.clear();
    if(const QJsonValue v = json[key]; v.isArray()) {
        const QJsonArray array = v.toArray();
        for(const auto& value : array) {
            vector.push_back(value.toInt());
        }
        return true;
    }
    return false;
}

bool JsonArchive::get(const QJsonObject& json, const QString& key, QVector<double>& vector)
{
    vector.clear();
    if(const QJsonValue v = json[key]; v.isArray()) {
        const QJsonArray array = v.toArray();
        for(const auto& value : array) {
            vector.push_back(value.toDouble());
        }
        return true;
    }
    return false;
}

bool JsonArchive::get(const QJsonObject& json, const QString& key, QVector<bool>& vector)
{
    vector.clear();
    if(const QJsonValue v = json[key]; v.isArray()) {
        const QJsonArray array = v.toArray();
        for(const auto& value : array) {
            vector.push_back(value.toBool());
        }
        return true;
    }
    return false;
}

bool JsonArchive::get(const QJsonObject& json, const QString& key, QVector<QString>& vector)
{
    vector.clear();
    if(const QJsonValue v = json[key]; v.isArray()) {
        const QJsonArray array = v.toArray();
        for(const auto& value : array) {
            vector.push_back(value.toString());
        }
        return true;
    }
    return false;
}

bool JsonArchive::loadFile(const QString& fileName)
{
    QFile loadFile(fileName);

    if(!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open save file.");
        return false;
    }

    QByteArray saveData = loadFile.readAll();

    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));

    read(loadDoc.object());

    return true;
}

bool JsonArchive::saveFile(const QString& fileName)
{
    QFile saveFile(fileName);

    if(!saveFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
        return false;
    }

    QJsonObject jsonObject;
    write(jsonObject);
    saveFile.write(QJsonDocument(jsonObject).toJson());

    return true;
}

}  // namespace rqt2_util
