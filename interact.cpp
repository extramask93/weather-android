#include "interact.h"
#include <QQmlApplicationEngine>
#include <QDebug>
#include "httprequestworker.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QStringList>
#include <QQuickItem>
#include <QQmlContext>
#include <QTimer>
#include <QChart>
#include <QtCharts>
#include <QAbstractSeries>
#include <QAbstractAxis>
#include <QtConcurrent/QtConcurrent>
#include "calendar.h"
Interact::Interact(QObject *parent, QQmlApplicationEngine &engine, MeasurementsModel *modell, LoginHandler *login):
    QObject{parent},engine_{engine}, model{modell}, login_{login}
{
    Measurement *temperature = new Measurement(this,ReadingType::temperature);
    engine_.rootContext()->setContextProperty("Temperature",temperature);
    Measurement *humidity = new Measurement(this,ReadingType::humidity);
    engine_.rootContext()->setContextProperty("Humidity",humidity);
    Measurement *lux = new Measurement(this,ReadingType::lux);
    engine_.rootContext()->setContextProperty("Lux",lux);
    Measurement *co2 = new Measurement(this,ReadingType::co2);
    engine_.rootContext()->setContextProperty("Co2",co2);
    Measurement *soil = new Measurement(this,ReadingType::soil);
    engine_.rootContext()->setContextProperty("Soil",soil);
    Measurement *battery = new Measurement(this,ReadingType::battery);
    engine_.rootContext()->setContextProperty("Battery",battery);
    measurementList_.append(temperature);
    measurementList_.append(humidity);
    measurementList_.append(lux);
    measurementList_.append(co2);
    measurementList_.append(soil);
    measurementList_.append(battery);
    timer = std::make_unique<QTimer>(this);

}

Interact::~Interact()
{
    timer->stop();
    for(int i = 0; i<measurementList_.length();i++) {
        delete measurementList_[i];
        measurementList_[i] = nullptr;
    }
    measurementList_.clear();
}

void Interact::updateStation(quint8 id, QString name, quint8 hour, quint8 minute, quint8 second, bool temp, bool hum, bool lux, bool soil, bool bat, bool co2)
{
    tempStation = Station(id,name);
    tempStation.reftime = QTime(hour,minute,second);
    tempStation.setFromBool(temp,hum,lux,soil,bat,co2);
    QString url = QString("http://")+SettingsManager::getSetting("Server","ip").toString()
            +":"+SettingsManager::getSetting("Server","port").toString()+"/ModStation";
    HttpRequestInput input(url,"POST");
    input.add_var("ID",QString::number(tempStation.id));
    input.add_var("Name",tempStation.name);
    input.add_var("RefTime",tempStation.reftime.toString("hh:mm:ss"));
    input.add_var("Temperature",QString::number(tempStation.tempSensor.enabled));
    input.add_var("Humidity",QString::number(tempStation.humiditySensor.enabled));
    input.add_var("Lux",QString::number(tempStation.luxSensor.enabled));
    input.add_var("Soil",QString::number(tempStation.soilSensor.enabled));
    input.add_var("Battery",QString::number(tempStation.batterySensor.enabled));
    input.add_var("Co2",QString::number(tempStation.co2Sensor.enabled));
    HttpRequestWorker *worker = new HttpRequestWorker(this);
    connect(worker,&HttpRequestWorker::on_execution_finished,this,&Interact::handleUpdateStationResult);
    worker->execute(&input);
}

void Interact::addStation(quint8 id, QString name, quint8 hour, quint8 minute, quint8 second, bool temp, bool hum, bool lux, bool soil, bool bat, bool co2)
{
    tempStation = Station(id,name);
    tempStation.reftime = QTime(hour,minute,second);
    tempStation.setFromBool(temp,hum,lux,soil,bat,co2);
    QString url = QString("http://")+SettingsManager::getSetting("Server","ip").toString()
            +":"+SettingsManager::getSetting("Server","port").toString()+"/AddStation";
    HttpRequestInput input(url,"POST");
    input.add_var("ID",QString::number(tempStation.id));
    input.add_var("Name",tempStation.name);
    input.add_var("RefTime",tempStation.reftime.toString("hh:mm:ss"));
    input.add_var("Temperature",QString::number(tempStation.tempSensor.enabled));
    input.add_var("Humidity",QString::number(tempStation.humiditySensor.enabled));
    input.add_var("Lux",QString::number(tempStation.luxSensor.enabled));
    input.add_var("Soil",QString::number(tempStation.soilSensor.enabled));
    input.add_var("Battery",QString::number(tempStation.batterySensor.enabled));
    input.add_var("Co2",QString::number(tempStation.co2Sensor.enabled));
    HttpRequestWorker *worker = new HttpRequestWorker(this);
    connect(worker,&HttpRequestWorker::on_execution_finished,this,&Interact::handleAddStationResult);
    worker->execute(&input);
}

