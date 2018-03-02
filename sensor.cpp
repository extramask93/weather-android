#include "sensor.h"
#include "station.h"
Sensor::Sensor(QString name, QObject *parent) : QObject(parent), owningStation_{dynamic_cast<Station*>(parent)}
{

}
