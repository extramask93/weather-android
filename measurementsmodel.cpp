#include "measurementsmodel.h"
#include <QtCharts/QXYSeries>
#include <QtCharts/QAreaSeries>
#include <QtQuick/QQuickView>
#include <QtQuick/QQuickItem>
#include <QDateTime>
#include "calendar.h"
QT_CHARTS_USE_NAMESPACE
Q_DECLARE_METATYPE(QAbstractSeries *)
Q_DECLARE_METATYPE(QAbstractAxis *)

MeasurementsModel::MeasurementsModel(QObject *parent,QAbstractSeries *series) : QObject(parent), series_{series}
{
    qRegisterMetaType<QAbstractSeries *>();
    qRegisterMetaType<QAbstractAxis *>();
}

void MeasurementsModel::getTodayData(int station, QString readingtype)
{
    type_=readingtype;
    QString url = "http://localhost:5000/GetDaily";
    HttpRequestWorker *worker = new HttpRequestWorker(this);
    HttpRequestInput input(url,"GET");
    auto period = Calendar::GetTodayDate().addDays(-1);
    input.add_var("date1",period.toString("yyyy-MM-dd"));
    input.add_var("station",QString::number(station));
    connect(worker,SIGNAL(on_execution_finished(HttpRequestWorker*)),this, SLOT(handleTodayData(HttpRequestWorker*)));
    worker->execute(&input);
    QLineSeries *lineseries = static_cast<QLineSeries *>(series_);
    auto axes = lineseries->attachedAxes();
    axes.at(0)->setMin(Calendar::GetTodayDate().addDays(-1));
    axes.at(0)->setMax(Calendar::GetTodayDate());
}

void MeasurementsModel::getLast3DaysData(int station, QString readingtype)
{
    type_=readingtype;
    QString url = "http://localhost:5000/GetDaily";
    HttpRequestWorker *worker = new HttpRequestWorker(this);
    HttpRequestInput input(url,"GET");
    auto period = Calendar::Last3Days();
    input.add_var("date1",period.first.toString("yyyy-MM-dd"));
    input.add_var("date2", period.second.toString("yyyy-MM-dd"));
    input.add_var("station",QString::number(station));
    connect(worker,SIGNAL(on_execution_finished(HttpRequestWorker*)),this, SLOT(handleTodayData(HttpRequestWorker*)));
    worker->execute(&input);
    QLineSeries *lineseries = static_cast<QLineSeries *>(series_);
    auto axes = lineseries->attachedAxes();
    axes.at(0)->setMin(Calendar::GetTodayDate().addDays(-3));
    axes.at(0)->setMax(Calendar::GetTodayDate());
}

void MeasurementsModel::getWeeklyData(int station, QString readingtype)
{
    type_=readingtype;
    QString url = "http://localhost:5000/GetDaily";
    HttpRequestWorker *worker = new HttpRequestWorker(this);
    HttpRequestInput input(url,"GET");
    auto period = Calendar::LastWeek();
    input.add_var("date1",period.first.toString("yyyy-MM-dd"));
    input.add_var("date2", period.second.toString("yyyy-MM-dd"));
    input.add_var("station",QString::number(station));
    connect(worker,SIGNAL(on_execution_finished(HttpRequestWorker*)),this, SLOT(handleTodayData(HttpRequestWorker*)));
    worker->execute(&input);
    QLineSeries *lineseries = static_cast<QLineSeries *>(series_);
    auto axes = lineseries->attachedAxes();
    axes.at(0)->setMin(Calendar::GetTodayDate().addDays(-7));
    axes.at(0)->setMax(Calendar::GetTodayDate());
}

void MeasurementsModel::getMonthlyData(int station, QString readingtype)
{
        type_=readingtype;
    QString url = "http://localhost:5000/GetDaily";
    HttpRequestWorker *worker = new HttpRequestWorker(this);
    HttpRequestInput input(url,"GET");
    auto period = Calendar::LastMonth();
    input.add_var("date1",period.first.toString("yyyy-MM-dd"));
    input.add_var("date2", period.second.toString("yyyy-MM-dd"));
    input.add_var("station",QString::number(station));
    connect(worker,SIGNAL(on_execution_finished(HttpRequestWorker*)),this, SLOT(handleTodayData(HttpRequestWorker*)));
    worker->execute(&input);
    QLineSeries *lineseries = static_cast<QLineSeries *>(series_);
    auto axes = lineseries->attachedAxes();
    axes.at(0)->setMin(Calendar::GetTodayDate().addMonths(-1));
    axes.at(0)->setMax(Calendar::GetTodayDate());
}

void MeasurementsModel::getYearlyData(int station, QString readingtype)
{
        type_=readingtype;
    QString url = "http://localhost:5000/GetDaily";
    HttpRequestWorker *worker = new HttpRequestWorker(this);
    HttpRequestInput input(url,"GET");
    auto period = Calendar::LastYear();
    input.add_var("date1",period.first.toString("yyyy-MM-dd"));
    input.add_var("date2", period.second.toString("yyyy-MM-dd"));
    input.add_var("station",QString::number(station));
    connect(worker,SIGNAL(on_execution_finished(HttpRequestWorker*)),this, SLOT(handleTodayData(HttpRequestWorker*)));
    worker->execute(&input);
    QLineSeries *lineseries = static_cast<QLineSeries *>(series_);
    auto axes = lineseries->attachedAxes();
    axes.at(0)->setMin(Calendar::GetTodayDate().addYears(-1));
    axes.at(0)->setMax(Calendar::GetTodayDate());
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
        foreach (const QJsonValue & v, jsonArray) {
             auto date = v.toObject().value("measurementDate").toString();
             auto value = v.toObject().value(type_).toString();
             data_.append(QPointF(QDateTime::fromString(date,"yyyy-MM-dd hh:mm:ss").toMSecsSinceEpoch(),value.toDouble()));
             qDebug() << date<<value;
        }
        QLineSeries *lineseries = static_cast<QLineSeries *>(series_);
        lineseries->replace(data_);
    }
}

