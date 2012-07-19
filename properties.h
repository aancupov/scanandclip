#ifndef PROPERTIES_H
#define PROPERTIES_H

#include <QString>
#include "field.h"

class Properties
{
public:
    static Properties& instance();

    int sizeOfLabel,
        deltaSize;

    Field   *fieldUpLeft,
            *fieldUpRight,
            *fieldDownLeft;

    QString  fileForExchange;
    QString  fileForBaseRecognise;
    QString  fileForPerceptron;
    QString  path;

protected:
    static Properties sInstance;

private:
    Properties();
};

#endif // PROPERTIES_H
