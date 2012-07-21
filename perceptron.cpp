#include "perceptron.h"

neuron::neuron(int m)
{
    weights = new QVector<float>(m);
}

neuron::neuron(QString v)
{
    QStringList numbers;
    numbers = v.split(";");
    if(numbers.size() > 1)
    {
        weights = new QVector<float>(numbers.size()-1);
        for(int i=0;i<numbers.size()-1;i++)
            weights->replace(i, numbers.at(i).toFloat());
    }
    else weights = new QVector<float>(1);
}


neuron::~neuron()
{
    delete weights;
}

//Передаточная функция
// x - входной вектор
// return - выходное значение нейрона
float neuron::transfer(QVector<int> *x)
{
    return activator(adder(x));
}

//Инициализация начальных весов синапсов
// небольшими случайными значениями
// n - от 0 до n
void neuron::initWeights(int n)
{
    for (int i = 0; i < weights->size(); i++)
    {
        weights->replace(i,rand()%n);
    }
}

//Модификация весов синапсов для обучения
// v - скорость обучения
// d - разница между выходом нейрона и нужным выходом
// x - входной вектор
void neuron::changeWeights(int v, float d, QVector<int> *x)
{
     for (int i = 0; i < weights->size(); i++)
     {
         weights->replace(i, weights->at(i) + v * d * (x->at(i)));
     }
}

//Сумматор
// x - входной вектор
// return - невзвешенная сумма nec (биас не используется)
float neuron::adder(QVector<int> *x)
{
    float nec = 0;
    for (int i = 0; i < x->size(); i++)
    {
        nec += x->at(i) * weights->at(i);

        //printf("x=%d w=%d x*w=%d\n",x->at(i),weights->at(i),x->at(i) * weights->at(i));
    }
    return nec;
}

//Нелинейный преобразователь или функция активации,
//в данном случае - жесткая пороговая функция,
//имеющая область значений {0;1}
// nec - выход сумматора
float neuron::activator(float nec)
{       //int threshold=50;
     //if (nec >= threshold) return 1;
     //if (nec >= threshold/2) return 0.7;
     //return 0;
    //printf("%5.2f -> %5.2f\n",nec,1./( 1 + pow(2.7182818, -nec)));
    return(1.0/( 1.0 + pow(2.7182818, -nec)));
}

//Cериализация объекта
QString neuron::serialization()
{
    QString s; // = new QString();
    s="";
    //printf("nser=%d\n",weights->size());
    for(int i=0;i<weights->size();i++)
        s += QString::number(weights->at(i))+";";
    return(s);
}

//-------------------------------------------------------------------------------------------------------
//Конструктор
// n - число нейронов
// m - число входов каждого нейрона скрытого слоя
/*perceptron::perceptron(int n, int m)
{
    this->n = n;
    this->m = m;
    neurons = new QVector<neuron*>(n);
    for (int j = 0; j < n; j++)
    {
        neurons->replace(j, new neuron(m));
    }
    initWeights();
}*/

//Конструктор
// namefile - файл с перцептроном
perceptron::perceptron(QString namefile, int n, int m)
{
    QString buf="";

    this->namefile = namefile;
    QFile file(namefile);
    if(file.open(QIODevice::ReadOnly))
    {
        QByteArray a = file.readAll();
        file.close();
        buf = QString::fromAscii(a);
    }
    else
    {
        this->n = n;
        this->m = m;
        neurons = new QVector<neuron*>(n);
        for (int j = 0; j < n; j++)
        {
            neurons->replace(j, new neuron(m));
        }
        initWeights();
        //printf("standart\n");
        return;
    }

    QStringList neuronsStr;
    neuronsStr = buf.split("#");
    this->m = m;
    if(neuronsStr.size() > 1)
    {
        this->n = neuronsStr.size()-1;
        neurons = new QVector<neuron*>(n);
        for(int i=0;i<n;i++)
        {
            neurons->replace(i, new neuron(neuronsStr.at(i)));
        }
    }
    else neurons = new QVector<neuron*>(1);

    //printf("buf=%s\n",qPrintable(buf));
}

//Деструктор
perceptron::~perceptron()
{
    for(int i=0;i<n;i++) delete neurons->at(i);
    delete neurons;
}

//Распознавание образа
// x - входной вектор
// return - выходной образ
vectorP* perceptron::recognize(QVector<int> *x)
{

    //for(int i=0;i<x->size();i++) printf("x[%d]=%d\n",i,x->at(i));

    vectorP *y = new vectorP(neurons->size());

    for (int j = 0; j < neurons->size(); j++)
    {
        //y->replace(j, neurons->at(j)->transfer(x));
        y->setP(j,neurons->at(j)->transfer(x));
    }

    return y;
}

//Инициализация начальных весов
//малым случайным значением
void perceptron::initWeights()
{
     for (int j = 0; j < neurons->size(); j++)
     {
         neurons->at(j)->initWeights(10);
     }
}

//Обучение перцептрона
// x - входной вектор
// y - правильный выходной вектор
void perceptron::study(QVector<int> *x, vectorP *y)
{
    float d;
    int v = 1; // скорость обучения

    vectorP *t = recognize(x);

    while (!equal(t, y))
    {
        // подстройка весов каждого нейрона
        for (int j = 0; j < neurons->size(); j++)
        {
            //d = y->at(j) - t->at(j);
            d = y->getP(j) - t->getP(j);
            neurons->at(j)->changeWeights(v, d, x);
        }
        t = recognize(x);
    }
    save();
}

//Сравнивание двух векторов
// a - первый вектор
// b - второй вектор
// return boolean
bool perceptron::equal(vectorP *a, vectorP *b)
{
    float razn;
    if (a->getN() != b->getN()) return false;
    for (int i = 0; i < a->getN(); i++)
    {
        razn = a->getP(i) - b->getP(i);
        if(razn < 0) razn = - razn;
        if (razn >= 0.001) return false;
    }
    return true;
}

int perceptron::getN()
{
    return n;
}

int perceptron::getM()
{
    return m;
}

//Сохранение перцептрона
// file - файл для хранения данных перцептрона
void perceptron::save()
{
    QString buf="";
    for(int i=0;i<neurons->size();i++)
        buf += neurons->at(i)->serialization() + "#";

    QFile file(namefile);
    if(file.open(QIODevice::WriteOnly))
    {
        file.write(qPrintable(buf));
        file.close();
    }

}
