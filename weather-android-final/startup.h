#ifndef STARTUP_H
#define STARTUP_H
#include <QQmlApplicationEngine>
#include <QObject>
#include <QQmlContext>

class Startup : public QObject
{
    Q_OBJECT
public:
    explicit Startup(QObject *parent,QQmlContext *context);
signals:

public slots:
private:
    QQmlApplicationEngine &engine_;
};

#endif // STARTUP_H
