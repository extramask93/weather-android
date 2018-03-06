#include "station.h"


Station::Station(quint8 id, QString name, std::bitset<6> enableSettins, QObject *parent): QObject{parent}, a_id(id), a_name(name)
{
    a_tempSensor = new Sensor("temperature");
    a_tempSensor->enabled(enableSettins[0]);
    a_batterySensor = new Sensor("bat");
    a_batterySensor->enabled(enableSettins[4]);
    a_humiditySensor = new Sensor("humidity");
    a_humiditySensor->enabled(enableSettins[1]);
    a_co2Sensor = new Sensor("co2");
    a_co2Sensor->enabled(enableSettins[5]);
    a_luxSensor = new Sensor("lux");
    a_luxSensor->enabled(enableSettins[2]);
    a_soilSensor = new Sensor("soil");
    a_soilSensor->enabled(enableSettins[3]);
    a_reftime = QTime(1,3,4);
}

Station::~Station()
{
    delete a_batterySensor;
    delete a_co2Sensor;
    delete a_humiditySensor;
    delete a_luxSensor;
    delete a_soilSensor;
    delete a_tempSensor;
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
