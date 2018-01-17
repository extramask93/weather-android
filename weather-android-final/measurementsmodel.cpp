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
    axes.at(1)->setTitleText(readingtype + '['+Measurement::readingUnit(Measurement::StringToReading(type_))+']');
    QDateTimeAxis *dt = static_cast<QDateTimeAxis*>(axes.at(0));
    dt->setFormat("yy-MM-dd");
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
    axes.at(1)->setTitleText(readingtype + '['+Measurement::readingUnit(Measurement::StringToReading(type_))+']');
    QDateTimeAxis *dt = static_cast<QDateTimeAxis*>(axes.at(0));
    dt->setFormat("yy-MM-dd");
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
    axes.at(1)->setTitleText(readingtype + '['+Measurement::readingUnit(Measurement::StringToReading(type_))+']');
    QDateTimeAxis *dt = static_cast<QDateTimeAxis*>(axes.at(0));
    dt->setFormat("yy-MM-dd");
}

void MeasurementsModel::getMonthlyData(int station, QString readingtype)
{
    type_=readingtype;
    QString url = "http://localhost:5000/GetDaily";
    QChartView view;
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
    lineseries->clear();
    axes.at(1)->setTitleText(readingtype + '['+Measurement::readingUnit(Measurement::StringToReading(type_))+']');
    QDateTimeAxis *dt = static_cast<QDateTimeAxis*>(axes.at(0));
    //dt->setFormat("yy-MM-dd");
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
    axes.at(1)->setTitleText(readingtype + '['+Measurement::readingUnit(Measurement::StringToReading(type_))+']');
    QDateTimeAxis *dt = static_cast<QDateTimeAxis*>(axes.at(0));
    dt->setFormat("yy-MM-dd");
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
        /*find smallest and biggest date*/
        auto comp = [](const QPointF &a, const QPointF &b) {return a.x() < b.x();};
        auto min = std::min_element(data_.begin(),data_.end(),comp);
        auto max = std::max_element(data_.begin(),data_.end(),comp);
        QLineSeries *lineseries = static_cast<QLineSeries *>(series_);
        auto axes = lineseries->attachedAxes();
            axes.at(0)->setMin(QDateTime::fromMSecsSinceEpoch(min->x()).addDays(-1));
            axes.at(0)->setMax(QDateTime::fromMSecsSinceEpoch(max->x()).addDays(1));
        /*find smallest and biggest measurement*/
        auto compy = [](const QPointF &a, const QPointF &b) {return a.y() < b.y();};
        auto miny = std::min_element(data_.begin(),data_.end(),compy);
        auto maxy = std::max_element(data_.begin(),data_.end(),compy);
        if(miny->y()<0)
            axes.at(1)->setMin(miny->y()-20);
        else
            axes.at(1)->setMin(0);
        axes.at(1)->setMax(maxy->y()+20);
        lineseries->replace(data_);

    }
}

