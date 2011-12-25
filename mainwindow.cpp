#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QStringList lst;

    ui->setupUi(this);

    // Set main window content
    form = new Ui_MainWindow();
    form->setupUi( this );

    g = new Goods(Properties::instance().fileForExchange);
    ci = new clipImages();

    for(int i=0; i < g->listOfKeys.size(); i++)
    {
        form->tochka->addItem(g->listOfKeys.at(i));
    }

    //form->tableWidget->setRowCount(100);
    form->tableWidget->setColumnCount(3);
    form->tableWidget->setColumnWidth(0,50);
    form->tableWidget->setColumnWidth(1,400);
    form->tableWidget->setColumnWidth(2,50);

    currentTochka = "";
    viewTable();

    selIm = new selectImages(Properties::instance().path);
    printf("first=%s\n",qPrintable(selIm->firstJPG()));
    currentImage = selIm->firstJPG();
    loadImage();

    connect(form->tochka,SIGNAL(currentIndexChanged(int)),this,SLOT(slViewTable(int)));
    connect(form->btSaveXML, SIGNAL(clicked()), this, SLOT(slSaveXML()) );
    connect(form->tableWidget,SIGNAL(itemSelectionChanged())/* cellActivated(int,int))*/, this,SLOT(slSum()));

    // Open image
    connect( form->btPrev, SIGNAL(clicked()), this, SLOT(slPrevImage()) );
    connect( form->btNext, SIGNAL(clicked()), this, SLOT(slNextImage()) );
    connect( form->tableWidget, SIGNAL(itemSelectionChanged()), this, SLOT(slViewString()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete g;
}

void MainWindow::slPrevImage()
{
    currentImage = selIm->prevJPG();
    loadImage();
}

void MainWindow::slNextImage()
{
    currentImage = selIm->nextJPG();
    loadImage();
}

void MainWindow::slViewString()
{
    viewString();
}

void MainWindow::loadImage()
{
    if(ci->img->load(currentImage))
    {
        //img.save("2.jpg","JPG");
        ci->workImage();

        if(!sceneTochka) delete(sceneTochka);
        sceneTochka = new QGraphicsScene(this);
        sceneTochka->setSceneRect(ci->LXcenter+70,ci->LYcenter-10,350,90);
        sceneTochka->addPixmap(QBitmap::fromImage(*(ci->img)));

        if(!sceneNuberList) delete(sceneNuberList);
        sceneNuberList = new QGraphicsScene(this);
        sceneNuberList->setSceneRect(ci->RXcenter-720,ci->RYcenter-10,150,90);
        sceneNuberList->addPixmap(QBitmap::fromImage(*(ci->img)));

        if(!sceneItog) delete(sceneItog);
        sceneItog = new QGraphicsScene(this);
        sceneItog->setSceneRect(ci->DXcenter-390,ci->DYcenter-40,300,90);
        sceneItog->addPixmap(QBitmap::fromImage(*(ci->img)));

        form->sourceImage->setScene(sceneTochka);
        form->grItog->setScene(sceneItog);
        form->grListNumber->setScene(sceneNuberList);
        viewString();
    }
    else printf("Ошибка загрузки изображения!!!\n");
}

void MainWindow::viewString()
{
    int curX, curY;
    int curRow = form->tableWidget->currentRow();
    int inPage = curRow % 50;

    if(inPage/25 == 0)  // в левом столбце
        curX = ci->LXcenter+290;
    else                // в правом столбце
        curX = ci->LXcenter+1390;

    curY = ci->LYcenter+265+112*(inPage%25);

    if(!sceneForRecognise) delete(sceneForRecognise);
    sceneForRecognise = new QGraphicsScene(this);
    sceneForRecognise->setSceneRect(curX,curY,800,90);
    sceneForRecognise->addPixmap(QBitmap::fromImage(*(ci->img)));
    form->grForRecognise->setScene(sceneForRecognise);
}


void MainWindow::slViewTable(int ch)
{
    viewTable();
}

void MainWindow::viewTable()
{
    QTableWidgetItem* pqtwi = 0;
    QString t;
    int vgr;

    //Если не первая точка, то сохраним данные предыдущей точки
    t="";
    if(currentTochka != t)
    {

        vgr = (form->tableWidget->rowCount());
        for(int i=0; i < vgr; i++)
        {
            t=form->tableWidget->item(i,2)->text();
            g->update(currentTochka, form->tableWidget->item(i,0)->text().toInt(), form->tableWidget->item(i,2)->text().toInt());
            pqtwi = form->tableWidget->item(i,0);
            delete pqtwi;

        }
    }
    //Изменим текущую точку
    currentTochka = form->tochka->currentText();

    //...и загрузим в таблицу ее данные
    g->startWithFilter(currentTochka);

    form->tableWidget->setRowCount(g->sizeWithFilter());

    for(int i=0;g->next();i++)
    {
        t = QString::number(g->retCode());
        pqtwi = new QTableWidgetItem(t);
        pqtwi->setFlags(Qt::ItemIsEditable^2);
        form->tableWidget->setItem(i,0,pqtwi);

        pqtwi = new QTableWidgetItem(g->retName());
        pqtwi->setFlags(Qt::ItemIsEditable^2);
        form->tableWidget->setItem(i,1,pqtwi);

        t.sprintf("%d",g->retQuantity());
        pqtwi = new QTableWidgetItem(t);
        form->tableWidget->setItem(i,2,pqtwi);

    }
    form->tableWidget->show();
}

void MainWindow::slSaveXML()
{
    int vgr;

    vgr = (form->tableWidget->rowCount());
    for(int i=0; i < vgr; i++)
    {
        //t=form->tableWidget->item(i,2)->text();
        g->update(currentTochka, form->tableWidget->item(i,0)->text().toInt(), form->tableWidget->item(i,2)->text().toInt());
    }
    g->save(Properties::instance().fileForExchange);
}

void MainWindow::slSum()
{
    int vgr,pages,sum;
    int arSum[10];
    QString StringSum("");

    for(int i=0; i<10;i++) arSum[i]=0;
    vgr = (form->tableWidget->rowCount());
    pages = (vgr-1)/50+1;
    for(int i=0; i < vgr; i++)
    {
        arSum[i/50]+=form->tableWidget->item(i,2)->text().toInt();
    }
    sum=0;
    for(int i=0; i<pages;i++)
    {
        StringSum += QString("+")+QString::number(arSum[i]);
        sum+=arSum[i];
    }
    form->lbSum->setText(StringSum+QString("=")+QString::number(sum));
}
