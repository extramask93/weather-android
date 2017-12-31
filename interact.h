#ifndef INTERACT_H
#define INTERACT_H

#include <QObject>
#include "propertyhelper.h"

class QQmlApplicationEngine;
class HttpRequestWorker;
class QStringList;
class Interact : public QObject
{
    Q_OBJECT
    AUTO_PROPERTY(QStringList, stations)
public:
    explicit Interact(QObject *parent,QQmlApplicationEngine &engine);
    void Run();
    void RetrieveStations();
public slots:
    void onLoginSignal(QString username, QString password);
    void onLogOutSignal();
    void handleResult(HttpRequestWorker *);
    void handleLogOutResult(HttpRequestWorker *);
    void handleRetrieveStationsResult(HttpRequestWorker *);
private:
    QQmlApplicationEngine &engine_;
    QObject *rootObject_;
};

#endif // INTERACT_H
