#ifndef SENSOR_H
#define SENSOR_H

#include <QObject>
#include "propertyhelper.h"

class Station;
class Sensor : public QObject
{
    Q_OBJECT
    AUTO_PROPERTY(double,currentVal)
    AUTO_PROPERTY(bool,currentValExists)
    AUTO_PROPERTY(QString, name)
    AUTO_PROPERTY(QString, unit)
    AUTO_PROPERTY(bool, enabled)
    AUTO_PROPERTY(QStringList, readingsDates)
    AUTO_PROPERTY(QList<double>, readings)
public:
    explicit Sensor(QString name="", QObject *parent = nullptr);
    Sensor(const Sensor& a);
    bool operator ==(const Sensor&a) {return this->a_name == a.a_name;}
    Sensor& operator =(const Sensor& a);
signals:

public slots:
private:
};
Q_DECLARE_METATYPE(Sensor)
#endif // SENSOR_H
