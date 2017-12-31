#include "interact.h"
#include <QQmlApplicationEngine>
#include <QDebug>
#include "httprequestworker.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QStringList>
Interact::Interact(QObject *parent, QQmlApplicationEngine &engine):QObject{parent},engine_{engine}
{
}

void Interact::Run()
{
    rootObject_ = engine_.rootObjects()[0];
    qDebug()<<rootObject_->objectName();
    QObject* home = engine_.rootObjects().first()->findChild<QObject*>("loginObject");
    QObject *logout = engine_.rootObjects().first()->findChild<QObject*>("sidePanelObject");
    connect(home, SIGNAL(loginSignal(QString, QString)), this, SLOT(onLoginSignal(QString,QString)));
    connect(logout, SIGNAL(logOutSignal()),this,SLOT(onLogOutSignal()));
}

void Interact::RetrieveStations()
{
    QString url = "http://localhost:5000/GetStations";
    HttpRequestInput input(url,"GET");
    HttpRequestWorker *worker = new HttpRequestWorker(this);
    connect(worker,SIGNAL(on_execution_finished(HttpRequestWorker*)),this,SLOT(handleRetrieveStationsResult(HttpRequestWorker*)));
    worker->execute(&input);
}

void Interact::onLoginSignal(QString username, QString password)
{
    QString url = "http://localhost:5000/LogIn";
    HttpRequestInput input(url,"POST");
    input.add_var("email",username);
    input.add_var("password",password);
    HttpRequestWorker *worker = new HttpRequestWorker(this);
    connect(worker,SIGNAL(on_execution_finished(HttpRequestWorker*)),this,SLOT(handleResult(HttpRequestWorker*)));
    worker->execute(&input);
}

void Interact::onLogOutSignal()
{
    QString url = "http://localhost:5000/LogIn";
    HttpRequestInput input(url,"GET");
    HttpRequestWorker *worker = new HttpRequestWorker(this);
    connect(worker,SIGNAL(on_execution_finished(HttpRequestWorker*)),this,SLOT(handleLogOutResult(HttpRequestWorker*)));
    worker->execute(&input);
}

void Interact::handleResult(HttpRequestWorker *worker)
{
    QString response;
    QObject *loader = engine_.rootObjects().first()->findChild<QObject*>("loaderObject");
    qDebug()<<loader->objectName();
    if(worker->error_type == QNetworkReply::NoError) {
        response = "Success, response: "+worker->response;
        loader->setProperty("source","qrc:/MainView.qml");
        RetrieveStations();
    }
    else {
        response = "Error: " + worker->error_str+'\n'+worker->response;
    }
    qDebug() << response;
}

void Interact::handleLogOutResult(HttpRequestWorker *worker)
{
    QObject *loader = engine_.rootObjects().first()->findChild<QObject*>("loaderObject");
    loader->setProperty("source","qrc:/LoginScreen.qml");

}

void Interact::handleRetrieveStationsResult(HttpRequestWorker *worker)
{
    qDebug()<<"Welcome from stations";
    if(worker->error_type == QNetworkReply::NoError) {
        QJsonParseError error;
        QJsonDocument document = QJsonDocument::fromJson(worker->response,&error);
        QJsonObject jsonObject = document.object();
        QJsonArray jsonArray = jsonObject["stations"].toArray();
        QString stationName;
        uint16_t stationNumber;
        QStringList list;
        foreach (const QJsonValue & v, jsonArray) {
             stationName = v.toObject().value("Name").toString();
             stationNumber = v.toObject().value("StationID").toInt();
             list.append(stationName);
        }
        stations(list);
    }
    else {
        qDebug()<<worker->response;
        qDebug()<<"error in stations";
    }
}
