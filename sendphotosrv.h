#ifndef SENDPHOTOSRV_H
#define SENDPHOTOSRV_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QJsonDocument>
#include <QJsonObject>
#include <QByteArray>
#include <QVector>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include "filecount.h"
#include <QThread>

class SendPhotoSrv : public QObject
{
    Q_OBJECT
public:
    explicit SendPhotoSrv(QObject *parent = 0);
    ~SendPhotoSrv();
    QNetworkAccessManager manager;
    QNetworkReply *reply;
    QUrl url;
    QByteArray requestString;

    QThread *th;

    // для получения файлов
    void countFilePath();
    QString oldNewStringFile;
    QVector<QString> fileInPath;
    QStringList *myStringList;
    QString *path;
    QString *filePath;
    FileCount *fc;
    int count = 0;
    // -------------------

public slots:
    void send();
    void start();

    void runTh();
};

#endif // SENDPHOTOSRV_H
