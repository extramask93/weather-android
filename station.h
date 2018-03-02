#ifndef STATION_H
#define STATION_H

#include <QObject>
#include <QAbstractItemModel>
#include <QTime>
#include "propertyhelper.h"
#include "sensor.h"

class Station : public QObject
{
    Q_OBJECT
    AUTO_PROPERTY(quint8, id)
    AUTO_PROPERTY(QString, name)
    AUTO_PROPERTY(QTime, reftime)
    AUTO_PROPERTY(Sensor, tempSensor)
    AUTO_PROPERTY(Sensor, humiditySensor)
    AUTO_PROPERTY(Sensor, co2Sensor)
    AUTO_PROPERTY(Sensor, soilSensor)
    AUTO_PROPERTY(Sensor, luxSensor)
    AUTO_PROPERTY(Sensor, batterySensor)
public:
    Station(quint8 id,QString name = "",QObject *parent = nullptr);
    Station();
    Q_INVOKABLE void save();
    Q_INVOKABLE void init();

signals:

public slots:
private:
};

#endif // STATION_H
