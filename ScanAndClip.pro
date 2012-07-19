#-------------------------------------------------
#
# Project created by QtCreator 2011-10-28T15:05:55
#
#-------------------------------------------------

QT       += core gui \
         += xml

TARGET = ScanAndClip
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    field.cpp \
    properties.cpp \
    goods.cpp \
    clipimages.cpp \
    selectimages.cpp \
    ../../QtSDK/testBaseRecognise/baserecognise.cpp \
    ../../QtSDK/testPerceptron/perceptron.cpp \
    ../../QtSDK/testPerceptron/neuron.cpp

HEADERS  += mainwindow.h \
    field.h \
    properties.h \
    goods.h \
    clipimages.h \
    selectimages.h \
    ../../QtSDK/testBaseRecognise/baserecognise.h \
    ../../QtSDK/testPerceptron/neuron.h \
    ../../QtSDK/testPerceptron/perceptron.h

FORMS    += mainwindow.ui















