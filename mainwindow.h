#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include "ui_mainwindow.h"
#include "goods.h"
#include "clipimages.h"
#include "selectimages.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void viewTable();

public slots:

    void slPrevImage();
    void slNextImage();
    void slViewString();

    void slViewTable(int);
    void slSaveXML();
    void slSum();

private:
    Ui::MainWindow *ui;
    Ui_MainWindow *form;
    QPainter      *mypainter;

    QGraphicsScene *sceneTochka;
    QGraphicsScene *sceneNuberList;
    QGraphicsScene *sceneForRecognise;
    QGraphicsScene *sceneItog;

    Goods *g;
    clipImages *ci;
    selectImages *selIm;

    QString currentImage;
    QString currentTochka;
    int sum;

    void loadImage();
    void viewString();
};

#endif // MAINWINDOW_H
