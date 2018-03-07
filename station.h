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
Q_DECLARE_METATYPE(Station)

class Station : public QObject
{
    Q_OBJECT
    AUTO_PROPERTY(quint8, id)
    AUTO_PROPERTY(QString, name)
    AUTO_PROPERTY(QTime, reftime)
    AUTO_PROPERTY(Sensor*, tempSensor)
    AUTO_PROPERTY(Sensor*, humiditySensor)
    AUTO_PROPERTY(Sensor*, co2Sensor)
    AUTO_PROPERTY(Sensor*, soilSensor)
    AUTO_PROPERTY(Sensor*, luxSensor)
    AUTO_PROPERTY(Sensor*, batterySensor)
public:
    Station(quint8 id,QString name = "", std::bitset<6> enableSettins = 0x111111,QObject *parent = nullptr);
    ~Station();
    void setFromBool(bool temp,bool humidity,bool lux, bool soil, bool battery, bool co2);
    Station(const Station& second): QObject(second.parent()){
        a_id = second.id();
        a_name = second.name();
        a_tempSensor = new Sensor();
        *a_tempSensor = *second.a_tempSensor;
        a_humiditySensor = new Sensor();
        *a_humiditySensor = *second.a_humiditySensor;
        a_luxSensor = new Sensor();
        *a_luxSensor = *second.a_luxSensor;
        a_soilSensor = new Sensor();
        *a_soilSensor = *second.a_soilSensor;
        a_batterySensor = new Sensor();
        *a_batterySensor = *second.a_batterySensor;
        a_co2Sensor = new Sensor();
        *a_co2Sensor = *second.a_co2Sensor;
        a_reftime = second.reftime();
    }
    bool operator ==(const Station &s) {if(this->id()==s.id() && this->name()==s.name()) return true; return false;}
    Station& operator =(const Station &s) {
        id(s.id());
        name(s.name());
        reftime(s.reftime());
        tempSensor(s.a_tempSensor);
        humiditySensor(s.a_humiditySensor);
        luxSensor(s.a_luxSensor);
        soilSensor(s.a_soilSensor);
        batterySensor(s.a_batterySensor);
        co2Sensor(s.a_co2Sensor);
        return *this;
    }
    Station();
    Q_INVOKABLE void save();
    Q_INVOKABLE void init();

signals:

public slots:
private:
};


#endif // STATION_H
