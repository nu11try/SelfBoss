#include "screenshotmaker.h"
#include <QPixmap>
#include <QApplication>
#include <QDesktopWidget>
#include <QScreen>
#include <QDebug>
#include <QFile>
#include <QDateTime>
#include <QTime>
#include <QTextStream>
#include <QBuffer>
#include <QByteArray>
#include <QCryptographicHash>
#include <QtConcurrent/QtConcurrentRun>


screenshotmaker::screenshotmaker(QObject *parent)
{}


QVector<QPixmap> screenshotmaker::makeScreenshots()
{

    QString path = getenv ("AppData");
    QString filePath = path.append("\\TimeCheckQtTest");
    path.append("\\Photo\\");
    QByteArray fileData;
    QByteArray hashData;
    QVector<QPixmap> screenshots;

    const int screenCount = QApplication::desktop()->screenCount();
    qDebug()<<"Screenshotmaker: screenCount: "<<screenCount;

    QFile fileForMD5(filePath.append("\\md5.txt"));
    fileForMD5.open(QIODevice::WriteOnly);

    for (int i = 0; i < screenCount; i++) {

        QString filePath = QString("%1%2.%3.%4.%5.png").arg(path)
                .arg(QTime::currentTime().hour()).arg(QTime::currentTime().minute())
                .arg(QTime::currentTime().second()).arg(QTime::currentTime().msec());
        qDebug() << "Screenshotmaker:" << filePath;

        QFile fileSaveScreen(filePath);
        fileSaveScreen.open(QIODevice::ReadWrite);

        QDesktopWidget *desktop = QApplication::desktop();
        QRect geo = desktop->screenGeometry(i);

        QScreen *primaryScreen = QApplication::primaryScreen();
        QFuture<QPixmap> future;
        future = QtConcurrent::run(primaryScreen, &QScreen::grabWindow,
                                   desktop->winId(),
                                   geo.left(), geo.top(),
                                   geo.width(), geo.height());
        future.waitForFinished();
        QPixmap screenshot = future.result();

        screenshot.save(&fileSaveScreen, "PNG");

        screenshots.append(screenshot);

        QBuffer buf(&fileData);
        screenshot.save(&buf, "PNG");
        qDebug() << "ScreenshotMaker:" << fileData;
        //---------------------------------

        fileSaveScreen.close();
    }
    fileForMD5.close();
    return screenshots;
}

