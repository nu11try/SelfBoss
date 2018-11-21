#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "screenshotmaker.h"
#include "loginform.h"
#include "hook.h"
#include "srvapi.h"
#include "sendphotosrv.h"
//-------------------------------------
#include <QTimer>
#include <QVector>
#include <QPixmap>
#include <QTime>
#include <QElapsedTimer>
#include <QString>
#include <QDebug>
#include <QStringList>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QMessageBox>
#include <QCloseEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this -> setTrayIconActions();
    this -> showTrayIcon();

    ui->lb_time_track->setAlignment(Qt::AlignCenter);
    ui->lb_time_track->setText("00:00:00");

    //Tusk << "CreateLog" << "CreateText" << "RenderingVideo";
    //ui->comboBox->addItems(Tusk);

    timer = new QTimer(this);

    ui->toolButton->setIcon(QIcon(":/settings.ico"));

    MainWindow::setWindowFlags(Qt::WindowStaysOnTopHint);
    MainWindow::activateWindow();

    ScreenShot = new screenshotmaker();
    sps = new SendPhotoSrv();
}

void MainWindow::keyboardHook(int key)
{
    keyboardHookCount++;
    qDebug() << "Keyboard Count Hook:" << keyboardHookCount << " + keyCode: " << key;
}

void MainWindow::keyboardHookEnd()
{
    keyboardHookCount = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
    delete timer;
    delete ScreenShot;
    delete sps;
}

QString MainWindow::getTuskNow()
{

    return CurrentTusk;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QString uri = "http://erg.1gb.ru/test/close.php?";

    uri.append("close=closeApp");

    QUrl url(uri);

    QNetworkRequest request(url);
    QNetworkAccessManager *nam = new QNetworkAccessManager(this);
    QNetworkReply* reply = nam->get(request);
    connect(reply, SIGNAL(finished()), this, SLOT(getResponse()));
    QMessageBox::StandardButton reply1;
      reply1 = QMessageBox::question(this, "Exit", "Вы точно хотите выйти?",
                                    QMessageBox::Yes|QMessageBox::No);
      if (reply1 == QMessageBox::Yes) {
        QApplication::quit();
      }
}

void MainWindow::getResponse()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());

    if (reply->error() == QNetworkReply::NoError) {
        // Получаем содержимое ответа
        result = reply->readAll();
        qDebug() << "MainWindowForm close: " << result;
    } else {
     qDebug() << reply->error();
    }
    reply->deleteLater();
}

void MainWindow::onUpdate()
{
    res = elTimer.elapsed();
    sec = res / 1000;
    if (sec > 59) {
        screens = ScreenShot->makeScreenshots();
        min++;
        minSrv++;
        if (minSrv >= 1) {
            srvApi.send(ui->comboBox->currentText(), "md5"/*screens[i]*/, QString::number(keyboardHookCount));
            sps->countFilePath();
            sps->runTh();
            minSrv = 0;
            screens.clear();
        }
        if (min > 59) { hr++; min = 0; }
        qDebug() << "Часы: " << hr;
        qDebug() << "Минуты: " << min;
        qDebug() << "min15: " << minSrv;
        elTimer.restart();
    }

    if (hr < 10 && min < 10 && sec < 10) timeNow = QString("0%1:0%2:0%3").arg(hr).arg(min).arg(sec);
    else if (hr < 10 && min < 10 && sec >= 10) timeNow = QString("0%1:0%2:%3").arg(hr).arg(min).arg(sec);
    else if (hr < 10 && min >= 10 && sec < 10) timeNow = QString("0%1:%2:0%3").arg(hr).arg(min).arg(sec);
    else if (hr < 10 && min >= 10 && sec >= 10) timeNow = QString("0%1:%2:%3").arg(hr).arg(min).arg(sec);
    else if (hr >= 10 && min < 10 && sec >= 10) timeNow = QString("%1:0%2:%3").arg(hr).arg(min).arg(sec);
    else if (hr >= 10 && min < 10 && sec < 10) timeNow = QString("%1:0%2:0%3").arg(hr).arg(min).arg(sec);
    else timeNow = QString("%1:%2:%3").arg(hr).arg(min).arg(sec);

    ui->lb_time_track->setText(timeNow);
}

