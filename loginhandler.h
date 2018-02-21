#ifndef LOGINHANDLER_H
#define LOGINHANDLER_H

#include <QObject>
#include <QHostAddress>
#include <QQmlApplicationEngine>
#include "propertyhelper.h"
#include "httprequestworker.h"
#include "settingsmanager.h"
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
public:
    explicit LoginHandler(SettingsManager *manager,QObject *parent = nullptr);
    void loadCredentialsFromFile();
    Q_INVOKABLE int saveCredentialsToFile();
public slots:
    Q_INVOKABLE void Login(QString email, QString password);
    Q_INVOKABLE void LogOut();
    void HandleLoginResult(HttpRequestWorker *worker);
    void HandleLogOutResult(HttpRequestWorker *worker);
signals:
     void loginFailed(int errorCode,QString message);
     void loginSuccess();
     void loggedOut();
private:
   HttpRequestWorker *worker_;
   SettingsManager *settingsManager_;
};

#endif // LOGINHANDLER_H
