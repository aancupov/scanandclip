#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "vectorp.h"
#include <QString>

class algorithm
{
public:
    algorithm();
    //algorithm(QString filename, int n, int m);   //конструктор
    virtual ~algorithm();

    virtual void save(QString s);   //сохранить базу распознавания алгоритма

    virtual void study(QVector<int> *x, vectorP* vp);    //обучение алгоритма фрагментом изображения
    virtual vectorP *recognize(QVector<int> *x);         //распознавание алгоритмом фрагмента изображения


};

#endif // ALGORITHM_H
