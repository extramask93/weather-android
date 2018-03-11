#include "registermodel.h"
#include "settingsmanager.h"
#include "stationmanager.h"
RegisterModel::RegisterModel(QObject *parent) : QObject(parent)
{

}

void RegisterModel::registerUser(QString name, QString email, QString password, QString phone)
{
    QString url = "http://"+SettingsManager::getSetting("Server","ip").toString()+":"
            +SettingsManager::getSetting("Server","port").toString()+"/CreateUser";
    HttpRequestWorker *worker = new HttpRequestWorker(this);
    HttpRequestInput input(url,"POST");
    input.add_var("email",email);
    input.add_var("password",password);
    input.add_var("userName",name);
    input.add_var("phone",phone);
    connect(worker,SIGNAL(on_execution_finished(HttpRequestWorker*)),this, SLOT(HandleResult(HttpRequestWorker*)));
    worker->execute(&input);
}

void RegisterModel::HandleResult(HttpRequestWorker *worker)
{
    if(worker->error_type == QNetworkReply::NoError) {
        emit registrationSuccess();
    }
    else {
        emit registrationFailed(StationManager::getMessageString(worker));
    }
    worker->deleteLater();
}
