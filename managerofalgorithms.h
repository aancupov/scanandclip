#ifndef MANAGEROFALGORITHMS_H
#define MANAGEROFALGORITHMS_H

#include <QImage>
#include <QVector>
#include "algorithm.h"
#include "vectorp.h"
#include "perceptron.h"
#include "properties.h"

class managerOfAlgorithms
{
public:
    managerOfAlgorithms(QImage *im);   //конструктор
    ~managerOfAlgorithms();  //деструктор


    void study(int x, int y, int w, int h, QString dig);  //обучить алгоритмы фрагментом изображения
    QString recognize(int x, int y, int w, int h);        //распознать фрагмент изображения с точностью до символа

private:
    QVector<algorithm*> *algorithms;
    QImage *im;

    void addAlgorithms(algorithm *alg);                  //добавить алгоритм для распознавания
    bool isBlack(int x, int y);                          //точка является черной
};

#endif // MANAGEROFALGORITHMS_H
