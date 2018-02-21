#ifndef MEASUREMENTSMODEL_H
#define MEASUREMENTSMODEL_H

#include <QObject>
#include <QtCharts>
#include "httprequestworker.h"
#include "measurement.h"
#include "calendar.h"
class QQuickView;
class MeasurementsModel : public QObject
{
    Q_OBJECT
public:
    explicit MeasurementsModel(QObject *parent, QAbstractSeries *series);
protected:
    void getDataHelper(DateRange period);
    QVector<QPointF> data_;
    QQuickView *appView_;
    QAbstractSeries *series_;
    QString type_;
    int station_;
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
