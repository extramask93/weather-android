#include "measurement.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <algorithm>
#include <QDebug>

QList<Reading> Measurement::LoadFromJSON(QString jsonString)
{
        QString measurementName = readingToString(type_);
        QJsonParseError error;
        QJsonDocument document = QJsonDocument::fromJson(jsonString.toLocal8Bit(),&error);
        QJsonObject jsonObject = document.object();
        QJsonArray jsonArray = jsonObject["measurements"].toArray();
        QStringList list;
        result.clear();
        foreach (const QJsonValue & v, jsonArray) {
             QString date = v.toObject().value("measurementDate").toString();
             QString measurement = v.toObject().value(measurementName).toString();
             result.append(std::make_pair(QDateTime::fromString(date,"yyyy-MM-dd hh:mm:ss"),measurement.toDouble()));
        }
        if(result.empty())
            return QList<Reading>{};
        auto rd = GetLatestReading();
        currentValue(rd.second);
        return result;
}

Measurement::Measurement(QObject *parent, ReadingType readingType, QString jsonString): QObject{parent},type_{readingType}, jsonString_{jsonString}
{
    currentValue(-300);
    unit(readingUnit(readingType));
    result = QList<Reading>{};
    if(jsonString_!="")
        LoadFromJSON(jsonString);
}

Reading Measurement::GetLatestReading()
{
    auto comp = [](const Reading &a, const Reading &b) {return a.first < b.first;};
    auto latest = std::min_element(result.begin(),result.end(),comp);
    return *latest;
}

QList<Reading> Measurement::GetReadingsByDate(QDateTime from, QDateTime to)
{
    QList<Reading> range;
    auto pred = [&](const Reading &reading) {
        if((reading.first >= from) && (reading.first<to)){
            return true;
        }
        else
            return false;
        };
    std::copy_if(result.begin(),result.end(),range.begin(),pred);
    return range;
}

QString Measurement::readingToString(ReadingType reading)
{
    //qDebug()<<"reading to string"<<(int)reading;
    switch (reading) {
    case ReadingType::temperature:
        return "temperature";
    case ReadingType::humidity:
        return "humidity";
    case ReadingType::co2:
        return "co2";
    case ReadingType::lux:
        return "lux";
    case ReadingType::soil:
        return "soil";
    case ReadingType::battery:
        return "battery";
    default:
        return "";
    }
}
QString Measurement::readingUnit(ReadingType reading)
{
    //qDebug()<<"reading to string"<<(int)reading;
    switch (reading) {
    case ReadingType::temperature:
        return "°C";
    case ReadingType::humidity:
        return "%";
    case ReadingType::co2:
        return "ppm";
    case ReadingType::lux:
        return "lux";
    case ReadingType::soil:
        return "%";
    case ReadingType::battery:
        return "%";
    default:
        return "";
    }
}
