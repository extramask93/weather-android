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
#include "stationmanager.h"
#include "registermodel.h"
#include "station.h"
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;
    auto root_context = engine.rootContext();

    qmlRegisterType<RegisterModel>("com.registration",1,0,"RegisterModel");

    SettingsManager settingsManager{};
    root_context->setContextProperty("SettingsManager",&settingsManager);

    LoginHandler login{&settingsManager};
    root_context->setContextProperty("LoginHandler",&login);

    MeasurementsModel model{nullptr,nullptr,engine};
    root_context->setContextProperty("Model",&model);

    Interact interact{0,engine,&model, &login};
    root_context->setContextProperty("Interact",&interact);

    StationManager stationManager(nullptr);
    root_context->setContextProperty("StationManager", &stationManager);
    /*-----------------------------*/
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;
    return app.exec();
}
