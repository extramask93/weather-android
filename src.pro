include(../defaults.pri)
QT += core gui qml quick charts
CONFIG   += console
CONFIG   -= app_bundle
CONFIG 	+= c++14 

TEMPLATE = lib

TARGET = myapp

SOURCES += \
    startup.cpp \
    loginhandler.cpp \
    settings.cpp \
    httprequestworker.cpp \
    interact.cpp \
    measurementsmodel.cpp \
    measurement.cpp \
    calendar.cpp \
    settingshandler.cpp
HEADERS += \
    startup.h \
    loginhandler.h \
    propertyhelper.h \
    settings.h \
    httprequestworker.h \
    interact.h \
    measurementsmodel.h \
    measurement.h \
    calendar.h \
    settingshandler.h
