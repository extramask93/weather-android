#ifndef INTERACT_H
#define INTERACT_H

#include <QObject>
#include <QList>
#include "measurement.h"
#include "measurementsmodel.h"
#include "propertyhelper.h"
#include "settingsmanager.h"
#include "loginhandler.h"
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
public:
    explicit Interact(QObject *parent, QQmlApplicationEngine &engine, MeasurementsModel *modell, LoginHandler *login);
public slots:
    void onMainViewLoaded();
    void RetrieveStations();
    void onUpdateChartSignal(QString type, qint64 index);
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
    LoginHandler *login_;
    std::unique_ptr<QTimer> timer;
};

#endif // INTERACT_H
