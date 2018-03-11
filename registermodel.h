#ifndef REGISTERMODEL_H
#define REGISTERMODEL_H

#include <QObject>
#include "httprequestworker.h"

class RegisterModel : public QObject
{
    Q_OBJECT
public:
    explicit RegisterModel(QObject *parent = nullptr);
    Q_INVOKABLE void registerUser(QString name, QString email, QString password, QString phone);

signals:
    void registrationFailed(QString reason);
    void registrationSuccess();
public slots:
    void HandleResult(HttpRequestWorker *);
};

#endif // REGISTERMODEL_H
