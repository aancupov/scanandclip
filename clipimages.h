#ifndef CLIPIMAGES_H
#define CLIPIMAGES_H

#include <QtGui>
#include "properties.h"
#include "/home/andrew/QtSDK/testBaseRecognise/baserecognise.h"
#include "managerofalgorithms.h"

class clipImages
{
public:
    clipImages();

    QImage        *img;
    int LXcenter, LYcenter, RXcenter, RYcenter, DXcenter, DYcenter;

    void workImage();
    void clipImage();
    void study(int x, int y, int w, int h, QString d3);
    QString recognise(int x, int y, int w, int h);
    void quoter(int x, int y, int w, int h, int *x1, int *y1, int *w1, int *h1);                     //определить четверти цифры

private:
    baseRecognise *brec;
    QImage       *bimg;
    managerOfAlgorithms *malg;
    bool findLeftBlock(int x, int y, int w, int h);                 //найден левый блок
    bool findRightBlock(int x, int y, int w, int h);                //найден правыйблок
    bool findDownBlock(int x, int y, int w, int h);                 //найден нижний блок
    bool findCenter(int x, int y, int *x_center, int *y_center);    //найден центр блока
    bool isBlack(int x, int y);                                     //точка является черной
    QString norma(QString rez, bool vert);                          //приведение линии результата к нормальной форме
    QString digital(int x, int y, int w, int h);                    //обозначить цифру
    QString normalDigit(int  x, int y, int w, int h);
    int minr(int i, int j, int x, int y, int w, int h);
};

#endif // CLIPIMAGES_H
