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
    Settings settings{nullptr,"settings.json"};
    /*magic happens*/
    auto root_context = engine.rootContext();
    LoginHandler login{engine,0};
    root_context->setContextProperty("LoginHandler",&login);
    Interact interact{0,engine};
    root_context->setContextProperty("Interact",&interact);
    /*-----------------------------*/
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    Startup startup{nullptr,engine.rootContext()};
    interact.Run();
    return app.exec();
}
