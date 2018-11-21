#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QStringList>
#include <QElapsedTimer>
#include "screenshotmaker.h"
#include "srvapi.h"
#include "sendphotosrv.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QCryptographicHash>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QTimer *timer;
    qint64 res;
    qint64 sec;
    qint64 min = 0;
    qint64 hr = 0;
    qint64 keyboardHookCount = 0;
    bool StartTime = false;
    QString timeNow;
    QStringList Tusk;
    QStringList lst;
    SrvApi srvApi;
    QString name;
    QString token;
    QString CurrentTusk;
    QString CurrentTime;
    int minSrv = 0;
    QString result;

    QElapsedTimer elTimer;

    QVector<QPixmap> screens;

    screenshotmaker *ScreenShot;
    SendPhotoSrv *sps;

    QString getTuskNow();

protected:
    void closeEvent(QCloseEvent *event);

public slots:
    void onUpdate();
    void getData(QString nameGet, QString tokenGet, QString tusk);
    void getResponse();
private slots:
    void on_pushButton_clicked();
    void keyboardHook(int key);
    void keyboardHookEnd();
    void changeEvent(QEvent*);
    void trayIconActivated(QSystemTrayIcon::ActivationReason reason);
    void trayActionExecute();
    void setTrayIconActions();
    void showTrayIcon();
private:
    Ui::MainWindow *ui;
    QMenu *trayIconMenu;
    QAction *minimizeAction;
    QAction *restoreAction;
    QAction *quitAction;
    QSystemTrayIcon *trayIcon;
};

#endif // MAINWINDOW_H
