#include "filecount.h"
#include <QDir>
#include <QString>
#include <QFileInfoList>
#include <QFileInfo>

FileCount::FileCount()
{

}

QString FileCount::listfilesindir(QString path)
{
    /*
    Функция считывает список файлов (включая скрытые) в директории в QString.
    Входные параметры:
     path - путь к папке.
    Возвращаемое значение:
     Строка со списком файлов в директории, разделенные \n в алфавитном порядке.
    */
    QString line="";
    QDir dir(path);
    bool ok = dir.exists();
    if (ok)
    {
        dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
        dir.setSorting(QDir::Name);
        QFileInfoList list = dir.entryInfoList();

        for (int i = 0; i < list.size(); ++i)
        {
            QFileInfo fileInfo = list.at(i);
            line+=fileInfo.fileName()+"\n";
        }
    }
    return line;
}

