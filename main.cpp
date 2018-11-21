#include "mainwindow.h"
#include "loginform.h"
#include <QApplication>
#include <QDir>
#include <QDebug>
#include "global.h"
#include <QDateTime>
#include <QObject>
#include <QFileInfoList>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginForm lForm;
    lForm.setFixedSize(lForm.width(), lForm.height());
    lForm.show();

    QString path = getenv ("AppData");
    QString pathCur;
    QString pathTime;

    path.append("\\TimeCheckQtTest");

    pathCur = path;
    pathCur.append("\\tusk.txt");

    pathTime = path;
    pathTime.append("\\time.txt");

    if (!(QDir().exists(path))) {
        QDir().mkdir(path);
        QDir().mkdir(path.append("\\Photo"));
    }

    QFile CurTusk(pathCur);
    CurTusk.open(QIODevice::WriteOnly);
    CurTusk.close();

    QFile CurTime(pathTime);
    CurTime.open(QIODevice::WriteOnly);
    CurTime.close();

    QDateTime dat;
    dat = QDateTime::currentDateTime();
    //filePathPhoto = new QString();
    filePathPhoto->append(QString("%1\\%2.%3.%4.%5.%6\\%7").arg(path).arg(dat.toString("dd.MM.yyyy.HH.MM.ss"))
            .arg(QTime::currentTime().hour()).arg(QTime::currentTime().minute())
            .arg(QTime::currentTime().second()).arg(QTime::currentTime().msec()).arg("\\Photo"));

    QDir().mkdir(*filePathPhoto);



    //qDebug() << listfilesindir(path.append("\\Photo"));

    return a.exec();
}

