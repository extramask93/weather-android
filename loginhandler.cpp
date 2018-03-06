#include "loginhandler.h"
#include <iostream>
#include <QString>
#include <QDebug>
#include <QSettings>
#include "httprequestworker.h"
LoginHandler::LoginHandler(SettingsManager *manager,QObject *parent): QObject{parent},settingsManager_{manager}
{
    loadCredentialsFromFile();
}

void LoginHandler::Login(QString username, QString password)
{
    QString url = "http://"+settingsManager_->GetSetting("Server","ip").toString()+":"
            +QString::number(settingsManager_->GetSetting("Server","port").toInt())
            +"/LogIn";
    HttpRequestInput input(url,"POST");
    input.add_var("email",username);
    input.add_var("password",password);
    if(rememberMe()) {
        saveCredentialsToFile();
    }
    HttpRequestWorker *worker = new HttpRequestWorker(this);
    connect(worker,SIGNAL(on_execution_finished(HttpRequestWorker*)),this,SLOT(HandleLoginResult(HttpRequestWorker*)));
    worker->execute(&input);
}
void LoginHandler::HandleLoginResult(HttpRequestWorker *worker) {
    if(worker->error_type == QNetworkReply::NoError) {
        emit loginSuccess();
    }
    else {
        if(worker->response != "")
            emit loginFailed(worker->error_type,worker->response);
        else
            emit loginFailed(worker->error_type,worker->error_str);
    }
    worker->deleteLater();
}
void LoginHandler::LogOut()
{
    QString url = "http://"+settingsManager_->GetSetting("Server","ip").toString()+":"
            +QString::number(settingsManager_->GetSetting("Server","port").toInt())+"/LogOut";
    HttpRequestInput input(url,"GET");
    HttpRequestWorker *worker = new HttpRequestWorker(this);
    connect(worker,SIGNAL(on_execution_finished(HttpRequestWorker*)),this,SLOT(HandleLogOutResult(HttpRequestWorker*)));
    worker->execute(&input);
    emit loggedOut();
}
void LoginHandler::HandleLogOutResult(HttpRequestWorker *worker) {
    worker->deleteLater();
}

void LoginHandler::loadCredentialsFromFile()
{
    login(settingsManager_->GetSetting("Credentials","login").toString());
    password(settingsManager_->GetSetting("Credentials","password").toString());
    rememberMe(settingsManager_->GetSetting("Credentials","rememberMe").toBool());
}

int LoginHandler::saveCredentialsToFile()
{
    settingsManager_->SaveSetting("Credentials","login",login());
    settingsManager_->SaveSetting("Credentials","password",password());
    settingsManager_->SaveSetting("Credentials","rememberMe",rememberMe());
    return 0;
}

