#include "goods.h"
#include "properties.h"

bool Goods::inKeys(QString key)
{
    for(int i=0;i<listOfKeys.size();i++)
    {
        if(key == listOfKeys.at(i)) return true;
    }
    return false;
}

void Goods::traverseNode(const QDomNode& node)
{
    QDomNode domNode = node.firstChild();

    while(!domNode.isNull())
    {
        if(domNode.isElement())
        {
            QDomElement domElement = domNode.toElement();

            if(!domElement.isNull())
            {
                if(domElement.nodeName() == "block")
                {
                    if(firstBlock)
                    {
                        firstBlock = false;
                    }
                    else
                    {
                        Goods::listOfGoods.append(sg);
                        sg.code=0;
                        sg.name="";
                        sg.quantity=0;
                        sg.tochka="";
                    }
                }
                if(domElement.nodeName() == "tochka")
                {
                    sg.tochka = domElement.text();
                    if(!inKeys(sg.tochka)) listOfKeys.append(sg.tochka);
                }
                if(domElement.nodeName() == "code")
                {
                    sg.code = domElement.text().toInt();
                }
                if(domElement.nodeName() == "goods")
                {
                    sg.name = domElement.text();
                }
                if(domElement.nodeName() == "quantity")
                {
                    sg.quantity = domElement.text().toInt();
                }

            }
        }
        traverseNode(domNode);
        domNode = domNode.nextSibling();
    }
}

Goods::Goods(QString& xmlFile)
{
    QDomDocument domDoc;
    QFile file(xmlFile);
    QString err;

    firstBlock = true;
    printf("xmlFile: %s\n",qPrintable(xmlFile));

    if(file.open(QIODevice::ReadOnly))
    {
        if(domDoc.setContent(&file, &err))
        {
            QDomElement domElement = domDoc.documentElement();
            traverseNode(domElement);
        }
        else printf("Ошибка domCom: %s\n",qPrintable(err));
        file.close();
    }
    else printf("Ошибка чтения: %s\n",qPrintable(file.errorString()));
    size = listOfGoods.size();
    printf("При создании:%d\n",size);
}

Goods::~Goods()
{
    listOfKeys.clear();
    listOfGoods.clear();
}

bool Goods::save(QString& xmlFile)
{
    /*QString exp = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n";
    exp+="<root>\r\n";
    for(int i=0; i<size; i++)
    {
        exp+="<block>\r\n";
        exp+="<tochka>"+listOfGoods.at(i).tochka+"</tochka>\r\n";
        exp+="<code>"+QString::number(listOfGoods.at(i).code)+"</code>\r\n";
        exp+="<goods>"+listOfGoods.at(i).name+"</goods>\r\n";
        exp+="<quantity>"+QString::number(listOfGoods.at(i).quantity)+"</quantity>\r\n";
        exp+="</block>\r\n";
    }
    exp+="<block/>\r\n";
    exp+="</root>\r\n";*/
    QDomDocument xmlDoc("");
    QDomElement root = xmlDoc.createElement("root");
    for(int i=0; i<size; i++)
    {
        QDomElement block = xmlDoc.createElement("block");

        QDomElement tochka = xmlDoc.createElement("tochka");
        QDomText tochkatext = xmlDoc.createTextNode(listOfGoods.at(i).tochka);
        tochka.appendChild(tochkatext);
        block.appendChild(tochka);

        QDomElement code = xmlDoc.createElement("code");
        QDomText codetext = xmlDoc.createTextNode(QString::number(listOfGoods.at(i).code));
        code.appendChild(codetext);
        block.appendChild(code);

        QDomElement goods = xmlDoc.createElement("goods");
        QDomText goodstext = xmlDoc.createTextNode(listOfGoods.at(i).name);
        goods.appendChild(goodstext);
        block.appendChild(goods);

        QDomElement quantity = xmlDoc.createElement("quantity");
        QDomText quantitytext = xmlDoc.createTextNode(QString::number(listOfGoods.at(i).quantity));
        quantity.appendChild(quantitytext);
        block.appendChild(quantity);

        root.appendChild(block);
    }
    QDomElement block = xmlDoc.createElement("block");
    root.appendChild(block);

    xmlDoc.appendChild(root);

    QString exp = xmlDoc.toString();

    QFile file(xmlFile);
    if(file.open(QIODevice::WriteOnly))
    {
        file.write(qPrintable(exp));
        file.close();
    }
    printf("При сохранении:%d\n",size);
    printf("При сохранении:%d\n",size);
    printf("При сохранении:%d\n",size);
    printf("При сохранении:%d\n",size);
    printf("При сохранении:%d\n",size);
    printf("При сохранении:%d\n",size);
}

void Goods::startWithFilter(QString tochka)
{
    current = -1;
    filter = tochka;
}

int Goods::retCode()
{
    if(current >= 0 && current < size)
        return(listOfGoods.at(current).code);
    else return(-1);
}

QString Goods::retName()
{
    if(current >= 0 && current < size)
        return(listOfGoods.at(current).name);
    else return("");
}

int Goods::retQuantity()
{
    if(current >= 0 && current < size)
        return(listOfGoods.at(current).quantity);
    else return(-1);
}

bool Goods::next()
{
    int i;

    for(i = current+1 ;i<size;i++)
    {
        if(listOfGoods.at(i).tochka==filter)
        {
            current = i;
            return true;
        }
    }
    return false;
}

int Goods::sizeWithFilter()
{
    int i,swf=0;

    for(i = 0; i < size; i++)
    {
        if(listOfGoods.at(i).tochka==filter) ++swf;
    }
    return(swf);
}

void Goods::update(QString tochka, int code, int quantity)
{
    QString name;
    int i;

    for(i=0;i < size; i++)
    {
        if(listOfGoods.at(i).tochka==tochka && listOfGoods.at(i).code == code)
        {
            name = listOfGoods.at(i).name;
            listOfGoods.removeAt(i);
            size=listOfGoods.size();
            break;
        }
    }
    sg.code = code;
    sg.tochka = tochka;
    sg.name = name;
    sg.quantity = quantity;
    listOfGoods.insert(i,sg);
    size=listOfGoods.size();
}
