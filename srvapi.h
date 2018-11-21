#ifndef SRVAPI_H
#define SRVAPI_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QJsonDocument>
#include <QJsonObject>
#include <QByteArray>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>


class SrvApi : public QObject
{
    Q_OBJECT
public:
    explicit SrvApi(QObject *parent = 0);
    QByteArray result;
    QString resultEnd;

public slots:
    void send (QString, QString, QString);
    void sendGETSnap();
    void getResponse();

};

#endif // SRVAPI_H
