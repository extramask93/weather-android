#include "settings.h"
#include <QFile>
#include <QDir>
#include <QJsonArray>
#include <QStandardPaths>
static auto RESOURCE_PREFIX = QStringLiteral(":/json");
Settings::Settings(QObject *parent, QString filename) : QObject(parent), filename_{filename}, stat_{*new QStringListModel{this}}
{
    ParseJSON();
}

QString Settings::LoadJSON()
{
    auto defaultSettings = ReadJSONFromInternalResource();
    QDir configDir = OpenConfigurationDirectory();
    auto path = configDir.filePath(filename_);
    QFile stdFile(path);
    if(stdFile.exists()) {
        if(!stdFile.open(QFile::ReadOnly|QFile::Text)) {
            SendErrorMessage("Could not open "+path);
            return defaultSettings;
        }
        QString settings = stdFile.readAll();
        stdFile.close();
        return settings;
    }
    else {
        WriteDefaultsToStdConfigFile(stdFile,defaultSettings);
        return defaultSettings;
    }
}

void Settings::ParseJSON()
{
    QString rawJSON = LoadJSON();
    if(rawJSON.size()==0)
        return;
    auto jsonResult = GetJsonObject(rawJSON);
    auto jsonErr = jsonResult.second;
    if(jsonErr.error != QJsonParseError::NoError)
    {
        SendErrorMessage("Parse json error");
        return;
    }
    auto jsonObj = jsonResult.first;
    appTitle_=jsonObj["applicationTitle"].toString();
    shortAppTitle_=jsonObj["appShortName"].toString();
    ip_ = jsonObj["hostname"].toString();
    port_=jsonObj["port"].toInt();
    longWait_=jsonObj["tcpLongWaitMS"].toInt();
    shortWait_=jsonObj["tcpShortWaitMS"].toInt();
    auto ar = jsonObj["stations"].toArray();
    for(auto item : ar)
        stations_.append(item.toString());
    stat_.setStringList(stations_);
}

JsonObjErrPair Settings::GetJsonObject(const QString &raw)
{
    QJsonParseError jsonParseError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(raw.toUtf8(),&jsonParseError);
    QJsonObject jsonObj = jsonDoc.object();
    return std::make_pair(jsonObj,jsonParseError);
}
QString Settings::ReadJSONFromInternalResource()
{
    QDir resDir{RESOURCE_PREFIX};
    if(!resDir.exists()){
        SendErrorMessage("Internal resource path missing" + resDir.canonicalPath());
        return "";}
    auto path = resDir.filePath(filename_);
    QFile file{path};
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        SendErrorMessage("Cannton open internal resource: " + path);
        return "";//
    }
    QString settings = file.readAll();
    return settings;
}

void Settings::SendErrorMessage(const QString &msg)
{
    emit NotifyStatusMessage(msg);
}

QDir Settings::OpenConfigurationDirectory()
{
    QDir configDir{QStandardPaths::writableLocation(QStandardPaths::ConfigLocation)};
    if(!configDir.exists())
    {
        QDir dir;
        dir.mkpath(configDir.path());
    }
    return configDir;
}

void Settings::WriteDefaultsToStdConfigFile(QFile &file, const QString &sets)
{
    if(!file.open(QFile::WriteOnly | QFile::Text)) {
        ;//error
    }
    file.write(qPrintable(sets),sets.length());
    file.close();
}
