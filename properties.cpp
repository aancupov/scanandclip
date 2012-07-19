#include "properties.h"

Properties Properties::sInstance;

Properties::Properties()
{
    sizeOfLabel = 40;
    deltaSize   = 5;

    //fieldUpLeft = new Field();
    //fieldUpRight = new Field();
    //fieldDownLeft = new Field();

    path = QString("/home/andrew/all/export/");
    fileForExchange = path + "obmen.xml"; //c:\\export\\obmen.xml";
    fileForBaseRecognise = path + "baserec.xml"; //c:\\export\\obmen.xml";
    fileForPerceptron = path + "perceptron.xml";

}

Properties& Properties::instance()
{
    return(sInstance);
}
