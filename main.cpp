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
    QList<QObject*> datalist;
    datalist.append(new Station(1,"prototype"));
    datalist.append(new Station(2,"dupa"));
    datalist.append(new Station(3,"wtf"));

    /*----------*/
    auto root_context = engine.rootContext();
    root_context->setContextProperty("mymodel",QVariant::fromValue(datalist));
    SettingsManager settingsManager{};
    root_context->setContextProperty("SettingsManager",&settingsManager);
    LoginHandler login{&settingsManager};
    root_context->setContextProperty("LoginHandler",&login);
    MeasurementsModel model{nullptr,nullptr,engine};
    root_context->setContextProperty("Model",&model);
    Interact interact{0,engine,&model, &login};
    root_context->setContextProperty("Interact",&interact);
     qmlRegisterType<RegisterModel>("com.registration",1,0,"RegisterModel");
    /*-----------------------------*/
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;
    return app.exec();
}
