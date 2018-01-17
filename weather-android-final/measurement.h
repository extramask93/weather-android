#ifndef MEASUREMENT_H
#define MEASUREMENT_H

#include <QObject>
#include <QDateTime>
#include "propertyhelper.h"
typedef std::pair<QDateTime,double> Reading;
enum class ReadingType {temperature, humidity, co2, lux, soil, battery};

class Measurement:public QObject
{
    Q_OBJECT
    AUTO_PROPERTY(double, currentValue)
    AUTO_PROPERTY(QString, unit)
public:
    explicit Measurement(QObject *parent,ReadingType readingType, QString jsonString="");

public:
    QList<std::pair<QDateTime,double>> LoadFromJSON(QString jsonString);
    Reading GetLatestReading();
    QList<Reading> GetReadingsByDate(QDateTime from, QDateTime to);
    static ReadingType StringToReading(QString reading);
    static QString readingUnit(ReadingType reading);
protected:
    QString readingToString(ReadingType reading);
    ReadingType type_;
    QString jsonString_;
    QDateTime date;
    QList<Reading> result;
signals:

public slots:
};

#endif // MEASUREMENT_H
