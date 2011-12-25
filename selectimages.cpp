#include "selectimages.h"

selectImages::selectImages(QString& path)
{
    QStringList filter;

    filter.append(QString("*.jpg"));
    filter.append(QString("*.JPG"));

    dir.setPath(path);
    //dir.setFilter(filter);

    strL = new QStringList(dir.entryList(filter,QDir::Files));

    size = strL->size();
    current = 0;
    printf("size=%d\n",size);
}

QString selectImages::firstJPG()
{
    current = 0;
    if(size==0) return("");
    return(dir.path()+QString("/")+strL->at(current));
}

QString selectImages::nextJPG()
{
    if(size==0) return("");
    if(current+1 < size) ++current;
    else current = 0;
    return(dir.path()+QString("/")+strL->at(current));
}

QString selectImages::prevJPG()
{
    if(size==0) return("");
    if(current-1 > 0) --current;
    else current = size - 1;
    return(dir.path()+QString("/")+strL->at(current));
}
