#ifndef INTERACT_H
#define INTERACT_H

#include <QObject>
#include <QList>
#include "measurement.h"
#include "measurementsmodel.h"
#include "propertyhelper.h"
#include "settingsmanager.h"

class QQmlApplicationEngine;
class HttpRequestWorker;
class Measurement;
class QStringList;
class SettingsHandler;
class Interact : public QObject
{
    Q_OBJECT
    AUTO_PROPERTY(QStringList, stations)
public:
    explicit Interact(QObject *parent,QQmlApplicationEngine &engine);
    void Run();
public slots:
    void onMainViewLoaded();
    void RetrieveStations();
    void onUpdateChartSignal(QString type);
    void onLoginSignal(QString username, QString password);
    void onLogOutSignal();
    void handleResult(HttpRequestWorker *);
    void handleLogOutResult(HttpRequestWorker *);
    void handleRetrieveStationsResult(HttpRequestWorker *);
    void updateMeasurements(HttpRequestWorker *);
    void updateDailyJSON();
    void onStationChanged(int index);
private:
    QQmlApplicationEngine &engine_;
    QList<Measurement*> measurementList_;
    SettingsHandler *settings_;
    QObject *rootObject_;
    HttpRequestWorker *worker_;
    std::pair<QString, int> currentStation;
    QList<std::pair<QString,int>> stationsAndIndexes;
    MeasurementsModel *model;
    QTimer *timer;
};

#endif // INTERACT_H
