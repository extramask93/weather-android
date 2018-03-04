#include "sensor.h"
#include "station.h"
Sensor::Sensor(QString name, QObject *parent) : QObject(parent),a_name(name)
{
    enabled(false);
}
