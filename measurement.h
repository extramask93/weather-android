#ifndef MEASUREMENT_H
#define MEASUREMENT_H

#include <QObject>
#include <QDateTime>

typedef std::pair<QDateTime,double> Reading;
enum class ReadingType {temperature, humidity, co2, lux, soil, battery};

class Measurement
{
    explicit Measurement(ReadingType readingType, QString jsonString="");
public:
    QList<std::pair<QDateTime,double>> LoadFromJSON(QString jsonString);
    Reading GetLatestReading();
    QList<Reading> GetReadingsByDate(QDateTime from, QDateTime to);
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
