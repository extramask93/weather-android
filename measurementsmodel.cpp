#include "measurementsmodel.h"
#include <QtCharts/QXYSeries>
#include <QtCharts/QAreaSeries>
#include <QtQuick/QQuickView>
#include <QtQuick/QQuickItem>
#include <QDateTime>
#include "settingsmanager.h"
QT_CHARTS_USE_NAMESPACE
Q_DECLARE_METATYPE(QAbstractSeries *)
Q_DECLARE_METATYPE(QAbstractAxis *)

MeasurementsModel::MeasurementsModel(QObject *parent,QAbstractSeries *series, QQmlApplicationEngine &engine) : engine_{engine},QObject(parent),
    series_{series}
{
    dates(QStringList{});
    values(QList<qreal>{});
    qRegisterMetaType<QAbstractSeries *>();
    qRegisterMetaType<QAbstractAxis *>();
}
void MeasurementsModel::getDataHelper(DateRange period, QString per) {
    QString url = "http://"+SettingsManager::getSetting("Server","ip").toString()+":"
            +SettingsManager::getSetting("Server","port").toString()+"/GetPeriodical";
    HttpRequestWorker *worker = new HttpRequestWorker(this);
    HttpRequestInput input(url,"GET");
    /*input.add_var("date1",period.first.toString("yyyy-MM-dd"));
    input.add_var("date2",period.second.toString("yyyy-MM-dd"));
    input.add_var("station",QString::number(station_));*/
    input.add_var("type",type_);
    input.add_var("station", QString::number(station_));
    input.add_var("period",per);
    input.add_var("interval","50");
    connect(worker,SIGNAL(on_execution_finished(HttpRequestWorker*)),this, SLOT(handleTodayData(HttpRequestWorker*)));
    worker->execute(&input);
}
void MeasurementsModel::getTodayData(int station, QString readingtype)
{
    type_=readingtype;
    station_=station;
    auto period = Calendar::Last24Hour();
    getDataHelper(period,"day");
    formatString_ = "hh:mm";

}

void MeasurementsModel::getLast3DaysData(int station, QString readingtype)
{
    type_=readingtype;
    station_=station;
    auto period = Calendar::Last3Days();
    getDataHelper(period,"3days");
    formatString_ = "dd-MM";
}

void MeasurementsModel::getWeeklyData(int station, QString readingtype)
{
    type_=readingtype;
    station_=station;
    auto period = Calendar::LastWeek();
    getDataHelper(period,"week");
    formatString_ = "dd-MM";
}

void MeasurementsModel::getMonthlyData(int station, QString readingtype)
{
    type_=readingtype;
    station_=station;
    auto period = Calendar::LastMonth();
    getDataHelper(period,"month");
    formatString_ = "dd-MM";
}

void MeasurementsModel::getYearlyData(int station, QString readingtype)
{
    type_=readingtype;
    station_=station;
    auto period = Calendar::LastYear();
    getDataHelper(period,"year");
    formatString_ = "dd-MM-yy";
}

void MeasurementsModel::handleTodayData(HttpRequestWorker *worker)
{
    if(worker->error_type == QNetworkReply::NoError) {
        QJsonParseError error;
        QString response = worker->response;
        QJsonDocument document = QJsonDocument::fromJson(worker->response,&error);
        QJsonObject jsonObject = document.object();
        QJsonArray jsonArray = jsonObject["measurements"].toArray();
        data_.clear();
        a_dates.clear();
        a_values.clear();
        QStringList tempd;
        QList<qreal> tempv;
        foreach (const QJsonValue & v, jsonArray) {
             auto date = v.toObject().value("time").toString();
             auto value = v.toObject().value(type_).toString();
             tempd.append(QDateTime::fromString(date,"yyyy-MM-dd hh:mm:ss").toString(formatString_));
             tempv.append(value.toFloat());
             data_.append(QPointF(QDateTime::fromString(date,"yyyy-MM-dd hh:mm:ss").toMSecsSinceEpoch(),value.toDouble()));
        }
        dates(tempd);
        values(tempv);
        unit(Measurement::readingUnit(Measurement::StringToReading(type_)));
        auto tmp = type_;
        tmp[0] = tmp[0].toUpper();
        cType(tmp);
        QObject *chart = engine_.rootObjects().first()->findChild<QObject*>("mychartObject");
        QMetaObject::invokeMethod(chart,"updater");
    }
    worker->deleteLater();
}

