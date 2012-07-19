#include "clipimages.h"

clipImages::clipImages()
{
    img = new QImage();
    bimg = new QImage();
    brec = new baseRecognise(Properties::instance().fileForBaseRecognise);
    brec->load();

    perc = new perceptron(Properties::instance().fileForPerceptron,10,90*67);
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

bool clipImages::isBlack(int x, int y)
{
    return(bimg->pixel(x,y) != -1); //текущая точка - черная

}

QString clipImages::norma(QString rez, bool vert)
{
    QString rez1="",rez2="";
    bool pr;

    //printf("rezzz=%s\n",qPrintable(rez));
    pr=true;
    for(int i = 0; i < rez.count(); i++)
    {
        if(pr && rez.at(i)=='0') continue;
        pr = false;
        if(rez.at(i) == '0') rez1+="0";
        else if(rez.at(i) == '1') rez1 += "1";
        else rez1 += "2";
    }
    pr=true;
    for(int i = rez1.count()-1; i >= 0 ; i--)
    {
        if(pr && rez1.at(i)=='0') continue;
        pr = false;
        if(rez1.at(i) == '0') rez2+="0";
        else if(rez1.at(i) == '1') rez2 += "1";
        else rez2 += "2";
    }

    if(vert)
    {
        if(rez2 == "1") return("A");
        if(rez2 == "2") return("B");

        if(rez2 == "101") return("C");
        if(rez2 == "102") return("D");
        if(rez2 == "202") return("E");

        if(rez2 == "10102") return("F");
        if(rez2 == "10202") return("G");

        if(rez2 == "1010202") return("H");
        return("");
    }
    else
    {
        if(rez2 == "1") return("S");
        if(rez2 == "2") return("T");

        if(rez2 == "101") return("U");
        if(rez2 == "102") return("V");
        if(rez2 == "202") return("W");

        if(rez2 == "10102") return("X");
        if(rez2 == "10202") return("Y");

        if(rez2 == "1010202") return("Z");
        return("");
    }
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

QString clipImages::recognise(int x, int y, int w, int h)
{
    int minx=0, miny=0, ww=0, hh=0;
    QString s="", rec="";

    ww=w/3;
    QVector<int> *inv = new QVector<int>(ww*h);

    //Первая цифра
    //printf("%s\n",qPrintable(digital(x, y, w/3, h)));
    minx=0, miny=0, ww=0, hh=0;
    //quoter(x,y,w/3,h,&minx,&miny,&ww,&hh);
    //s = normalDigit(minx, miny, ww, hh);
    //if(s=="")
        //rec =  brec->recognise(digital(minx, miny, ww, hh));
    //else rec = s;
    for(int i=0;i<ww;i++)
    {
        for(int j=0;j<h;j++)
        {
            if(isBlack(x+i,y+j)) inv->replace(i*h+j,1);
            else inv->replace(i*h+j,0);
        }
    }
    QVector<float>* rez = perc->recognize(inv);
    int maxd=-1; float maxp=0.0;
    printf("=================\n");
    for(int i=0;i<10;i++)
    {
        if(rez->at(i) > maxp)
        {
            maxp=rez->at(i);
            maxd=i;
        }
        printf("%5.3f %5.3f",maxp,rez->at(i));
    }
    printf("\n");
    if(maxd > -1) rec=QString('0'+maxd);
    else rec="";
    return(rec);

    //Вторая цифра
    //printf("%s\n",qPrintable(digital(x+w/3, y, w/3, h)));
    minx=0, miny=0, ww=0, hh=0;
    quoter(x+w/3,y,w/3,h,&minx,&miny,&ww,&hh);
    //s = normalDigit(minx, miny, ww, hh);
    //if(s=="")
        rec += brec->recognise(digital(minx, miny, ww, hh));
    //else rec += s;

    //Третья цифра
    //printf("%s\n",qPrintable(digital(x+2*w/3, y, w/3, h)));
    minx=0, miny=0, ww=0, hh=0;
    quoter(x+2*w/3,y,w/3,h,&minx,&miny,&ww,&hh);
    //s = normalDigit(minx, miny, ww, hh);
    //if(s=="")
    rec += brec->recognise(digital(minx, miny, ww, hh));
    //else rec += s;
    printf("dig = %s\n",qPrintable(s));
    return(rec);
}

QString clipImages::normalDigit(int x, int y, int w, int h)
{
    int a[8]={0,0,0,0,0,0,0,0}, med=0, min, max, minproc, min1, minproc1;

    if(w > 0)
    {  if(h/w > 3) return("1*");
    }

    if(h > 0)
    {  if(w/h > 3) return("0*");
    }

    for(int i=x;i<x+w;i++)
    {
        for(int j=y;j<y+h;j++)
        {
            if(isBlack(i,j)) ++a[minr(i,j,x,y,w,h)];
        }
    }

    for(int i=0; i<7; i++) med+=a[i];
    if(med <= 10) return("");
    min = 0; minproc = a[0]*100/med;
    max = 0;
    for(int i=1; i<7; i++)
    {
        if(a[i] < a[min])
        {
            min = i;
            minproc = a[i]*100/med;
        }
        if(a[i] > a[max]) max = i;
    }
    min1 = max; minproc1=100;
    for(int i=0; i<7; i++)
    {
        if(i==min) continue;
        if(a[i] < a[min1])
        {
            min1 = i;
            minproc1 = a[i]*100/med;
        }
    }

    if(min==0 && minproc < 3 && min1==3 && minproc1 < 3 || min==3 && minproc < 3 && min1==0 && minproc1 < 3) return("2*");
    if(min==0 && minproc < 3 && min1==5 && minproc1 < 3 || min==5 && minproc < 3 && min1==0 && minproc1 < 3) return("3*");
    if(min==1 && minproc < 3 && min1==4 && minproc1 < 3 || min==4 && minproc < 3 && min1==1 && minproc1 < 3) return("4*");
    if(min==1 && minproc < 3 && min1==5 && minproc1 < 3 || min==5 && minproc < 3 && min1==1 && minproc1 < 3) return("4*");
    if(min==4 && minproc < 3 && min1==5 && minproc1 < 3 || min==5 && minproc < 3 && min1==4 && minproc1 < 3) return("4*");
    if(min==2 && minproc < 3 && min1==5 && minproc1 < 3 || min==5 && minproc < 3 && min1==2 && minproc1 < 3) return("5*");
    if(min==2 && minproc < 3) return("6*");
    if(min==5 && minproc < 3) return("9*");
    if(min==6 && minproc < 3) return("0*");
    if(min==0 && minproc < 3 && min1==4 && minproc1 < 3 || min==4 && minproc < 3 && min1==0 && minproc1 < 3) return("7*");
    if(minproc >= 3 ) return("8*");
    return("");
}

int clipImages::minr(int i, int j, int x, int y, int w, int h)
{
    int ra, rb, rc, rd, re, rf, rg;

    if(j-y < h/2)  //верхняя половина
    {
        ra = i-x;
        rb = j-y;
        rc = x+w-i;
        rg = y+h/2-j;
        if(ra < rb && ra < rc && ra < rg) return(0);
        if(rb < ra && rb < rc && rb < rg) return(1);
        if(rc < ra && rc < rb && rc < rg) return(2);
        if(rg < ra && rg < rb && rg < rc) return(6);
        return(7);
    }
    else           //нижняя половина
    {
        rf = i-x;
        rg = j-(y+h/2);
        rd = x+w-i;
        re = y+h-j;
        if(rf < rg && rf < rd && rf < re) return(5);
        if(rg < rf && rg < rd && rg < re) return(6);
        if(rd < rg && rd < rf && rd < re) return(3);
        if(re < rg && re < rd && re < rf) return(4);
        return(7);
    }
}

void clipImages::study(int x, int y, int w, int h, QString digits3)
{
    int minx=0, miny=0, ww=0, hh=0;
    ww=w/3;
    QVector<int> *inv = new QVector<int>(ww*h);
    printf("digs=%s\n",qPrintable(digits3));
    //Первая цифра
    if(digits3.size()>0)
    {
        //printf("%s\n",qPrintable(digital(x, y, w/3, h)));
        /*minx=0, miny=0, ww=0, hh=0;
        quoter(x,y,w/3,h,&minx,&miny,&ww,&hh);
        brec->study(digital(minx, miny, ww, hh), QString(digits3.at(0)));*/
        printf("blok1\n");
        for(int i=0;i<ww;i++)
        {
            for(int j=0;j<h;j++)
            {
                if(isBlack(x+i,y+j)) inv->replace(i*h+j,1);
                else inv->replace(i*h+j,0);
            }
        }
        //for(int i=0;i<50;i++)
        perc->study(inv,QString(digits3.at(0)));
    }
    //Вторая цифра
    if(digits3.size()>1)
    {
        //printf("%s\n",qPrintable(digital(x+w/3, y, w/3, h)));
        /*minx=0, miny=0, ww=0, hh=0;
        quoter(x+w/3,y,w/3,h,&minx,&miny,&ww,&hh);
        brec->study(digital(minx, miny, ww, hh), QString(digits3.at(1)));*/
        for(int i=0;i<ww;i++)
        {
            for(int j=0;j<h;j++)
            {
                if(isBlack(x+ww+i,y+j)) inv->replace(i*h+j,1);
                else inv->replace(i*h+j,0);
            }
        }
        //for(int i=0;i<50;i++)
            perc->study(inv,QString(digits3.at(1)));
    }
    //Третья цифра
    if(digits3.size()>2)
    {
        //printf("%s\n",qPrintable(digital(x+2*w/3, y, w/3, h)));
        /*minx=0, miny=0, ww=0, hh=0;
        quoter(x+2*w/3,y,w/3,h,&minx,&miny,&ww,&hh);
        brec->study(digital(minx, miny, ww, hh), QString(digits3.at(2)));*/
        for(int i=0;i<ww;i++)
        {
            for(int j=0;j<h;j++)
            {
                if(isBlack(x+2*ww+i,y+j)) inv->replace(i*h+j,1);
                else inv->replace(i*h+j,0);
            }
        }
        //for(int i=0;i<50;i++)
            perc->study(inv,QString(digits3.at(2)));

    }
    //brec->save();
    perc->save(Properties::instance().fileForPerceptron);
    printf("---------------\n");
}

QString clipImages::digital(int x, int y, int w, int h)
{
    QString rez="",     //линия результата
            pred="",    //результат предыдущего перехода 0 или 1
            prstr="",   //предыдущая линия результата
            dig="";     //результирующий код

    printf("============цифра = %s %d %d %d %d\n",qPrintable(rez),x,y,w,h);
    // Обработаем по вертикали
    for(int i=x; i <= x+w; i++)
    {
        rez=""; pred="0";
        for(int j = y; j <= y+ h-4; )
        {
            if(isBlack(i,j)) //текущая точка - черная
            {
                if(isBlack(i,j+1) && isBlack(i,j+2) && isBlack(i,j+3)) //и следующие две(три) точки - черные
                {
                    j += 4;
                    if(pred == "0") //смена белой на черную
                    {
                        if(j-y > (h/2)) pred = "2";
                        else pred = "1";
                        rez += pred;
                    }
                }
                else ++j; // следующие точки - белые

            }
            else //текущая точка - белая
            {
                if((!isBlack(i,j+1)) && (!isBlack(i,j+2)) && (!isBlack(i,j+3))) //и следующие две точки - белые
                {
                    j += 4;
                    if(pred != "0") //смена черной на белую
                    {
                        pred = "0";
                        rez += "0";
                    }
                }
                else ++j; // следующие точки - черные
            }
        }
        //printf("vert rezzz=%s\n",qPrintable(rez));
        rez = norma(rez, true);
        if(prstr != rez && rez != "")
        {
            printf("rez = %s\n",qPrintable(rez));
            dig += rez;
            prstr = rez;
        }
    }
    //printf("===по горизонтали:\n");
    // Обработаем по горизонтали
    for(int j=y; j <= y+h; j++)
    {
        rez=""; pred="0";
        for(int i = x; i <= x+ w-4; )
        {
            if(isBlack(i,j)) // текущая точка черная
            {
                if(isBlack(i+1,j) && isBlack(i+2,j) && isBlack(i+3,j)) // следующие две точки черные
                {
                    i += 4;
                    if(pred == "0")  // смена белой на черную
                    {
                        if(i-x>(w/2)) pred = "2";
                        else pred = "1";
                        rez += pred;
                    }
                }
                else ++i; // следующие две точки нечерные
            }
            else // текущая точка белая
            {
                if((!isBlack(i+1,j)) && (!isBlack(i+2,j)) && (!isBlack(i+3,j))) //и следующие две точки - белые
                {
                    i += 4;
                    if(pred != "0") //смена черой на белую
                    {
                        pred = "0";
                        rez += "0";
                    }
                }
                else ++i; // следующие точки - черные
            }
        }
        //printf("hor rezzz=%s\n",qPrintable(rez));
        rez = norma(rez, false);
        if(prstr != rez && rez != "")
        {
            printf("rez = %s\n",qPrintable(rez));
            dig += rez;
            prstr = rez;
        }
    }
    printf("============конец цифры ==========\n");
    return(dig);
}

void clipImages::quoter(int x, int y, int w, int h, int *x1, int *y1, int *w1, int *h1)
{
    int minx=x+w,miny=y+h,maxx=x,maxy=y;

    for(int i=x;i<x+w-2;i++)
    {
        for(int j=y;j<y+h-2;j++)
        {
            if(isBlack(i,j) && isBlack(i+1,j) && isBlack(i+2,j) && isBlack(i,j+1) && isBlack(i,j+2))
            {
                if(minx > i) minx=i;
                if(maxx < i) maxx=i;
                if(miny > j) miny=j;
                if(maxy < j) maxy=j;
            }
        }
    }

    *x1=minx; *y1=miny; *w1=maxx-minx+2; *h1=maxy-miny+2;
}
