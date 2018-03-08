#include "stationmanager.h"
#include "settingsmanager.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
StationManager::StationManager(QObject *parent) : QObject(parent)
{
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
    input.add_var("ID",QString::number(tempStation_.id));
    input.add_var("Name",tempStation_.name);
    input.add_var("RefTime",tempStation_.reftime.toString("hh:mm:ss"));
    input.add_var("Temperature",QString::number(tempStation_.tempSensor.enabled));
    input.add_var("Humidity",QString::number(tempStation_.humiditySensor.enabled));
    input.add_var("Lux",QString::number(tempStation_.luxSensor.enabled));
    input.add_var("Soil",QString::number(tempStation_.soilSensor.enabled));
    input.add_var("Battery",QString::number(tempStation_.batterySensor.enabled));
    input.add_var("Co2",QString::number(tempStation_.co2Sensor.enabled));
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
    input.add_var("ID",QString::number(tempStation_.id));
    input.add_var("Name",tempStation_.name);
    input.add_var("RefTime",tempStation_.reftime.toString("hh:mm:ss"));
    input.add_var("Temperature",QString::number(tempStation_.tempSensor.enabled));
    input.add_var("Humidity",QString::number(tempStation_.humiditySensor.enabled));
    input.add_var("Lux",QString::number(tempStation_.luxSensor.enabled));
    input.add_var("Soil",QString::number(tempStation_.soilSensor.enabled));
    input.add_var("Battery",QString::number(tempStation_.batterySensor.enabled));
    input.add_var("Co2",QString::number(tempStation_.co2Sensor.enabled));
    HttpRequestWorker *worker = new HttpRequestWorker(this);
    connect(worker,&HttpRequestWorker::on_execution_finished,this,&StationManager::handleAddStationResult);
    worker->execute(&input);
}

void StationManager::removeCurrentStation()
{
    QString url = QString("http://")+SettingsManager::getSetting("Server","ip").toString()
            +":"+SettingsManager::getSetting("Server","port").toString()+"/RemoveStation";
    HttpRequestInput input(url,"POST");
    input.add_var("ID",QString::number(currentStation_.id));
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
    currentStationEnables(QList<bool>{currentStation_.tempSensor.enabled,currentStation_.humiditySensor.enabled, currentStation_.soilSensor.enabled,
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
        uint16_t stationNumber;
        QString enableSettings = 0;
        QStringList list;
        realStations_.clear();
        list.clear();
        foreach (const QJsonValue & v, jsonArray) {
             stationName = v.toObject().value("Name").toString();
             stationNumber = v.toObject().value("StationID").toString().toInt();
             enableSettings = v.toObject().value("enableSettings").toString();
             list.append(stationName);
             realStations_.append(Station(stationNumber,stationName,std::bitset<6>(enableSettings.toStdString())));
        }
        stations(list);
        onStationChanged(0);
    }
}

void StationManager::handleUpdateStationResult(HttpRequestWorker *worker)
{
    if(worker->error_type == QNetworkReply::NoError) {
        retrieveStations();
        emit updateSucceed();
    }
    else {
        emit updateFailed(worker->error_str);
    }
}

void StationManager::handleRemoveCurrentStationResult(HttpRequestWorker *worker)
{
    if(worker->error_type == QNetworkReply::NoError) {
        retrieveStations();
        emit removeSucceed();
    }
    else {
        emit removeFailed(worker->error_str);
    }
}

void StationManager::handleAddStationResult(HttpRequestWorker *worker)
{
    if(worker->error_type == QNetworkReply::NoError) {
        retrieveStations();
        emit addSucceed();
    }
    else {
        emit addFailed(worker->error_str);
    }
}
