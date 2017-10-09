#ifndef STARTUP_H
#define STARTUP_H
#include <QQmlApplicationEngine>
#include <QObject>
#include <QQmlContext>
#include "mainviewmgr.h"

class Startup : public QObject
{
    Q_OBJECT
public:
    explicit Startup(QObject *parent,QQmlContext *context);
signals:

public slots:
private:
    QQmlApplicationEngine &engine_;
    int abc;
    MainViewMgr &mainview_;
};

#endif // STARTUP_H
