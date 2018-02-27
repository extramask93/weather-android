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
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;
    /*magic happens*/
    auto root_context = engine.rootContext();
    SettingsManager settingsManager{};
    root_context->setContextProperty("SettingsManager",&settingsManager);
    LoginHandler login{&settingsManager};
    root_context->setContextProperty("LoginHandler",&login);
    MeasurementsModel model{nullptr,nullptr,engine};
    root_context->setContextProperty("Model",&model);
    Interact interact{0,engine,&model, &login};
    root_context->setContextProperty("Interact",&interact);
    /*-----------------------------*/
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;
    return app.exec();
}
