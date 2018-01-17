#ifndef LOGINHANDLER_H
#define LOGINHANDLER_H

#include <QObject>
#include <QHostAddress>
#include <QQmlApplicationEngine>
#include "propertyhelper.h"
class QString;

class LoginHandler : public QObject
{
    Q_OBJECT
public:
    AUTO_PROPERTY(QString, login)
    AUTO_PROPERTY(QString, password)
    AUTO_PROPERTY(bool, rememberMe)
    AUTO_PROPERTY(bool, isLogged)
    AUTO_PROPERTY(QString, message)
    QQmlApplicationEngine &engine_;
public:
    explicit LoginHandler(QQmlApplicationEngine  &engine,QObject *parent = nullptr);
    ~LoginHandler();
    enum State {Login, Main, Settings};
    void loadCredentialsFromFile();
    Q_INVOKABLE int saveCredentialsToFile();
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
