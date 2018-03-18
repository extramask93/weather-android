#ifndef MEASUREMENTSMODEL_H
#define MEASUREMENTSMODEL_H

#include <QObject>
#include <QtCharts>
#include <QStringList>
#include <QList>
#include <QString>
#include "httprequestworker.h"
#include "measurement.h"
#include <QQmlApplicationEngine>
#include "propertyhelper.h"
#include "calendar.h"
class QQuickView;
class MeasurementsModel : public QObject
{
    Q_OBJECT
    AUTO_PROPERTY(QStringList, dates)
    AUTO_PROPERTY(QList<qreal>, values)
    AUTO_PROPERTY(QString, unit)
    AUTO_PROPERTY(QString, cType)
public:
    explicit MeasurementsModel(QObject *parent, QAbstractSeries *series, QQmlApplicationEngine &engine);
protected:
    void getDataHelper(DateRange period, QString per);
    QVector<QPointF> data_;
    QQuickView *appView_;
    QAbstractSeries *series_;
    QString type_;
    int station_;
    QString formatString_;
    QQmlApplicationEngine &engine_;
Q_SIGNALS:

public slots:
    void getTodayData(int station, QString readingtype);
    void getLast3DaysData(int station, QString readingtype);
    void getWeeklyData(int station,QString readingtype);
    void getMonthlyData(int station, QString readingtype);
    void getYearlyData(int station, QString readingtype);
    void handleTodayData(HttpRequestWorker*);
};

#endif // MEASUREMENTSMODEL_H
