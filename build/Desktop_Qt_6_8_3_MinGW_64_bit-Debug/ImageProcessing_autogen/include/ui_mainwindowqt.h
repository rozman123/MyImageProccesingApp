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
    QGraphicsView *ImageSlot;
    QPushButton *Negative;
    QPushButton *GreyScale;
    QPushButton *Correction;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindowQt)
    {
        if (MainWindowQt->objectName().isEmpty())
            MainWindowQt->setObjectName("MainWindowQt");
        MainWindowQt->resize(800, 600);
        centralwidget = new QWidget(MainWindowQt);
        centralwidget->setObjectName("centralwidget");
        ImageSlot = new QGraphicsView(centralwidget);
        ImageSlot->setObjectName("ImageSlot");
        ImageSlot->setGeometry(QRect(125, 11, 671, 531));
        Negative = new QPushButton(centralwidget);
        Negative->setObjectName("Negative");
        Negative->setGeometry(QRect(10, 20, 101, 31));
        GreyScale = new QPushButton(centralwidget);
        GreyScale->setObjectName("GreyScale");
        GreyScale->setGeometry(QRect(10, 120, 101, 31));
        Correction = new QPushButton(centralwidget);
        Correction->setObjectName("Correction");
        Correction->setGeometry(QRect(10, 210, 101, 31));
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
        Negative->setText(QCoreApplication::translate("MainWindowQt", "Negative", nullptr));
        GreyScale->setText(QCoreApplication::translate("MainWindowQt", "Grey Scale", nullptr));
        Correction->setText(QCoreApplication::translate("MainWindowQt", "Correction", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindowQt: public Ui_MainWindowQt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOWQT_H
