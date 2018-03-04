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
    Station(const Station& second): QObject(second.parent()){
        a_id = second.id();
        a_name = second.name();
        this->a_tempSensor = second.a_tempSensor;
        this->a_humiditySensor = second.a_humiditySensor;
        this->a_luxSensor = second.a_luxSensor;
        this->a_soilSensor = second.a_soilSensor;
        this->a_batterySensor = second.a_batterySensor;
        this->a_co2Sensor = second.a_co2Sensor;
        a_reftime = second.reftime();
    }
    bool operator ==(const Station &s) {if(this->id()==s.id() && this->name()==s.name()) return true; return false;}
    Station& operator =(const Station &s) {
        this->a_id = s.id();
        this->a_name = s.name();
        this->a_tempSensor = s.a_tempSensor;
        this->a_humiditySensor = s.a_humiditySensor;
        this->a_luxSensor = s.a_luxSensor;
        this->a_soilSensor = s.a_soilSensor;
        this->a_batterySensor = s.a_batterySensor;
        this->a_co2Sensor = s.a_co2Sensor;
        this->a_reftime = s.reftime();
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
