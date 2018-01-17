#include "settingshandler.h"

SettingsHandler::SettingsHandler(QObject *parent) : QObject(parent)
{

}

SettingsHandler::~SettingsHandler()
{
   saveIPConfigToFile();
}
void LoginHandler::loadIPConfigFromFile()
{
    QSettings settings_("Jozek","Robots");
    settings_.beginGroup("Server");
    ip(settings_.value("IP","localhost").toString());
    port(settings_.value("PORT",5000).toInt());
    settings_.endGroup();
}

void LoginHandler::saveIPConfigToFile()
{
    QSettings settings_("Jozek","Robots");
    settings_.beginGroup("Server");
    settings_.remove("");
    settings_.setValue("IP",ip());
    settings_.setValue("PORT",port());
    settings_.endGroup();
}
