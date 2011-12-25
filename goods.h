#ifndef GOODS_H
#define GOODS_H

#include <QList>
#include <QFile>
#include <QDomDocument>
#include "goods.h"

class StrOfGoods
{
public:
    QString tochka;
    int code;
    QString name;
    int quantity;

};

class Goods
{
public:

    QList<QString> listOfKeys;

    Goods(QString& xmlFile);
    ~Goods();

    bool save(QString& xmlFile);

    void startWithFilter(QString tochka);
    int retCode();
    QString retName();
    int retQuantity();
    bool next();
    int sizeWithFilter();
    void update(QString tochka, int code, int quantity);

private:
    QList<StrOfGoods> listOfGoods;
    bool inKeys(QString keyword);
    void traverseNode(const QDomNode& node);
    bool firstBlock;
    StrOfGoods sg;
    int size;
    int current;
    QString filter;
};

#endif // GOODS_H