void Interact::removeCurrentStation()
{
    QString url = QString("http://")+SettingsManager::getSetting("Server","ip").toString()
            +":"+SettingsManager::getSetting("Server","port").toString()+"/RemoveStation";
    HttpRequestInput input(url,"POST");
    input.add_var("ID",QString::number(currentStation->id));
    HttpRequestWorker *worker = new HttpRequestWorker(this);
    connect(worker,&HttpRequestWorker::on_execution_finished,this,&Interact::handleRemoveCurrentStationResult);
    worker->execute(&input);
}

void Interact::onMainViewLoaded()
{
    RetrieveStations();
    connect(timer.get(),&QTimer::timeout,this,&Interact::updateDailyJSON);
    RetrieveStations();
    timer->start(3600);
}

void Interact::onSettingsLoaded()
{
    RetrieveStations();
}

void Interact::RetrieveStations()
{
    QString url = QString("http://")+SettingsManager::getSetting("Server","ip").toString()
            +":"+SettingsManager::getSetting("Server","port").toString()+"/GetStations";
    HttpRequestInput input(url,"GET");
    HttpRequestWorker *worker = new HttpRequestWorker(this);
    connect(worker,&HttpRequestWorker::on_execution_finished,this,&Interact::handleRetrieveStationsResult);
    worker->execute(&input);
}

void Interact::onUpdateChartSignal(QString type, qint64 index)
{
    static QString lasttype;
    if(type=="")
        type=lasttype;
    lasttype=type;
    switch(index) {
    case 0:
        model->getTodayData(currentStation->id,type);
        break;
    case 1:
        model->getLast3DaysData(currentStation->id,type);
        break;
    case 2:
        model->getWeeklyData(currentStation->id,type);
        break;
    case 3:
        model->getMonthlyData(currentStation->id,type);
        break;
    case 4:
        model->getYearlyData(currentStation->id,type);
        break;
    default:
        break;
    }
}

void Interact::handleRetrieveStationsResult(HttpRequestWorker *worker)
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
        stations_.clear();
        list.clear();
        foreach (const QJsonValue & v, jsonArray) {
             stationName = v.toObject().value("Name").toString();
             stationNumber = v.toObject().value("StationID").toString().toInt();
             enableSettings = v.toObject().value("enableSettings").toString();
             list.append(stationName);
             stations_.append(Station(stationNumber,stationName,std::bitset<6>(enableSettings.toStdString())));
        }
        stations(list);
        onStationChanged(0);
    }
    else {
        login_->LogOut();
         timer->stop();
    }
}

void Interact::handleUpdateStationResult(HttpRequestWorker *worker)
{
    if(worker->error_type == QNetworkReply::NoError) {
        RetrieveStations();
        emit updateSucceed();
    }
    else {
        emit updateFailed(worker->error_str);
    }
}

void Interact::handleRemoveCurrentStationResult(HttpRequestWorker *worker)
{
    if(worker->error_type == QNetworkReply::NoError) {
        RetrieveStations();
        emit removeSucceed();
    }
    else {
        emit removeFailed(worker->error_str);
    }
}

void Interact::handleAddStationResult(HttpRequestWorker *worker)
{
    if(worker->error_type == QNetworkReply::NoError) {
        RetrieveStations();
        emit addSucceed();
    }
    else {
        emit addFailed(worker->error_str);
    }
}

void Interact::updateDailyJSON()
{
    if(currentStation->name == "")
        return;
    HttpRequestWorker *worker = new HttpRequestWorker(this);
    QString url = "http://"+SettingsManager::getSetting("Server","ip").toString()+":"+
            SettingsManager::getSetting("Server","port").toString()+"/GetDaily";
    HttpRequestInput input(url,"GET");
    input.add_var("station",QString::number(currentStation->id));
    input.add_var("date1",Calendar::Last24Hour().first.toString("yyyy-MM-dd"));
    connect(worker,&HttpRequestWorker::on_execution_finished,this,&Interact::updateMeasurements);
    worker->execute(&input);
}

void Interact::onStationChanged(int /*index*/)
{
    QObject* scombobox = engine_.rootObjects().first()->findChild<QObject*>("stationBoxObject");
    if(scombobox==nullptr)
        return;
    auto currentText = scombobox->property("currentText").toString();
    auto it = std::find_if(stations_.begin(),stations_.end(),[=](auto val){if(val.name==currentText) return true; else return false;});
    if(it!= stations_.end()){
        *currentStation = *it;
    }
    updateDailyJSON();
}
void Interact::updateMeasurements(HttpRequestWorker *worker) {
    for(auto measurement : measurementList_) {
        measurement->LoadFromJSON(worker->response);
    }
}
