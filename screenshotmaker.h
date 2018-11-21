#ifndef SCREENSHOTMAKER_H
#define SCREENSHOTMAKER_H

#include <QObject>
#include <QVector>
#include <QPixmap>

class screenshotmaker : public QObject
{
    Q_OBJECT
public:

    explicit screenshotmaker(QObject *parent = 0);
    QVector<QPixmap> makeScreenshots();
    //void makeScreenshots();
};

#endif // SCREENSHOTMAKER_H
