#ifndef CLIPIMAGES_H
#define CLIPIMAGES_H

#include <QtGui>
#include "properties.h"

class clipImages
{
public:
    clipImages();

    QImage        *img;
    int LXcenter, LYcenter, RXcenter, RYcenter, DXcenter, DYcenter;

    void workImage();
    void clipImage();

private:
    QImage       *bimg;
    bool findLeftBlock(int x, int y, int w, int h);
    bool findRightBlock(int x, int y, int w, int h);
    bool findDownBlock(int x, int y, int w, int h);
    bool findCenter(int x, int y, int *x_center, int *y_center);

};

#endif // CLIPIMAGES_H
