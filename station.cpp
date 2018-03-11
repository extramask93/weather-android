#include "station.h"


Station::Station(quint8 id, QString name, std::bitset<6> enableSettins): id(id), name(name)
{
    tempSensor = Sensor("temperature");
    tempSensor.enabled = enableSettins[5];
    batterySensor = Sensor("bat");
    batterySensor.enabled=enableSettins[1];
    humiditySensor = Sensor("humidity");
    humiditySensor.enabled=enableSettins[4];
    co2Sensor = Sensor("co2");
    co2Sensor.enabled=enableSettins[0];
    luxSensor = Sensor("lux");
    luxSensor.enabled=enableSettins[3];
    soilSensor = Sensor("soil");
    soilSensor.enabled =enableSettins[2];
    reftime = QTime(0,0,0);
}

Station::~Station()
{
}

void Station::setFromBool(bool temp, bool humidity, bool lux, bool soil, bool battery, bool co2)
{
    tempSensor.enabled=temp;
    humiditySensor.enabled=humidity;
    soilSensor.enabled=soil;
    batterySensor.enabled=battery;
    luxSensor.enabled=lux;
    co2Sensor.enabled=co2;
}

QList<bool> Station::getBool()
{
    return QList<bool>{tempSensor.enabled,humiditySensor.enabled,luxSensor.enabled,soilSensor.enabled, batterySensor.enabled,
                        co2Sensor.enabled};
}

Station::Station()
{
}

void Station::save()
{

}

void Station::init()
{

}

/****************************************************************/
