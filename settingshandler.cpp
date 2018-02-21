#include "settingshandler.h"

SettingsHandler::SettingsHandler(QObject *parent) : QObject(parent)
{
    loadIPConfigFromFile();
}

SettingsHandler::~SettingsHandler()
{
   saveIPConfigToFile();
}
void SettingsHandler::loadIPConfigFromFile()
{
    QSettings settings_("Jozek","Robots");
    settings_.beginGroup("Server");
    ip(settings_.value("IP","localhost").toString());
    port(settings_.value("PORT",5000).toInt());
    settings_.endGroup();
}

void SettingsHandler::saveIPConfigToFile()
{
    QSettings settings_("Jozek","Robots");
    settings_.beginGroup("Server");
    settings_.remove("");
    settings_.setValue("IP",ip());
    settings_.setValue("PORT",port());
    settings_.endGroup();
}
