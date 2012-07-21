#include "managerofalgorithms.h"

managerOfAlgorithms::managerOfAlgorithms(QImage *im)   //конструктор
{
    this->im = im;
    algorithms = new QVector<algorithm*>();
    perceptron* perc = new perceptron(Properties::instance().fileForPerceptron,10,90*67);
    algorithms->append((algorithm*) perc);
}

managerOfAlgorithms::~managerOfAlgorithms()  //деструктор
{
    delete algorithms->at(0);
    delete algorithms;
}

void managerOfAlgorithms::addAlgorithms(algorithm *alg) //добавить алгоритм для распознавания
{
    algorithms->append(alg);
}

void managerOfAlgorithms::study(int x, int y, int w, int h, QString dig) //обучить алгоритмы фрагментом изображения
{
    algorithm* alg;

    vectorP* vp = new vectorP(10);
    if(dig=="0") vp->setP(0,1.0f);
    if(dig=="1") vp->setP(1,1.0f);
    if(dig=="2") vp->setP(2,1.0f);
    if(dig=="3") vp->setP(3,1.0f);
    if(dig=="4") vp->setP(4,1.0f);
    if(dig=="5") vp->setP(5,1.0f);
    if(dig=="6") vp->setP(6,1.0f);
    if(dig=="7") vp->setP(7,1.0f);
    if(dig=="8") vp->setP(8,1.0f);
    if(dig=="9") vp->setP(9,1.0f);

    QVector<int> *inpx = new QVector<int>(w*h);
    for(int i=0;i<w;i++)
    {
        for(int j=0;j<h;j++)
        {
            if(isBlack(x+i,y+j)) inpx->replace(i*h+j,1);
            else inpx->replace(i*h+j,0);
        }
    }
    for(int i=0;i<algorithms->size();i++)
        algorithms->at(i)->study(inpx, vp);
}

QString managerOfAlgorithms::recognize(int x, int y, int w, int h)        //распознать фрагмент изображения с точностью до символа
{
    QVector<int> *inpx = new QVector<int>(w*h);
    for(int i=0;i<w;i++)
    {
        for(int j=0;j<h;j++)
        {
            if(isBlack(x+i,y+j)) inpx->replace(i*h+j,1);
            else inpx->replace(i*h+j,0);
        }
    }

    vectorP *p = algorithms->at(0)->recognize(inpx);
    for(int i=1;i<algorithms->size();i++) p->add(algorithms->at(i)->recognize(inpx));
    float razn = p->valueOfmaxP()- p->valueOfminP();
    if(razn < 0) razn = -razn;
    if(razn < 0.001f) return("");
    return(QString('0'+p->maxP()));
}

bool managerOfAlgorithms::isBlack(int x, int y)
{
    return(im->pixel(x,y) != -1); //текущая точка - черная

}
