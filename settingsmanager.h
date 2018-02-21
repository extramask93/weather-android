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
    Q_INVOKABLE static QVariant GetSetting(QString group, QString name);
    Q_INVOKABLE static QVariant getSetting(QString group, QString name);
    Q_INVOKABLE static int saveSetting(QString group, QString name, QVariant value);
    Q_INVOKABLE static int SaveSetting(QString group, QString name, QVariant value);
};

#endif // SETTINGSMANAGER_H
