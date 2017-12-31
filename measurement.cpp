#include "measurement.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <algorithm>

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
             double measurement = v.toObject().value(measurementName).toDouble();
             result.append(std::make_pair(QDateTime::fromString(date,"yyyy-MM-dd hh:mm:ss"),measurement));
        }
        return result;
}

Measurement::Measurement(ReadingType readingType, QString jsonString): type_{readingType}, jsonString_{jsonString}
{
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
    default:
        return "";
    }
}
