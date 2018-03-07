#ifndef INTERACT_H
#define INTERACT_H

#include <QObject>
#include <QList>
#include "measurement.h"
#include "measurementsmodel.h"
#include "propertyhelper.h"
#include "settingsmanager.h"
#include "loginhandler.h"
#include "station.h"
#include <memory>

class QQmlApplicationEngine;
class HttpRequestWorker;
class Measurement;
class QStringList;
class SettingsHandler;
class Interact : public QObject
{
    Q_OBJECT
    AUTO_PROPERTY(QStringList, stations)
    AUTO_PROPERTY(QList<QObject*>, stations2)

public:
    explicit Interact(QObject *parent, QQmlApplicationEngine &engine, MeasurementsModel *modell, LoginHandler *login, Station *currentStat);
    ~Interact();
    Q_INVOKABLE void updateStation(quint8 id,QString name, quint8 hour, quint8 minute, quint8 second,
                                   bool temp, bool hum, bool lux,bool soil, bool bat, bool co2);
    Q_INVOKABLE void addStation(quint8 id,QString name, quint8 hour, quint8 minute, quint8 second,
                                bool temp, bool hum, bool lux,bool soil, bool bat, bool co2);
    Q_INVOKABLE void removeCurrentStation();
public slots:
    void onMainViewLoaded();
    void onSettingsLoaded();
    void RetrieveStations();
    void onUpdateChartSignal(QString type, qint64 index);
    void handleRetrieveStationsResult(HttpRequestWorker *);
    void handleUpdateStationResult(HttpRequestWorker *);
    void handleRemoveCurrentStationResult(HttpRequestWorker*);
    void handleAddStationResult(HttpRequestWorker*);
    void updateMeasurements(HttpRequestWorker *);
    void updateDailyJSON();
    void onStationChanged(int);
signals:
    void updateFailed(QString reason);
    void updateSucceed();
    void removeFailed(QString reason);
    void removeSucceed();
    void addFailed(QString reason);
    void addSucceed();
private:
    Station tempStation;
    QQmlApplicationEngine &engine_;
    QList<Measurement*> measurementList_;
    SettingsHandler *settings_;
    QObject *rootObject_;
    HttpRequestWorker *worker_;
    Station *currentStation;
    QList<Station> stations_;
    MeasurementsModel *model;
    LoginHandler *login_;
    std::unique_ptr<QTimer> timer;
};

#endif // INTERACT_H
