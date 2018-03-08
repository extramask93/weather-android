#ifndef STATION_H
#define STATION_H

#include <QObject>
#include <QAbstractItemModel>
#include <QTime>
#include <QAbstractListModel>
#include <QQmlListProperty>
#include <bitset>
#include "propertyhelper.h"
#include "sensor.h"

class Station
{
public:
    quint8 id;
    QString name;
    QTime reftime;
    Sensor tempSensor;
    Sensor humiditySensor;
    Sensor co2Sensor;
    Sensor soilSensor;
    Sensor luxSensor;
    Sensor batterySensor;
public:
    Station(quint8 id,QString name = "", std::bitset<6> enableSettins = 0x111111);
    ~Station();
    void setFromBool(bool temp,bool humidity,bool lux, bool soil, bool battery, bool co2);
    bool operator ==(const Station &s) {if(this->id==s.id && this->name==s.name) return true; return false;}
    Station();
    void save();
    void init();

signals:

public slots:
private:
};


#endif // STATION_H
