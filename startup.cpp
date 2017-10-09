#include "startup.h"
#include <QDebug>
Startup::Startup(QObject *parent, QQmlContext *context) : QObject(parent), engine_{*new QQmlApplicationEngine{}}, mainview_(*new MainViewMgr{})
{
    auto rootContext = context;
    rootContext->setContextProperty("MainViewMgr", &mainview_);
    qDebug()<<"asd";
}
