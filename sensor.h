#ifndef SENSOR_H
#define SENSOR_H

#include <QObject>
#include "propertyhelper.h"

class Station;
class Sensor : public QObject
{
    AUTO_PROPERTY(double,currentVal)
    AUTO_PROPERTY(bool,currentValExists)
    AUTO_PROPERTY(QString, name)
    AUTO_PROPERTY(QString, unit)
    AUTO_PROPERTY(bool, enabled)
    AUTO_PROPERTY(QStringList, readingsDates)
    AUTO_PROPERTY(QList<double>, readings)
    Q_OBJECT
public:
    explicit Sensor(QString name="", QObject *parent = nullptr);
    Sensor(const Sensor& a) {a_currentVal= a.a_currentVal;}
    bool operator ==(const Sensor&a) {return this->a_name == a.a_name;}
    Sensor& operator =(const Sensor& other) { this->name(other.name()); return *this;}
signals:

public slots:
private:
    Station *owningStation_;
};

#endif // SENSOR_H
