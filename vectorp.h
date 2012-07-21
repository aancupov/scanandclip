#ifndef VECTORP_H
#define VECTORP_H

#include <QVector>
#include <QtAlgorithms>
#include "stdio.h"

class vectorP
{
public:
    vectorP(int n);         //конструктор вектора вероятностей
    ~vectorP();             //деструктор

    int getN();             //размерность вектора

    void setP(int k, float valueP); //установить значение вероятности k-го элемента вектора вероятностей

    int maxP();             //номер элемента вектора с максимальной вероятностью
    int minP();             //номер элемента вектора с минимальной вероятностью
    int nP(int k);          //номер элемента вектора с вероятностью k-го рейтинга (max - n-й рейтинг, min - 1-й рейтинг, где n - размерность вектора

    float valueOfmaxP();    //значение максимальной вероятности
    float valueOfminP();    //значение минимальной вероятности
    float valueOfnP(int k); //значение вероятности k-го рейтинга

    float getP(int k);      //получить значение k-го элемента вектора
    void add(vectorP* v);   //сложение векторов вероятностей

    void prn(int s);         //вывод значений элементов вектора в консоль

private:
    QVector<float> *vectP;  //сам вектор вероятностей
    QVector<float> *vectPs; //вектор вероятностей для сортировки
    int n;                  //и его размерность
    void sort(QVector<float> *v); //сортировка вектора вероятностей
};

#endif // VECTORP_H
