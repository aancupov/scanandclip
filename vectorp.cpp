#include "vectorp.h"

vectorP::vectorP(int n)         //конструктор вектора вероятностей
{
    vectP = new QVector<float>(n);
    vectPs = new QVector<float>(n);
    this->n = n;
    for(int i=0;i<n;i++) vectP->replace(i,0.0f);
}

vectorP::~vectorP()             //деструктор
{
    delete vectP;
}

int vectorP::getN()             //размерность вектора
{
    return(n);
}

void vectorP::setP(int k, float valueP)       //установить значение вероятности k-го элемента вектора вероятностей
{
    if(k>=n) return;
    vectP->replace(k,valueP);
}

int vectorP::maxP()             //номер элемента вектора с максимальной вероятностью
{
    float mp=-1.0; int ret=-1;
    for(int i=0;i<n;i++)
        if(vectP->at(i) > mp)
        {
            ret=i;
            mp=vectP->at(i);
        }
    return(ret);
}

int vectorP::minP()             //номер элемента вектора с минимальной вероятностью
{
    float mp=1.1; int ret=-1;
    for(int i=0;i<n;i++)
        if(vectP->at(i) < mp)
        {
            ret=i;
            mp=vectP->at(i);
        }
    return(ret);
}

int vectorP::nP(int k)  //номер элемента вектора с вероятностью k-го рейтинга (max - 1-й рейтинг, min - n-й рейтинг, где n - размерность вектора
{
    for(int i=0;i<n;i++) vectPs->replace(i,vectP->at(i));
    sort(vectPs);
    for(int i=0;i<n;i++)
        if(vectP->at(i)==vectPs->at(k))
            return(i);
}

float vectorP::valueOfmaxP()    //значение максимальной вероятности
{
    float mp=-1.0; int ret=-1;
    for(int i=0;i<n;i++)
        if(vectP->at(i) > mp)
        {
            ret=i;
            mp=vectP->at(i);
        }
    return(mp);
}

float vectorP::valueOfminP()    //значение минимальной вероятности
{
    float mp=1.1; int ret=-1;
    for(int i=0;i<n;i++)
        if(vectP->at(i) < mp)
        {
            ret=i;
            mp=vectP->at(i);
        }
    return(mp);
}

float vectorP::valueOfnP(int k) //значение вероятности k-го рейтинга
{
    for(int i=0;i<n;i++) vectPs->replace(i,vectP->at(i));
    sort(vectPs);
    return(vectPs->at(k));
}

void vectorP::sort(QVector<float>* v) //сортировка вектора вероятностей
{
    qSort(*v);
}

float vectorP::getP(int k)
{
    return(vectP->at(k));
}

void vectorP::add(vectorP* v)   //сложение векторов вероятностей
{
    if(v->getN() != n) return;
    for(int i=0;i<n;i++) vectP->replace(i,(vectP->at(i) + v->getP(i)) / 2);
}

void vectorP::prn(int s)    //вывод значений элемнтов вектоар в консоль
{
    if(s)
        //for(int i=0;i<n;i++) printf("p[%d]=%5.3f ",i,vectPs->at(i));
        for(int i=0;i<n;i++) printf("%5.3f ",vectPs->at(i));
    else
        //for(int i=0;i<n;i++) printf("p[%d]=%5.3f ",i,vectP->at(i));
        for(int i=0;i<n;i++) printf("%5.3f ",vectP->at(i));
    printf("\n");
}
