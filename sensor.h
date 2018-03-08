#ifndef SENSOR_H
#define SENSOR_H
#include <QString>
#include <QStringList>
class Station;
class Sensor
{
public:
    double currentVal;
    bool currentValExists;
    QString name;
    QString unit;
    bool enabled;
    QStringList readingsDates;
    QList<double> readings;
public:
    explicit Sensor(QString name="");
    bool operator ==(const Sensor&a) {return this->name == a.name;}
private:
};
#endif // SENSOR_H
