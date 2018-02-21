#ifndef SETTINGS_H
#define SETTINGS_H
#include <QJsonParseError>
#include <QJsonObject>
#include <QObject>
#include <QJsonDocument>
#include <QStringListModel>
class QDir;
class QFile;
class QString;
using JsonObjErrPair = std::pair<QJsonObject,QJsonParseError> ;

class Settings : public QObject
{
    Q_OBJECT
public:
    explicit Settings(QObject *parent, QString filename);
    QString LoadJSON();
    void ParseJSON(const QString & content);

signals:
    void NotifyStatusMessage(QString const msg);
public slots:
private:
    JsonObjErrPair GetJsonObject(const QString& raw);
    QString filename_;
    QString ReadJSONFromInternalResource();
    void SendErrorMessage(QString const &msg);
    QDir OpenConfigurationDirectory();
    void WriteDefaultsToStdConfigFile(QFile &file, const QString &sets);
    QString appTitle_;
    QString shortAppTitle_;
    int port_;
    QString ip_;
    int shortWait_;
    int longWait_;
    QStringList stations_;
    QStringListModel &stat_;
};

#endif // SETTINGS_H
