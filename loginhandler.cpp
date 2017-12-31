#include "loginhandler.h"
#include <iostream>
#include <QString>
#include <QDebug>
LoginHandler::LoginHandler(QObject *parent) : QObject(parent)
{
    isLogged(false);
    state(State::Login);
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

