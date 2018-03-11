#ifndef STATIONMANAGER_H
#define STATIONMANAGER_H

#include <QObject>
#include <QStringListModel>
#include <QQmlApplicationEngine>
#include "propertyhelper.h"
#include "httprequestworker.h"
#include "station.h"
class StationManager : public QObject
{
    Q_OBJECT
    AUTO_PROPERTY(QStringList, stations)
    AUTO_PROPERTY(QString, currentStationName)
    AUTO_PROPERTY(quint8, currentStationID)
    AUTO_PROPERTY(QTime, currentStationTime)
    AUTO_PROPERTY(QList<bool>, currentStationEnables)
public:
    explicit StationManager(QQmlApplicationEngine * engine,QObject *parent = nullptr);
    Q_INVOKABLE void updateStation(quint8 id,QString name, quint8 hour, quint8 minute, quint8 second,
                                   bool temp, bool hum, bool lux,bool soil, bool bat, bool co2);
    Q_INVOKABLE void addStation(quint8 id,QString name, quint8 hour, quint8 minute, quint8 second,
                                bool temp, bool hum, bool lux,bool soil, bool bat, bool co2);
    Q_INVOKABLE void removeCurrentStation();
    void setCurrentStation(int index);
    Q_INVOKABLE void retrieveStations();
    QStringListModel *stationsStrings;
    static QString getMessageString(HttpRequestWorker *worker);
signals:
    void updateFailed(QString reason);
    void updateSucceed();
    void removeFailed(QString reason);
    void removeSucceed();
    void addFailed(QString reason);
    void addSucceed();
public slots:
    void onStationChanged(int index);
    void handleRetrieveStationsResult(HttpRequestWorker *);
    void handleUpdateStationResult(HttpRequestWorker *);
    void handleRemoveCurrentStationResult(HttpRequestWorker*);
    void handleAddStationResult(HttpRequestWorker*);
private:

    Station currentStation_;
    QQmlApplicationEngine * engine;
    Station tempStation_;
    QList<Station> realStations_;
};

#endif // STATIONMANAGER_H
