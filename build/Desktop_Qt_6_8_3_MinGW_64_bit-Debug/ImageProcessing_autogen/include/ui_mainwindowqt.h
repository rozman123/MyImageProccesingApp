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
    QGraphicsView *imageSlot;
    QPushButton *negative;
    QPushButton *greyScale;
    QPushButton *correction;
    QPushButton *loadImage;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindowQt)
    {
        if (MainWindowQt->objectName().isEmpty())
            MainWindowQt->setObjectName("MainWindowQt");
        MainWindowQt->resize(800, 600);
        centralwidget = new QWidget(MainWindowQt);
        centralwidget->setObjectName("centralwidget");
        imageSlot = new QGraphicsView(centralwidget);
        imageSlot->setObjectName("imageSlot");
        imageSlot->setGeometry(QRect(125, 11, 671, 531));
        negative = new QPushButton(centralwidget);
        negative->setObjectName("negative");
        negative->setGeometry(QRect(10, 70, 101, 31));
        greyScale = new QPushButton(centralwidget);
        greyScale->setObjectName("greyScale");
        greyScale->setGeometry(QRect(10, 120, 101, 31));
        correction = new QPushButton(centralwidget);
        correction->setObjectName("correction");
        correction->setGeometry(QRect(10, 210, 101, 31));
        loadImage = new QPushButton(centralwidget);
        loadImage->setObjectName("loadImage");
        loadImage->setGeometry(QRect(10, 20, 101, 31));
        MainWindowQt->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindowQt);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 27));
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
        correction->setText(QCoreApplication::translate("MainWindowQt", "Correction", nullptr));
        loadImage->setText(QCoreApplication::translate("MainWindowQt", "Load Image", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindowQt: public Ui_MainWindowQt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOWQT_H
