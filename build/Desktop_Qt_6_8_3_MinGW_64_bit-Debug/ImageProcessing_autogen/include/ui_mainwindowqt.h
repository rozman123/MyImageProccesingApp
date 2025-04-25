/********************************************************************************
** Form generated from reading UI file 'mainwindowqt.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOWQT_H
#define UI_MAINWINDOWQT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindowQt
{
public:
    QWidget *centralwidget;
    QPushButton *negative;
    QPushButton *greyScale;
    QPushButton *Stretching;
    QPushButton *loadImage;
    QGraphicsView *imageSlot;
    QPushButton *Brightnes;
    QPushButton *Contrast;
    QPushButton *Gamma;
    QLineEdit *numberEditor;
    QPushButton *histogram;
    QPushButton *wyrownanie;
    QPushButton *rozmycieRownomierne;
    QLineEdit *maskSize;
    QLineEdit *optionOfFillingpixelsOutOfImage;
    QPushButton *rozmycieGausowskie;
    QLineEdit *sigma;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindowQt)
    {
        if (MainWindowQt->objectName().isEmpty())
            MainWindowQt->setObjectName("MainWindowQt");
        MainWindowQt->resize(1227, 600);
        centralwidget = new QWidget(MainWindowQt);
        centralwidget->setObjectName("centralwidget");
        negative = new QPushButton(centralwidget);
        negative->setObjectName("negative");
        negative->setGeometry(QRect(10, 70, 101, 31));
        greyScale = new QPushButton(centralwidget);
        greyScale->setObjectName("greyScale");
        greyScale->setGeometry(QRect(10, 120, 101, 31));
        Stretching = new QPushButton(centralwidget);
        Stretching->setObjectName("Stretching");
        Stretching->setGeometry(QRect(10, 220, 101, 31));
        loadImage = new QPushButton(centralwidget);
        loadImage->setObjectName("loadImage");
        loadImage->setGeometry(QRect(10, 20, 101, 31));
        imageSlot = new QGraphicsView(centralwidget);
        imageSlot->setObjectName("imageSlot");
        imageSlot->setGeometry(QRect(295, 11, 921, 531));
        Brightnes = new QPushButton(centralwidget);
        Brightnes->setObjectName("Brightnes");
        Brightnes->setGeometry(QRect(160, 20, 101, 31));
        Contrast = new QPushButton(centralwidget);
        Contrast->setObjectName("Contrast");
        Contrast->setGeometry(QRect(160, 70, 101, 31));
        Gamma = new QPushButton(centralwidget);
        Gamma->setObjectName("Gamma");
        Gamma->setGeometry(QRect(160, 120, 101, 31));
        numberEditor = new QLineEdit(centralwidget);
        numberEditor->setObjectName("numberEditor");
        numberEditor->setGeometry(QRect(162, 170, 91, 31));
        histogram = new QPushButton(centralwidget);
        histogram->setObjectName("histogram");
        histogram->setGeometry(QRect(10, 170, 101, 31));
        wyrownanie = new QPushButton(centralwidget);
        wyrownanie->setObjectName("wyrownanie");
        wyrownanie->setGeometry(QRect(10, 270, 101, 31));
        rozmycieRownomierne = new QPushButton(centralwidget);
        rozmycieRownomierne->setObjectName("rozmycieRownomierne");
        rozmycieRownomierne->setGeometry(QRect(10, 350, 261, 31));
        maskSize = new QLineEdit(centralwidget);
        maskSize->setObjectName("maskSize");
        maskSize->setGeometry(QRect(20, 310, 91, 31));
        optionOfFillingpixelsOutOfImage = new QLineEdit(centralwidget);
        optionOfFillingpixelsOutOfImage->setObjectName("optionOfFillingpixelsOutOfImage");
        optionOfFillingpixelsOutOfImage->setGeometry(QRect(150, 310, 101, 31));
        rozmycieGausowskie = new QPushButton(centralwidget);
        rozmycieGausowskie->setObjectName("rozmycieGausowskie");
        rozmycieGausowskie->setGeometry(QRect(10, 430, 261, 31));
        sigma = new QLineEdit(centralwidget);
        sigma->setObjectName("sigma");
        sigma->setGeometry(QRect(10, 390, 261, 31));
        MainWindowQt->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindowQt);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1227, 27));
        MainWindowQt->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindowQt);
        statusbar->setObjectName("statusbar");
        MainWindowQt->setStatusBar(statusbar);

        retranslateUi(MainWindowQt);

        QMetaObject::connectSlotsByName(MainWindowQt);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowQt)
    {
        MainWindowQt->setWindowTitle(QCoreApplication::translate("MainWindowQt", "MainWindowQt", nullptr));
        negative->setText(QCoreApplication::translate("MainWindowQt", "Negative", nullptr));
        greyScale->setText(QCoreApplication::translate("MainWindowQt", "Grey Scale", nullptr));
        Stretching->setText(QCoreApplication::translate("MainWindowQt", "Stretching", nullptr));
        loadImage->setText(QCoreApplication::translate("MainWindowQt", "Load Image", nullptr));
        Brightnes->setText(QCoreApplication::translate("MainWindowQt", "Brightnes", nullptr));
        Contrast->setText(QCoreApplication::translate("MainWindowQt", "Contrast", nullptr));
        Gamma->setText(QCoreApplication::translate("MainWindowQt", "Gamma", nullptr));
        histogram->setText(QCoreApplication::translate("MainWindowQt", "Histogram", nullptr));
        wyrownanie->setText(QCoreApplication::translate("MainWindowQt", "Wyr\303\263wnanie", nullptr));
        rozmycieRownomierne->setText(QCoreApplication::translate("MainWindowQt", "Rozmycie R\303\263wnomierne", nullptr));
        optionOfFillingpixelsOutOfImage->setText(QString());
        rozmycieGausowskie->setText(QCoreApplication::translate("MainWindowQt", "Rozmycie Gausowskie", nullptr));
        sigma->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindowQt: public Ui_MainWindowQt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOWQT_H
