#include "sensor.h"
#include "station.h"
Sensor::Sensor(QString name, QObject *parent) : QObject(parent),a_name(name)
{
    enabled(false);
}

Sensor::Sensor(const Sensor &a):QObject(a.parent())
{
     a_currentVal= a.a_currentVal;
     a_currentValExists = a.a_currentValExists;
     a_unit = a.unit();
     a_readings = a.readings();
     a_readingsDates = a.readingsDates();
     a_name = a.a_name;
     a_enabled=a.a_enabled;

}

Sensor &Sensor::operator =(const Sensor &a)
{
    currentVal(a.currentVal());
    currentValExists(a.currentValExists());
    unit(unit());
    readings(a.readings());
    readingsDates(a.readingsDates());
    name(a.name());
    enabled(a.enabled());
    return *this;
}
