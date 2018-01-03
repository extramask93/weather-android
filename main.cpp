#include <QGuiApplication>
#include <QApplication>
#include <QQmlApplicationEngine>
#include "startup.h"
#include <QLoggingCategory>
#include <QQmlContext>
#include "loginhandler.h"
#include "settings.h"
#include "interact.h"
#include "measurementsmodel.h"
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;
    LoginHandler login;
    Settings settings{nullptr,"settings.json"};
    QLoggingCategory::setFilterRules("qt.network.ssl.w arning=false");
    /*magic happens*/
    auto root_context = engine.rootContext();
    root_context->setContextProperty("LoginHandler",&login);
    Interact interact{0,engine};
    root_context->setContextProperty("Interact",&interact);
    /*-----------------------------*/
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;
    Startup startup{nullptr,engine.rootContext()};
    MeasurementsModel mmodel(0);
    root_context->setContextProperty("MModel", &mmodel) ;
    interact.Run();
    return app.exec();
}
