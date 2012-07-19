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

    connect( form->btRecognize, SIGNAL(clicked()), this, SLOT(slRecognise()) );
    connect( form->btStudy, SIGNAL(clicked()), this, SLOT(slStudy()));

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

void MainWindow::slRecognise()
{
    int curX, curY;
    int curRow = form->tableWidget->currentRow();
    int inPage = curRow % 50;
    int page = curRow / 50;

    for(; curRow < form->tableWidget->rowCount(); curRow++)
    {
        if(curRow/50 > page) break;
        inPage = curRow % 50;
        printf("-------------------------\n");
        printf("%s\n",qPrintable(form->tableWidget->item(curRow,2)->text()));
    if(inPage/25 == 0)  // в левом столбце
    {
        curX = ci->LXcenter+300;
        curY = ci->LYcenter+(ci->DYcenter - ci->LYcenter)*45/500 + (ci->DYcenter - ci->LYcenter)*445/500/25 * (inPage%25);
    }
    else                // в правом столбце
    {
        curX = ci->LXcenter+1390;
        curY = ci->RYcenter+(ci->DYcenter - ci->RYcenter)*45/500 + (ci->DYcenter - ci->RYcenter)*445/500/25 * (inPage%25);
    }

    if(!sceneForRecognise) delete(sceneForRecognise);
    sceneForRecognise = new QGraphicsScene(this);
    sceneForRecognise->setSceneRect(curX,curY,800,90);
    sceneForRecognise->addPixmap(QBitmap::fromImage(*(ci->img)));
    form->grForRecognise->setScene(sceneForRecognise);

    //int minx=0, miny=0, w=0, h=0;
    //ci->quoter(curX+550,curY,200/3,90,&minx,&miny,&w,&h);

    form->tableWidget->item(curRow,2)->setText(ci -> recognise(curX+550, curY, 201, 90));
    //form->tableWidget->item(curRow,2)->setText(ci -> recognise(minx, miny, w, h));
    }
    viewString();
}

void MainWindow::slStudy()
{
    int curX, curY;
    int curRow = form->tableWidget->currentRow();
    int inPage = curRow % 50;

    if(inPage/25 == 0)  // в левом столбце
    {
        curX = ci->LXcenter+300;
        curY = ci->LYcenter+(ci->DYcenter - ci->LYcenter)*45/500 + (ci->DYcenter - ci->LYcenter)*445/500/25 * (inPage%25);
    }
    else                // в правом столбце
    {
        curX = ci->LXcenter+1390;
        curY = ci->RYcenter+(ci->DYcenter - ci->RYcenter)*45/500 + (ci->DYcenter - ci->RYcenter)*445/500/25 * (inPage%25);
    }


    /*for(int i=0;i<w;i++)
        ci->img->setPixel(minx+i, miny, 1);
    for(int i=0;i<w;i++)
        ci->img->setPixel(minx+i, miny+h, 1);
    for(int i=0;i<h;i++)
        ci->img->setPixel(minx, miny+i, 1);
    for(int i=0;i<h;i++)
        ci->img->setPixel(minx+w, miny+i, 1);*/

    /*for(int i=0; i<90; i++)
        ci->img->setPixel(curX+550, curY+i, 1);
    for(int i=10; i<80; i++)
        ci->img->setPixel(curX+550+100/3, curY+i, 1);
    for(int i=0; i<90; i++)
        ci->img->setPixel(curX+550+200/3, curY+i, 1);
    for(int i=10; i<80; i++)
        ci->img->setPixel(curX+550+200/2, curY+i, 1);
    for(int i=0; i<90; i++)
        ci->img->setPixel(curX+550+2*200/3, curY+i, 1);
    for(int i=0; i<90; i++)
        ci->img->setPixel(curX+750, curY+i, 1);
    for(int i=0; i<200; i++)
        ci->img->setPixel(curX+550+i, curY+45, 1);*/

    if(!sceneForRecognise) delete(sceneForRecognise);
    sceneForRecognise = new QGraphicsScene(this);
    sceneForRecognise->setSceneRect(curX,curY,800,90);
    sceneForRecognise->addPixmap(QBitmap::fromImage(*(ci->img)));
    form->grForRecognise->setScene(sceneForRecognise);

    ci -> study(curX+550, curY, 201, 90, form->tableWidget->item(curRow,2)->text());

    //viewString();
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
    {
        curX = ci->LXcenter+300;
        curY = ci->LYcenter+(ci->DYcenter - ci->LYcenter)*45/500 + (ci->DYcenter - ci->LYcenter) * (inPage%25) * 445/500/25;
    }
    else                // в правом столбце
    {
        curX = ci->LXcenter+1390;
        curY = ci->RYcenter+(ci->DYcenter - ci->RYcenter)*45/500 + (ci->DYcenter - ci->RYcenter) * (inPage%25) * 445/500/25;
    }

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

    //Если не первая точка, то сохраним данные предыдущей точки
    t="";
    if(currentTochka != t)
    {

        for(int i=0; g->next(); i++)
        {
            t=form->tableWidget->item(i,2)->text();
            g->update(currentTochka, form->tableWidget->item(i,0)->text().toInt(), form->tableWidget->item(i,2)->text().toInt());
            pqtwi = form->tableWidget->item(i,0);
            //printf("pqtwi0=%d\n",pqtwi);
            if(pqtwi) delete pqtwi;
            pqtwi = form->tableWidget->item(i,1);
            //printf("pqtwi1=%d\n",pqtwi);
            if(pqtwi) delete pqtwi;
            pqtwi = form->tableWidget->item(i,2);
            //printf("pqtwi2=%d\n",pqtwi);
            if(pqtwi) delete pqtwi;

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