void MainWindow::getData(QString nameGet, QString tokenGet, QString tusk)
{
    QString temp;
    for(int i = 0; i < tusk.length(); i++) {
        if(tusk[i].unicode()!=95) {
            temp = temp + tusk[i];
        } else {
            Tusk << temp;
            temp = "";
        }
    }

    name = nameGet;
    token = tokenGet;
    ui->label->setText(name);
    ui->comboBox->addItems(Tusk);
}

void MainWindow::on_pushButton_clicked()
{
   Hook* hook = new Hook(this);

   QString path = getenv ("AppData");
   QString pathTime = getenv ("AppData");

   path.append("\\TimeCheckQtTest");
   path.append("\\tusk.txt");

   pathTime.append("\\TimeCheckQtTest");
   pathTime.append("\\time.txt");

   //qDebug() << "Current Tusk = " << CurrentTusk;
   if (StartTime) {
       ui->pushButton->setText("Старт");
       StartTime = false;
       elTimer.restart();
       timer->stop();

       QFile CurTime(pathTime);
       CurTime.open(QIODevice::WriteOnly);
       CurrentTime = ui->lb_time_track->text();
       CurTime.write(CurrentTime.toUtf8());
       CurTime.close();

       ui->lb_time_track->setText("00:00:00");

       sec = min = hr = 0;

       connect(hook, SIGNAL(hookEvent(int)), this, SLOT(keyboardHookEnd()));

   } else {

       QFile CurTusk(path);
       CurTusk.open(QIODevice::WriteOnly);
       CurrentTusk = ui->comboBox->currentText();
       CurTusk.write(CurrentTusk.toUtf8());
       CurTusk.close();

       ui->lb_time_track->setText("00:00:00");

       QFile CurTime(pathTime);
       CurTime.open(QIODevice::WriteOnly);
       CurrentTime = ui->lb_time_track->text();
       CurTime.write(CurrentTime.toUtf8());
       CurTime.close();

       StartTime = true;
       ui->pushButton->setText("Стоп");
       timer->setInterval(1000);
       connect(timer, SIGNAL(timeout()), this, SLOT(onUpdate()));

       connect(hook, SIGNAL(hookEvent(int)), this, SLOT(keyboardHook(int)));

       timer->start(0);
       elTimer.start();
   }
   ScreenShot->makeScreenshots();

   sps->countFilePath();
   sps->send();
}

// все для работы трее
void MainWindow::changeEvent(QEvent *event)
{
    QMainWindow::changeEvent(event);
    if (event -> type() == QEvent::WindowStateChange)
    {
       if (isMinimized())
       {
          this -> hide();
       }
    }
}

void MainWindow::trayIconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason)
    {
       case QSystemTrayIcon::Trigger:
        this->setWindowFlags(Qt::WindowStaysOnTopHint);
        MainWindow::showNormal();
            break;
       case QSystemTrayIcon::DoubleClick:
            //this -> trayActionExecute();
            break;
       default:
            break;
    }
}

void MainWindow::trayActionExecute()
{
    QMessageBox::information(this, "TrayIcon", "Тестовое сообщение. Замените вызов этого сообщения своим кодом.");
}

void MainWindow::setTrayIconActions()
{
    // Setting actions...
    minimizeAction = new QAction("Свернуть", this);
    restoreAction = new QAction("Восстановить", this);
    quitAction = new QAction("Выход", this);

    // Connecting actions to slots...
    connect (minimizeAction, SIGNAL(triggered()), this, SLOT(hide()));
    connect (restoreAction, SIGNAL(triggered()), this, SLOT(showNormal()));
    connect (quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

    // Setting system tray's icon menu...
    trayIconMenu = new QMenu(this);
    trayIconMenu -> addAction (minimizeAction);
    trayIconMenu -> addAction (restoreAction);
    trayIconMenu -> addAction (quitAction);
}

void MainWindow::showTrayIcon()
{
    // Создаём экземпляр класса и задаём его свойства...
    trayIcon = new QSystemTrayIcon(this);
    QIcon trayImage(":/tree.png");
    trayIcon -> setIcon(trayImage);
    trayIcon -> setContextMenu(trayIconMenu);

    // Подключаем обработчик клика по иконке...
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(trayIconActivated(QSystemTrayIcon::ActivationReason)));

    // Выводим значок...
    trayIcon -> show();
}
//----------------------------------------------------
