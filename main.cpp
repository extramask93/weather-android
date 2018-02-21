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
#include "settingsmanager.h"
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;
    Settings settings{nullptr,"settings.json"};
    /*magic happens*/
    auto root_context = engine.rootContext();
    SettingsManager settingsManager{};
    root_context->setContextProperty("SettingsManager",&settingsManager);
    LoginHandler login{&settingsManager};
    root_context->setContextProperty("LoginHandler",&login);
    Interact interact{0,engine};
    root_context->setContextProperty("Interact",&interact);
    /*-----------------------------*/
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;
    interact.Run();
    return app.exec();
}
