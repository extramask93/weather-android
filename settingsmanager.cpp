#include "settingsmanager.h"

SettingsManager::SettingsManager(QObject *parent) :QObject{parent}
{
}

QVariant SettingsManager::GetSetting(QString group, QString name)
{
    QSettings settings_{"Jozek","Robot"};
    settings_.beginGroup(group);
    QVariant result = settings_.value(name,"asd");
    settings_.endGroup();
    return result;
}

QVariant SettingsManager::getSetting(QString group, QString name)
{
    return GetSetting(group,name);
}

int SettingsManager::saveSetting(QString group, QString name, QVariant value)
{
    return SaveSetting(group,name,value);
}

int SettingsManager::SaveSetting(QString group, QString name, QVariant value)
{
    QSettings settings_{"Jozek","Robot"};
    settings_.beginGroup(group);
    settings_.remove(name);
    settings_.setValue(name,value);
    settings_.endGroup();
    return 0;
}
