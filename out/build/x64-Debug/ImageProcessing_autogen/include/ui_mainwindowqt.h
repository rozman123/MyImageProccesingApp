/********************************************************************************
** Form generated from reading UI file 'mainwindowqt.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOWQT_H
#define UI_MAINWINDOWQT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindowQt
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindowQt)
    {
        if (MainWindowQt->objectName().isEmpty())
            MainWindowQt->setObjectName(QStringLiteral("MainWindowQt"));
        MainWindowQt->resize(800, 600);
        centralwidget = new QWidget(MainWindowQt);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        MainWindowQt->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindowQt);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 27));
        MainWindowQt->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindowQt);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindowQt->setStatusBar(statusbar);

        retranslateUi(MainWindowQt);

        QMetaObject::connectSlotsByName(MainWindowQt);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowQt)
    {
        MainWindowQt->setWindowTitle(QApplication::translate("MainWindowQt", "MainWindowQt", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindowQt: public Ui_MainWindowQt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOWQT_H
