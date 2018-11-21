#include "loginform.h"
#include "ui_loginform.h"
#include "mainwindow.h"
#include <QUrl>
#include <QDebug>

LoginForm::LoginForm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginForm)
{
    ui->setupUi(this);
    ui->errors->setAlignment(Qt::AlignCenter);

    //thLogin = new QThread();
    //QObject::connect(thLogin, SIGNAL(started()), this, SLOT(sendGETData(login, pass)));
}

LoginForm::~LoginForm()
{
    delete ui;
}

void LoginForm::on_pushButton_clicked()
{
    login = ui->lineEdit->text();
    pass = ui->lineEdit_2->text();

    //this->moveToThread(this->thLogin);

    //thLogin->start();

    emit sendGETData(login, pass);
}

void LoginForm::sendGETData(QString login, QString password)
{
    QString uri = "http://erg.1gb.ru/test/auth.php?";

    uri.append("login=");
    uri.append(login);
    uri.append("&");
    uri.append("pass=");
    uri.append(password);

    QUrl url(uri);

    QNetworkRequest request(url);
    QNetworkAccessManager *nam = new QNetworkAccessManager(this);
    QNetworkReply* reply = nam->get(request);
    connect(reply, SIGNAL(finished()), this, SLOT(getResponse()));
}

void LoginForm::getResponse() {
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());

    if (reply->error() == QNetworkReply::NoError) {
        // Получаем содержимое ответа

        //qDebug() << result;

        result = reply->readAll();
        QJsonDocument doc = QJsonDocument::fromJson(result);
        QJsonObject obj = doc.object();
        resultEnd = obj.value("result").toInt();
        token = obj.value("token").toString();
        name = obj.value("name").toString();
        tusk = obj.value("tusk").toString();


        qDebug() << "LoginForm token: " << token;
        qDebug() << "LoginForm name: " << name;
        qDebug() << "LoginForm result: " << resultEnd;
        qDebug() << "LoginForm tusk: " << tusk;

    } else {
     qDebug() << reply->error();
    }

    reply->deleteLater();

    emit openNextForm();
}

void LoginForm::openNextForm()
{
    //qDebug() << resultEnd;

    if (resultEnd == 10)
    {
        MainWindow *w = new MainWindow();
        w->setAttribute(Qt::WA_DeleteOnClose, true);
        w->setFixedSize(w->width(), w->height());
        w->show();
        emit w->getData(name, token, tusk);
        this->close();

    } else {
        ui->lineEdit->setText("");
        ui->lineEdit_2->setText("");

        ui->errors->setText("Данные не верны!");
    }
}
