#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H
#include <QString>
#include <QSettings>
#include <QObject>
class SettingsManager: public QObject
{
    Q_OBJECT
public:
    SettingsManager(QObject *parent=nullptr);
    Q_INVOKABLE QVariant GetSetting(QString group, QString name);
    Q_INVOKABLE QVariant getSetting(QString group, QString name);
    Q_INVOKABLE int saveSetting(QString group, QString name, QVariant value);
    Q_INVOKABLE int SaveSetting(QString group, QString name, QVariant value);
private:
    QSettings settings_;
};

#endif // SETTINGSMANAGER_H
