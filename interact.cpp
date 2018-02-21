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
Interact::Interact(QObject *parent, QQmlApplicationEngine &engine):QObject{parent},engine_{engine}, worker_{new HttpRequestWorker(nullptr)}
{
    currentStation = std::make_pair("",0);
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
    timer = new QTimer{this};

}

void Interact::Run()
{
    rootObject_ = engine_.rootObjects()[0];
    QObject* home = engine_.rootObjects().first()->findChild<QObject*>("loginObject");
    QObject *logout = engine_.rootObjects().first()->findChild<QObject*>("sidePanelObject");
    if(home !=nullptr)
    connect(home, SIGNAL(loginSignal(QString, QString)), this, SLOT(onLoginSignal(QString,QString)));
    connect(logout, SIGNAL(logOutSignal()),this,SLOT(onLogOutSignal()));

}

void Interact::onMainViewLoaded()
{
    QObject *mainView = engine_.rootObjects().first()->findChild<QObject*>("mainViewObject");
    connect(mainView,SIGNAL(loaded()),this,SLOT(RetrieveStations()));
    connect(timer,&QTimer::timeout,this,&Interact::updateDailyJSON);
    RetrieveStations();
    timer->start(3600);
}

void Interact::RetrieveStations()
{
    qDebug() << "Retrieving stations";
    QString url = QString("http://")+"localhost"+":"+"5000"+"/GetStations";
    HttpRequestInput input(url,"GET");
    HttpRequestWorker *worker = new HttpRequestWorker(this);
    connect(worker,&HttpRequestWorker::on_execution_finished,this,&Interact::handleRetrieveStationsResult);
    worker->execute(&input);
}

void Interact::onUpdateChartSignal(QString type)
{
    static QString lasttype;
    if(type=="")
        type=lasttype;
    lasttype=type;
    QObject *chart = engine_.rootObjects().first()->findChild<QObject*>("mychartObject")->findChild<QObject*>("chartObject");
    QObject *pbox = engine_.rootObjects().first()->findChild<QObject*>("mychartObject")->findChild<QObject*>("periodBoxObject");
    int index = pbox->property("currentIndex").toInt();
    chart->setProperty("title",type);
    QAbstractSeries * series;
    QMetaObject::invokeMethod(chart,"series",Qt::AutoConnection,Q_RETURN_ARG(QAbstractSeries*,series),Q_ARG(int,0));
    QScatterSeries *ln = static_cast<QScatterSeries*>(series);
    auto axes = ln->attachedAxes();
         model = new MeasurementsModel{this,series};
    switch(index) {
    case 0:
        model->getTodayData(currentStation.second,type);
        break;
    case 1:
        model->getLast3DaysData(currentStation.second,type);
        break;
    case 2:
        model->getWeeklyData(currentStation.second,type);
        break;
    case 3:
        model->getMonthlyData(currentStation.second,type);
        break;
    case 4:
        model->getYearlyData(currentStation.second,type);
        break;
    default:
        break;
    }
}

void Interact::onLoginSignal(QString username, QString password)
{
    QString url = "http://"+QString("localhost")+":"+"5000"+"/LogIn";
    HttpRequestInput input(url,"POST");
    input.add_var("email",username);
    input.add_var("password",password);
    HttpRequestWorker *worker = new HttpRequestWorker(this);
    connect(worker,SIGNAL(on_execution_finished(HttpRequestWorker*)),this,SLOT(handleResult(HttpRequestWorker*)));
    worker->execute(&input);
}

void Interact::onLogOutSignal()
{
    timer->stop();
    QString url = "http://"+QString("localhost")+":"+QString("5000")+"/LogOut";
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
    qDebug()<<"There is response";
    if(worker->error_type == QNetworkReply::NoError) {
        QJsonParseError error;
        QJsonDocument document = QJsonDocument::fromJson(worker->response,&error);
        QJsonObject jsonObject = document.object();
        QJsonArray jsonArray = jsonObject["stations"].toArray();
        QString stationName;
        uint16_t stationNumber;
        QStringList list;
        stationsAndIndexes.clear();
        list.clear();
        foreach (const QJsonValue & v, jsonArray) {
             stationName = v.toObject().value("Name").toString();
             stationNumber = v.toObject().value("StationID").toString().toInt();
             list.append(stationName);
             stationsAndIndexes.append(std::make_pair(stationName,stationNumber));
        }
        stations(list);
        onStationChanged(0);
    }
    else {
        qDebug()<<worker->response;
        qDebug()<<"error in stations";
    }
}

void Interact::updateDailyJSON()
{
    if(currentStation.first == "")
        return;
    worker_->disconnect();
    QString url = "http://"+QString("localhost")+":"+"5000"+"/GetDaily";
    HttpRequestInput input(url,"GET");
    input.add_var("station",QString::number(currentStation.second));
    input.add_var("date1",Calendar::Last24Hour().first.toString("yyyy-MM-dd"));
    connect(worker_,&HttpRequestWorker::on_execution_finished,this,&Interact::updateMeasurements);
    worker_->execute(&input);
}

void Interact::onStationChanged(int index)
{
    QObject* scombobox = engine_.rootObjects().first()->findChild<QObject*>("stationBoxObject");
    if(scombobox==nullptr)
        return;
    auto currentText = scombobox->property("currentText").toString();
    auto it = std::find_if(stationsAndIndexes.begin(),stationsAndIndexes.end(),[=](auto val){if(val.first==currentText) return true; else return false;});
    if(it!= stationsAndIndexes.end()){
        currentStation = *it;
    }
    qDebug()<<"current text"<<currentStation.first<<currentStation.second;
    updateDailyJSON();
}
void Interact::updateMeasurements(HttpRequestWorker *worker) {
    for(auto measurement : measurementList_) {
        measurement->LoadFromJSON(worker->response);
    }
}
