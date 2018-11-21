#ifndef MAIN
#define MAIN

#include <QString>
#include <QMap>
#include <QDebug>

class Session {
public:
    QString token;
    QMap<QString, int> task;
    qint64 curTask;
    bool sendFieldsEnabled;
};

class SrvApi {
public:
    void send(qint64, const QString, unsigned int);
};

class SrvImgApi {
public:
    qint64 taskId;
    void send(QString);
    bool check(QString md5);
};





#endif // MAIN

