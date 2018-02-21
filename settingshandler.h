#ifndef SETTINGSHANDLER_H
#define SETTINGSHANDLER_H

#include <QObject>
#include <QString>
#include<QSettings>
#include "propertyhelper.h"
class SettingsHandler : public QObject
{
    Q_OBJECT
    AUTO_PROPERTY(unsigned int, port)
    AUTO_PROPERTY(QString, ip)
public:
    explicit SettingsHandler(QObject *parent = nullptr);
    ~SettingsHandler();
    void loadIPConfigFromFile();
    Q_INVOKABLE void saveIPConfigToFile();
signals:

public slots:
};

#endif // SETTINGSHANDLER_H
