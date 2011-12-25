#include "clipimages.h"

clipImages::clipImages()
{
    img = new QImage();
    bimg = new QImage();
}

bool clipImages::findLeftBlock(int x, int y, int w, int h)
{

    for(int i=0; i<= w;i+=10)
    {
        for(int j=0; j <= h;j+=10)
        {
            //printf("Проверка точки: %d:%d\n",x+i,y+j);
            if(findCenter(x+i,y+j,&LXcenter, &LYcenter)) return true;
        }
    }
    return false;
}

bool clipImages::findRightBlock(int x, int y, int w, int h)
{
    for(int i=0; i<= w;i+=10)
    {
        for(int j=0; j <= h;j+=10)
        {
            //printf("Проверка точки: %d:%d\n",x+i,y+j);
            if(findCenter(x+i,y+j,&RXcenter, &RYcenter)) return true;
        }
    }
    return false;
}

bool clipImages::findDownBlock(int x, int y, int w, int h)
{
    for(int i=0; i<= w;i+=10)
    {
        for(int j=0; j <= h;j+=10)
        {
            //printf("Проверка точки: %d:%d\n",x+i,y+j);
            if(findCenter(x+i,y+j,&DXcenter, &DYcenter)) return true;
        }
    }
    return false;
}

bool clipImages::findCenter(int x0, int y0, int *x_center, int *y_center)
{
    unsigned int eq;
    int x_left, y_up, x_right, y_down;

    bool pr1, pr2, pr3, pr4;

    *x_center=0;
    *y_center=0;

    int delta = Properties::instance().sizeOfLabel + 2 * Properties::instance().deltaSize;
    int minSize = 50;//Properties::instance().sizeOfLabel - Properties::instance().deltaSize;
    int maxSize = 70;//Properties::instance().sizeOfLabel + Properties::instance().deltaSize;

    *bimg =img->convertToFormat(QImage::Format_Mono);
    eq = -1; //bimg->pixel(20,20);
    //printf("width=%d, height=%d\n",img->width(),img->height());


    //Проверка исходной точки
    if (bimg->pixel(x0,y0) == eq) return false;

    //найти левую границу
    pr1 = false;
    for(x_left = x0; x_left > (x0 - delta) ; x_left--)
    {
        if(bimg->pixel(x_left,y0) == eq)
        {
            ++x_left;
            pr1 = true;
            break;
        }
    }

    //найти верхнюю границу
    pr2 = false;
    for(y_up = y0; y_up > (y0 - delta) ; y_up--)
    {
        if(bimg->pixel(x0,y_up) == eq)
        {
            ++y_up;
            pr2 = true;
            break;
        }
    }

    //найти правую границу
    pr3 = false;
    for(x_right = x0; x_right < (x0 + delta) ; x_right++)
    {
        if(bimg->pixel(x_right,y0) == eq)
        {
            --x_right;
            pr3 = true;
            break;
        }
    }

    //найти нижнюю границу
    pr4 = false;
    for(y_down = y0; y_down < (y0 + delta) ; y_down++)
    {
        if(bimg->pixel(x0,y_down) == eq)
        {
            --y_down;
            pr4 = true;
            break;
        }
    }

    if((!pr1) || (!pr2) || (!pr3) || (!pr4))
    {
        //printf("Одна из границ блока не найдена!\n");
        return false;
    }

    if(y_down - y_up < minSize || y_down - y_up > maxSize || x_right - x_left < minSize || x_right - x_left > maxSize)
    {
        //printf("Размер отличный от стандарта! %d:%d\n",x_right - x_left,y_down - y_up);
        return false;
    }

    *x_center = x_left + (( x_right - x_left ) >> 1);
    *y_center = y_up + (( y_down - y_up ) >> 1);


    return true;

}

void clipImages::workImage()
{
    findLeftBlock(120,120,50,50);
    findRightBlock(img->width()-220,130,50,50);
    findDownBlock(img->width()-220,img->height()-260,50,50);
}

void clipImage()
{

}
