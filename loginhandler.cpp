#include "loginhandler.h"
#include <iostream>
#include <QString>
#include <QDebug>
LoginHandler::LoginHandler(QQmlApplicationEngine &engine,QObject *parent) : QObject(parent), engine_{engine}
{
    isLogged(false);
    state(State::Login);
}

void LoginHandler::onLoginScreenLoaded()
{
    qDebug()<<engine_.baseUrl().toString();
    qDebug()<<engine_.rootObjects().isEmpty();
    //.first()->findChild<QObject*>("loginObject");
    //auto username = home->findChild<QObject*>("userTextObject");
    //auto password = home->findChild<QObject*>("passwordTextObject");
    //password->setProperty("text","cloakengage2@gmail.com");
    //username->setProperty("text","admin123");
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

