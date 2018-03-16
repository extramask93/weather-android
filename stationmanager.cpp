#include "stationmanager.h"
#include "settingsmanager.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QQmlContext>
#include <QJsonArray>
#include <algorithm>
StationManager::StationManager(QQmlApplicationEngine * engine,QObject *parent) : QObject(parent)
{
    stationsStrings = new QStringListModel(this);
    this->engine = engine;
    engine->rootContext()->setContextProperty("StationsStrings",stationsStrings);
    currentStation_ = Station(0,"Empty");
    currentStationEnables(currentStation_.getBool());
    currentStationID(currentStation_.id);
    currentStationName(currentStation_.name);
    currentStationTime(currentStation_.reftime);
}

void StationManager::updateStation(quint8 id, QString name, quint8 hour, quint8 minute, quint8 second, bool temp, bool hum, bool lux, bool soil, bool bat, bool co2)
{
    tempStation_ = Station(id,name);
    tempStation_.reftime = QTime(hour,minute,second);
    tempStation_.setFromBool(temp,hum,lux,soil,bat,co2);
    QString url = QString("http://")+SettingsManager::getSetting("Server","ip").toString()
            +":"+SettingsManager::getSetting("Server","port").toString()+"/ModStation";
    HttpRequestInput input(url,"POST");
    input.add_var("StationID",QString::number(tempStation_.id));
    input.add_var("Name",tempStation_.name);
    input.add_var("refTime",tempStation_.reftime.toString("hh:mm:ss"));
    auto list = tempStation_.getBool();
    QString tempstr = "";
    for(auto element:list) {
        tempstr+= QString::number(element);
    }
    input.add_var("settings",tempstr);
    HttpRequestWorker *worker = new HttpRequestWorker(this);
    connect(worker,&HttpRequestWorker::on_execution_finished,this,&StationManager::handleUpdateStationResult);
    worker->execute(&input);
}

void StationManager::addStation(quint8 id, QString name, quint8 hour, quint8 minute, quint8 second, bool temp, bool hum, bool lux, bool soil, bool bat, bool co2)
{
    tempStation_ = Station(id,name);
    tempStation_.reftime = QTime(hour,minute,second);
    tempStation_.setFromBool(temp,hum,lux,soil,bat,co2);
    QString url = QString("http://")+SettingsManager::getSetting("Server","ip").toString()
            +":"+SettingsManager::getSetting("Server","port").toString()+"/AddStation";
    HttpRequestInput input(url,"POST");
    input.add_var("StationID",QString::number(tempStation_.id));
    input.add_var("Name",tempStation_.name);
    input.add_var("refTime",QString::number(QTime(0,0,0).secsTo(tempStation_.reftime)));
    auto list = tempStation_.getBool();
    QString tempstr = "";
    for(auto element:list) {
        tempstr+= QString::number(element);
    }
    input.add_var("settings",tempstr);
    HttpRequestWorker *worker = new HttpRequestWorker(this);
    connect(worker,&HttpRequestWorker::on_execution_finished,this,&StationManager::handleAddStationResult);
    worker->execute(&input);
}

void StationManager::removeCurrentStation()
{
    QString url = QString("http://")+SettingsManager::getSetting("Server","ip").toString()
            +":"+SettingsManager::getSetting("Server","port").toString()+"/RemoveStation";
    HttpRequestInput input(url,"POST");
    input.add_var("StationID",QString::number(currentStation_.id));
    HttpRequestWorker *worker = new HttpRequestWorker(this);
    connect(worker,&HttpRequestWorker::on_execution_finished,this,&StationManager::handleRemoveCurrentStationResult);
    worker->execute(&input);
}

void StationManager::setCurrentStation(int index)
{
    if(index<0 || index >=realStations_.length())
        return;
    currentStation_ = realStations_[index];
    currentStationID(currentStation_.id);
    currentStationName(currentStation_.name);
    currentStationTime(currentStation_.reftime);
    currentStationEnables(QList<bool>{currentStation_.tempSensor.enabled,currentStation_.humiditySensor.enabled, currentStation_.luxSensor.enabled,
                                      currentStation_.soilSensor.enabled,
                                      currentStation_.batterySensor.enabled, currentStation_.co2Sensor.enabled});
}

void StationManager::retrieveStations()
{
    QString url = QString("http://")+SettingsManager::getSetting("Server","ip").toString()
            +":"+SettingsManager::getSetting("Server","port").toString()+"/GetStations";
    HttpRequestInput input(url,"GET");
    HttpRequestWorker *worker = new HttpRequestWorker(this);
    connect(worker,&HttpRequestWorker::on_execution_finished,this,&StationManager::handleRetrieveStationsResult);
    worker->execute(&input);
}

void StationManager::onStationChanged(int index)
{
    setCurrentStation(index);
}

void StationManager::handleRetrieveStationsResult(HttpRequestWorker *worker)
{
    if(worker->error_type == QNetworkReply::NoError) {
        QJsonParseError error;
        QJsonDocument document = QJsonDocument::fromJson(worker->response,&error);
        QJsonObject jsonObject = document.object();
        QJsonArray jsonArray = jsonObject["stations"].toArray();
        QString stationName;
        QString refTime;
        uint16_t stationNumber;
        QString enableSettings = 0;
        QStringList list;
        realStations_.clear();
        stationsStrings->setStringList(QStringList());
        list.clear();
        foreach (const QJsonValue & v, jsonArray) {
             stationName = v.toObject().value("Name").toString();
             stationNumber = v.toObject().value("StationID").toString().toInt();
             enableSettings = v.toObject().value("enableSettings").toString();
             refTime = v.toObject().value("refTime").toString();
             list.append(stationName);
             Station tempStation(stationNumber,stationName,std::bitset<6>(enableSettings.toStdString()));
             auto secs = refTime.toInt();
             auto tim = QTime(0,0,0).addSecs(secs);
             tempStation.reftime = tim;
             realStations_.append(tempStation);

        }
        stationsStrings->setStringList(list);
        //engine->rootContext()->setContextProperty("StationsStrings",stationsStrings);
        stations(list);
        onStationChanged(0);
    }
    worker->deleteLater();
}

void StationManager::handleUpdateStationResult(HttpRequestWorker *worker)
{
    if(worker->error_type == QNetworkReply::NoError) {
        retrieveStations();
        emit updateSucceed();
    }
    else {
        emit updateFailed(getMessageString(worker));
    }
    worker->deleteLater();
}

void StationManager::handleRemoveCurrentStationResult(HttpRequestWorker *worker)
{
    if(worker->error_type == QNetworkReply::NoError) {
        retrieveStations();
        emit removeSucceed();
    }
    else {
        emit removeFailed(getMessageString(worker));
    }
    worker->deleteLater();
}

void StationManager::handleAddStationResult(HttpRequestWorker *worker)
{
    if(worker->error_type == QNetworkReply::NoError) {
        retrieveStations();
        emit addSucceed();
    }
    else {
        emit addFailed(getMessageString(worker));
    }
    worker->deleteLater();
}

QString StationManager::getMessageString(HttpRequestWorker *worker)
{
    QJsonParseError error;
    QJsonDocument document = QJsonDocument::fromJson(worker->response,&error);
    if(error.error != QJsonParseError::NoError)
        return worker->error_str;
    QJsonObject jsonObject = document.object();
    return jsonObject.value("message").toString();

}
