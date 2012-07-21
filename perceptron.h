#ifndef PERCEPTRON_H
#define PERCEPTRON_H

#include <QFile>
#include <stdio.h>
#include <math.h>
#include <QVector>
#include <QString>
#include <QStringList>
#include "vectorp.h"
#include "algorithm.h"

class neuron
{
public:
    neuron(int sizeVector);                                 //конструктор, где sizeVector - размерность входного сигнала
    neuron(QString vector);                                 //конструктор, где Vector - вектор весов
    ~neuron();                                              //деструктор
    float transfer(QVector<int> *x);                        //передаточная функция
    void initWeights(int n);                                //инициализация начальных весов
    void changeWeights(int v, float d, QVector<int> *x);    //изменение весов при обучении, где v - скорость обучения
                                                                                      //d - разница между выходом нейрона и целевым выходом
                                                                                      //x - входной вектор
    QString serialization();                                //возвращает строку сериализованного объекта

private:
    QVector<float> *weights;                                //веса синапсов
    //int threshold;                                        //порог
    float adder(QVector<int> *x);                           //сумматор
    float activator(float nec);                             //нелинейный преобразователь, где nec - выход сумматора
};


class perceptron : public algorithm
{
public:
    //Конструктор
    // n - число нейронов
    // m - число входов каждого нейрона скрытого слоя
    //perceptron(int n, int m);

    //Конструктор
    // namefile - файл с перцептроном
    // n - число нейронов
    // m - число входов каждого нейрона скрытого слоя
    perceptron(QString namefile, int n, int m);

    //Деструктор
    ~perceptron();

    //Распознавание образа
    // x - входной вектор
    // return - выходной образ
    vectorP* recognize(QVector<int> *x);

    //Обучение перцептрона
    // x - входной вектор
    // y - правильный выходной вектор
    void study(QVector<int> *x, vectorP *y);

    //Обучение перцептрона
    // x - входной вектор
    // dig - текстовое представление цифры
    void study(QVector<int> *x, QString dig);

    int getN();
    int getM();

private:
    //Данные
    int n; //размерность вектора вероятностей
    int m; //размерность входного вектора
    QVector<neuron*> *neurons;  //Множество нейронов
    QString namefile; //файл для хранения базы

    //Инициализация начальных весов
    //малым случайным значением
    void initWeights();

    //Сравнивание двух векторов
    // a - первый вектор
    // b - второй вектор
    // return bool
    bool equal(vectorP *a, vectorP *b);

    //Сохранение перцептрона
    // file - файл для хранения данных перцептрона
    void save();

};

#endif // PERCEPTRON_H
