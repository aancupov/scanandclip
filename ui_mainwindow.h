/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Thu Dec 22 16:45:21 2011
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QGraphicsView>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QTableWidget>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QTabWidget *tabWidget;
    QWidget *tab;
    QWidget *tab_2;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QGraphicsView *sourceImage;
    QGraphicsView *grListNumber;
    QGraphicsView *grItog;
    QGraphicsView *grForRecognise;
    QHBoxLayout *horizontalLayout;
    QPushButton *btPrev;
    QPushButton *btNext;
    QComboBox *tochka;
    QPushButton *btSaveXML;
    QPushButton *btRecognize;
    QTableWidget *tableWidget;
    QLabel *lbSum;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(812, 542);
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(0, 0, 811, 491));
        sizePolicy.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        sizePolicy.setHeightForWidth(tab->sizePolicy().hasHeightForWidth());
        tab->setSizePolicy(sizePolicy);
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        sizePolicy.setHeightForWidth(tab_2->sizePolicy().hasHeightForWidth());
        tab_2->setSizePolicy(sizePolicy);
        verticalLayoutWidget_2 = new QWidget(tab_2);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(0, 10, 802, 451));
        verticalLayout_3 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setSizeConstraint(QLayout::SetMaximumSize);
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        sourceImage = new QGraphicsView(verticalLayoutWidget_2);
        sourceImage->setObjectName(QString::fromUtf8("sourceImage"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(sourceImage->sizePolicy().hasHeightForWidth());
        sourceImage->setSizePolicy(sizePolicy1);
        sourceImage->setMinimumSize(QSize(350, 90));
        sourceImage->setMaximumSize(QSize(350, 90));
        sourceImage->setBaseSize(QSize(0, 0));
        sourceImage->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        sourceImage->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        sourceImage->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        horizontalLayout_2->addWidget(sourceImage);

        grListNumber = new QGraphicsView(verticalLayoutWidget_2);
        grListNumber->setObjectName(QString::fromUtf8("grListNumber"));
        grListNumber->setMaximumSize(QSize(150, 90));
        grListNumber->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        grListNumber->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        horizontalLayout_2->addWidget(grListNumber);

        grItog = new QGraphicsView(verticalLayoutWidget_2);
        grItog->setObjectName(QString::fromUtf8("grItog"));
        grItog->setMaximumSize(QSize(300, 90));
        grItog->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        grItog->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        horizontalLayout_2->addWidget(grItog);


        verticalLayout_3->addLayout(horizontalLayout_2);

        grForRecognise = new QGraphicsView(verticalLayoutWidget_2);
        grForRecognise->setObjectName(QString::fromUtf8("grForRecognise"));
        sizePolicy.setHeightForWidth(grForRecognise->sizePolicy().hasHeightForWidth());
        grForRecognise->setSizePolicy(sizePolicy);
        grForRecognise->setMinimumSize(QSize(600, 90));
        grForRecognise->setMaximumSize(QSize(800, 90));
        grForRecognise->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        grForRecognise->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        grForRecognise->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        verticalLayout_3->addWidget(grForRecognise);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        btPrev = new QPushButton(verticalLayoutWidget_2);
        btPrev->setObjectName(QString::fromUtf8("btPrev"));

        horizontalLayout->addWidget(btPrev);

        btNext = new QPushButton(verticalLayoutWidget_2);
        btNext->setObjectName(QString::fromUtf8("btNext"));

        horizontalLayout->addWidget(btNext);

        tochka = new QComboBox(verticalLayoutWidget_2);
        tochka->setObjectName(QString::fromUtf8("tochka"));

        horizontalLayout->addWidget(tochka);

        btSaveXML = new QPushButton(verticalLayoutWidget_2);
        btSaveXML->setObjectName(QString::fromUtf8("btSaveXML"));

        horizontalLayout->addWidget(btSaveXML);

        btRecognize = new QPushButton(verticalLayoutWidget_2);
        btRecognize->setObjectName(QString::fromUtf8("btRecognize"));

        horizontalLayout->addWidget(btRecognize);


        verticalLayout_3->addLayout(horizontalLayout);

        tableWidget = new QTableWidget(verticalLayoutWidget_2);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));

        verticalLayout_3->addWidget(tableWidget);

        tabWidget->addTab(tab_2, QString());
        lbSum = new QLabel(centralWidget);
        lbSum->setObjectName(QString::fromUtf8("lbSum"));
        lbSum->setGeometry(QRect(250, 490, 441, 20));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(lbSum->sizePolicy().hasHeightForWidth());
        lbSum->setSizePolicy(sizePolicy2);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 812, 22));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Tab 1", 0, QApplication::UnicodeUTF8));
        btPrev->setText(QApplication::translate("MainWindow", "\320\237\321\200\320\265\320\264\321\213\320\264\321\203\321\211\320\270\320\271 (Alt-&P)", 0, QApplication::UnicodeUTF8));
        btNext->setText(QApplication::translate("MainWindow", "\320\241\320\273\320\265\320\264\321\203\321\216\321\211\320\270\320\271 (Alt-&N)", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_ACCESSIBILITY
        tochka->setAccessibleName(QString());
#endif // QT_NO_ACCESSIBILITY
        btSaveXML->setText(QApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 (Alt-&S)", 0, QApplication::UnicodeUTF8));
        btRecognize->setText(QApplication::translate("MainWindow", "\320\240\320\260\321\201\320\277\320\276\320\267\320\275\320\260\321\202\321\214 (Alt-&R)", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "Tab 2", 0, QApplication::UnicodeUTF8));
        lbSum->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
