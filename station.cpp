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
    delete a_batterySensor; a_batterySensor = nullptr;
    delete a_co2Sensor; a_co2Sensor = nullptr;
    delete a_humiditySensor; a_humiditySensor = nullptr;
    delete a_luxSensor;  a_luxSensor = nullptr;
    delete a_soilSensor; a_soilSensor = nullptr;
    delete a_tempSensor; a_tempSensor = nullptr;
}

void Station::setFromBool(bool temp, bool humidity, bool lux, bool soil, bool battery, bool co2)
{
    tempSensor()->enabled(temp);
    humiditySensor()->enabled(humidity);
    soilSensor()->enabled(soil);
    batterySensor()->enabled(battery);
    luxSensor()->enabled(lux);
    co2Sensor()->enabled(co2);
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
