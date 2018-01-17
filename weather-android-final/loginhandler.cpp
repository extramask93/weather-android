#include "loginhandler.h"
#include <iostream>
#include <QString>
#include <QDebug>
#include <QSettings>
LoginHandler::LoginHandler(QQmlApplicationEngine &engine,QObject *parent) : QObject(parent), engine_{engine}
{
    isLogged(false);
    state(State::Login);
    loadCredentialsFromFile();
}

LoginHandler::~LoginHandler()
{
    if(rememberMe())
        saveCredentialsToFile();
}

void LoginHandler::loadCredentialsFromFile()
{
    QSettings settings_("Jozek","Robots");
    settings_.beginGroup("Credentials");
    login(settings_.value("login","").toString());
    password(settings_.value("password","").toString());
    rememberMe(settings_.value("rememberMe",false).toBool());
    settings_.endGroup();
}

int LoginHandler::saveCredentialsToFile()
{
    QSettings settings_("Jozek","Robots");
    settings_.beginGroup("Credentials");
    settings_.remove("");
    settings_.setValue("login",login());
    settings_.setValue("password",password());
    settings_.setValue("rememberMe",rememberMe());
    settings_.endGroup();

    return 0;
}

void LoginHandler::onLoginScreenLoaded()
{
    qDebug()<<engine_.baseUrl().toString();
    qDebug()<<engine_.rootObjects().isEmpty();
}

void LoginHandler::doLogin(QString name, QString password)
{
    if(name == "extramask" && password == "123")
    {
        isLogged(true);
        state(State::Main);
    }
    else {
        isLogged(false);
        message("Login or password incorrect");
        state(State::Login);
    }
}

void LoginHandler::doChangeState(LoginHandler::State s)
{
    state(s);
}

