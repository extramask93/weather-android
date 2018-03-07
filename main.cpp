#include <QGuiApplication>
#include <QApplication>
#include <QQmlApplicationEngine>
#include "startup.h"
#include <QLoggingCategory>
#include <QQmlContext>
#include "loginhandler.h"
#include "interact.h"
#include "measurementsmodel.h"
#include "settingsmanager.h"
#include "registermodel.h"
#include "station.h"
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;
    /*magic happens*/
    /*----------*/



    /*----------*/
    auto root_context = engine.rootContext();
    qRegisterMetaType<Station>("Station");
    qRegisterMetaType<Sensor>("Sensor");
    qmlRegisterType<Sensor>("foo.bar",1,0,"Sensor");
    qmlRegisterType<Station>("foo.bar",1,0,"Station");
    SettingsManager settingsManager{};
    root_context->setContextProperty("SettingsManager",&settingsManager);
    LoginHandler login{&settingsManager};
    root_context->setContextProperty("LoginHandler",&login);
    MeasurementsModel model{nullptr,nullptr,engine};
    Station currentStation(0);
    root_context->setContextProperty("CurrentStation", &currentStation);
    root_context->setContextProperty("Model",&model);
    Interact interact{0,engine,&model, &login, &currentStation};
    root_context->setContextProperty("Interact",&interact);
     qmlRegisterType<RegisterModel>("com.registration",1,0,"RegisterModel");
    /*-----------------------------*/
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;
    return app.exec();
}
