#ifndef LOGINHANDLER_H
#define LOGINHANDLER_H

#include <QObject>
#include <QHostAddress>
#include <QQmlApplicationEngine>
#include "propertyhelper.h"

class LoginHandler : public QObject
{
    Q_OBJECT
    AUTO_PROPERTY(unsigned int, port)
    AUTO_PROPERTY(QString, ip)
    AUTO_PROPERTY(bool, isLogged)
    AUTO_PROPERTY(QString, message)
    QQmlApplicationEngine &engine_;
public:
    explicit LoginHandler(QQmlApplicationEngine  &engine,QObject *parent = nullptr);
    enum State {Login, Main, Settings};
    Q_ENUM(State)
    AUTO_PROPERTY(State, state)
public slots:
    void onLoginScreenLoaded();
    void doLogin(QString name, QString password);
    void doChangeState(State s);
signals:
    void loginSuccess();
    void loginFailed(QString reason);
public slots:
};

#endif // LOGINHANDLER_H
