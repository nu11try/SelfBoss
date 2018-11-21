#include "srvapi.h"

SrvApi::SrvApi(QObject *parent) : QObject(parent)
{

}

void SrvApi::sendGETSnap()
{

}

void SrvApi::send(QString taskID, QString screenMD5, QString keyboard)
{
    QString uri = "http://erg.1gb.ru/test/getSrvApi.php?";

    uri.append("taskID=");
    uri.append(taskID);
    uri.append("&");
    uri.append("screen=");
    uri.append(screenMD5);
    uri.append("&");
    uri.append("keyboard=");
    uri.append(keyboard);

    qDebug() << "SrvApi: " << uri;

    QUrl url(uri);

    QNetworkRequest request(url);
    QNetworkAccessManager *nam = new QNetworkAccessManager(this);
    QNetworkReply* reply = nam->get(request);
    connect(reply, SIGNAL(finished()), this, SLOT(getResponse()));
}


void SrvApi::getResponse()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());

    if (reply->error() == QNetworkReply::NoError) {
        // Получаем содержимое ответа

        result = reply->readAll();
        qDebug() << "SrvApi result: " << result;
        QJsonDocument doc = QJsonDocument::fromJson(result);
        QJsonObject obj = doc.object();
        resultEnd = obj.value("result").toString();

        qDebug() << "SrvApi resultEnd: " << resultEnd;

    } else {
        qDebug() << "kosyak blin";
    }

    reply->deleteLater();
}
