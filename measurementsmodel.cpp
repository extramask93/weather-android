#include "measurementsmodel.h"
#include <QtCharts/QXYSeries>
#include <QtCharts/QAreaSeries>
#include <QtQuick/QQuickView>
#include <QtQuick/QQuickItem>
#include <QDateTime>
QT_CHARTS_USE_NAMESPACE
Q_DECLARE_METATYPE(QAbstractSeries *)
Q_DECLARE_METATYPE(QAbstractAxis *)

MeasurementsModel::MeasurementsModel(QObject *parent) : QObject(parent)
{
    qRegisterMetaType<QAbstractSeries *>();
    qRegisterMetaType<QAbstractAxis *>();
}

void MeasurementsModel::getTodayData(QAbstractSeries *series)
{
    QString url = "http://localhost:5000/GetDaily";
    HttpRequestWorker *worker = new HttpRequestWorker(this);
    HttpRequestInput input(url,"POST");
    QDateTime now = QDateTime::currentDateTime();
    QString requestedDate = now.toString("yyyy-MM-dd");
    QString requestedDateEnd  = now.addDays(1).toString("yyyy-MM-dd");
    input.add_var("date1",requestedDate);
    input.add_var("date2", requestedDateEnd);
    input.add_var("station","1");
    connect(worker,SIGNAL(on_execution_finished(HttpRequestWorker*)),this, SLOT(handleTodayData(HttpRequestWorker*)));
    worker->execute(&input);
}

void MeasurementsModel::getWeekData(QAbstractSeries *series, QAbstractAxis *axis)
{
    if(axis) {
        qDebug()<<"date-time axis not null";
        QDateTimeAxis *daxis = static_cast<QDateTimeAxis*>(axis);
        daxis->setMin(QDateTime::currentDateTime());
        qDebug()<<daxis->min();
        daxis->setMax(QDateTime::currentDateTime().addDays(2));
        qDebug() << daxis->max();
    }
    if(series) {
        QXYSeries *xyseries = static_cast<QXYSeries *>(series);
        QDateTime time = QDateTime::currentDateTime();
        qDebug() <<time.toMSecsSinceEpoch();
        QVector<QPointF> points{QPointF(time.toMSecsSinceEpoch(),0.0),QPointF(time.addDays(1).toMSecsSinceEpoch(),1.0),QPointF(time.addDays(2).toMSecsSinceEpoch(),2.0),QPointF(time.addDays(3).toMSecsSinceEpoch(),3.0), QPointF(time.addDays(4).toMSecsSinceEpoch(),4.0)};
        xyseries->replace(points);
    }
}

void MeasurementsModel::handleTodayData(HttpRequestWorker *worker)
{
    if(worker->error_type == QNetworkReply::NoError) {
        QJsonParseError error;
        QString response = worker->response;
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
        //stations(list);
    }
}
