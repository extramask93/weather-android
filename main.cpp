#include <QGuiApplication>
#include <QApplication>
#include <QQmlApplicationEngine>
#include "startup.h"
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
    /*magic happens*/
    auto root_context = engine.rootContext();
    root_context->setContextProperty("LoginHandler",&login);
    /*-----------------------------*/
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;
    Startup startup{nullptr,engine.rootContext()};
    Interact interact{0,engine};
    MeasurementsModel mmodel(0);
    root_context->setContextProperty("MModel", &mmodel) ;
    root_context->setContextProperty("Interact",&interact);
    interact.Run();
    return app.exec();
}
