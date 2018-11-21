#ifndef FILECOUNT_H
#define FILECOUNT_H

#include <QObject>

class FileCount
{
public:
    FileCount();
    QString listfilesindir(QString path);
};

#endif // FILECOUNT_H
