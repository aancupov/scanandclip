#ifndef SELECTIMAGES_H
#define SELECTIMAGES_H

#include <QString>
#include <QDir>

class selectImages
{
public:
    selectImages(QString &path);
    QString firstJPG();
    QString nextJPG();
    QString prevJPG();

private:
    QDir dir;
    QStringList* strL;
    int current;
    int size;
};

#endif // SELECTIMAGES_H
