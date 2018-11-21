#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QMainWindow>
#include <QString>
#include <QStringList>
#include <QJsonDocument>
#include <QJsonObject>
#include <QByteArray>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QThread>

namespace Ui {
class LoginForm;
}

class LoginForm : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginForm(QWidget *parent = 0);
    ~LoginForm();

    QThread *thLogin;

    QString login;
    QString pass;
    QString token;
    QString tusk;
    QString name;
    QByteArray result;
    int resultEnd = -1;

public slots:
    void on_pushButton_clicked();
    void sendGETData(QString, QString);
    void getResponse();
    void openNextForm();

private:
    Ui::LoginForm *ui;
};

#endif // LOGINFORM_H
