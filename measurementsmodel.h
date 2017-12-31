#ifndef MEASUREMENTSMODEL_H
#define MEASUREMENTSMODEL_H

#include <QObject>
#include <QtCharts>
#include "httprequestworker.h"
class QQuickView;
class MeasurementsModel : public QObject
{
    Q_OBJECT
public:
    explicit MeasurementsModel(QObject *parent = nullptr);
protected:
    QList<QVector<QPointF>> data_;
    QQuickView *appView_;
Q_SIGNALS:

public slots:
    void getTodayData(QAbstractSeries *series);
    void getWeekData(QAbstractSeries *series,QAbstractAxis *axis);
    void handleTodayData(HttpRequestWorker*);
    //void getMonthData(QAbstractSeries *series);
    //void getYearData(QAbstractSeries *series);

};

#endif // MEASUREMENTSMODEL_H
