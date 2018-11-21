#include "sendphotosrv.h"
#include <QHttpMultiPart>
#include <QHttpPart>
#include <QFile>
#include <QVector>
#include <QBuffer>
#include <QPixmap>
#include <QEventLoop>
#include "filecount.h"
#include <QRegExp>
#include <QStringList>
#include <QtConcurrent/QtConcurrentRun>
#include <QFuture>
#include <QThreadPool>
#include <mainwindow.h>

SendPhotoSrv::SendPhotoSrv(QObject *parent) : QObject(parent)
{
    myStringList = new QStringList();
    path = new QString();
    filePath = new QString();

    fc = new FileCount();
    path->append(getenv ("AppData"));
    path->append("\\TimeCheckQtTest");
    path->append("\\Photo\\");

    //QThreadPool pool;
    //QFuture<void> future = QtConcurrent::run(&pool, send);
    //th = new QThread();
    //connect(this, SIGNAL(started()), this, SLOT(send()));
}

SendPhotoSrv::~SendPhotoSrv()
{
    //delete th;
}

void SendPhotoSrv::countFilePath()
{
    oldNewStringFile = fc->listfilesindir(*path);

    QRegExp rx("(\\\n)");
    *myStringList = oldNewStringFile.split(rx);

    //qDebug() << myStringList->at(0);

}

void SendPhotoSrv::send()
{
    MainWindow mw;
    QNetworkRequest request;
    QEventLoop loop;

    countFilePath();

    QString fileName;
    fileName.append(path);
    fileName.append(myStringList->at(0));

    QString path = getenv ("AppData");
    QString time = getenv ("AppData");
    QString CurrentTusk;
    QString CurrentTime;

    path.append("\\TimeCheckQtTest");
    path.append("\\tusk.txt");

    time.append("\\TimeCheckQtTest");
    time.append("\\time.txt");

    QFile CurTusk(path);
    CurTusk.open(QIODevice::ReadOnly);
    CurrentTusk = CurTusk.readAll();
    CurTusk.close();

    QFile CurTime(time);
    CurTime.open(QIODevice::ReadOnly);
    CurrentTime = CurTime.readAll();
    CurTime.close();

    //qDebug() << myStringList.size();
    //qDebug() << myStringList.last();
    QFile file(fileName);
    file.open(QIODevice::ReadOnly);

    request.setRawHeader("Host", "erg.1gb.ru");
    request.setUrl(QUrl("http://erg.1gb.ru/test/getPhoto.php"));
    request.setRawHeader("Content-Type", "multipart/form-data; boundary=---------------------------200242615429510");

    QByteArray array;
    array.append("-----------------------------200242615429510\r\n");
    array.append("Content-disposition: ");
    array.append("form-data; name=\"method\"\r\n");
    array.append("\r\n");
    array.append("post");
    array.append("\r\n");
    array.append("-----------------------------200242615429510\r\n");
    array.append("Content-disposition: ");
    array.append("form-data; name=\"key\"\r\n");
    array.append("\r\n");
    array.append("a1683bc4jhkjhkhkgutiuftsdrsr62dkiu");
    array.append("\r\n");
    array.append("-----------------------------200242615429510\r\n");
    array.append("-----------------------------200242615429510\r\n");
    array.append("Content-disposition: ");
    array.append("form-data; name=\"time\"\r\n");
    array.append("\r\n");
    array.append(CurrentTime);
    array.append("\r\n");
    array.append("-----------------------------200242615429510\r\n");
    array.append("Content-disposition: ");
    array.append("form-data; name=\"tusk\"\r\n");
    array.append("\r\n");
    array.append(CurrentTusk);
    array.append("\r\n");
    array.append("-----------------------------200242615429510\r\n");
    array.append("Content-disposition: ");
    array.append("form-data; name=\"file\"; filename=\".png\"\r\n");
    array.append("Content-Type: image/png");
    array.append("\r\n");
    array.append("\r\n");
    array.append(file.readAll());
    array.append("\r\n");
    array.append("-----------------------------200242615429510--");

    QNetworkAccessManager* pManager = new QNetworkAccessManager();
    QNetworkReply *reply = pManager->post(request, array);
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    qDebug() << "SendPhotoSrc: " << reply->readAll();

    //count++;

    qDebug() << file.fileName();

    file.remove();
    countFilePath();
    //th->quit();
}

void SendPhotoSrv::start()
{

}

void SendPhotoSrv::runTh()
{

    //this->moveToThread( this->th );
    //th->start();
}
