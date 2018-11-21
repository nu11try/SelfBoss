#ifndef NETWORK_H
#define NETWORK_H

#include <QObject>
#include <QString>

class NetWork
{
public:
    NetWork();

public slots:
    void slotLogin(QString login, QString password);
    void slotLoginResult(QString result);
};

#endif // NETWORK_H
