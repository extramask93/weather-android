#include "startup.h"
#include <QDebug>
Startup::Startup(QObject *parent, QQmlContext *context) : QObject(parent), engine_{*new QQmlApplicationEngine{}}
{
}
