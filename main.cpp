#include "mainwindowqt.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);


    MainWindowQt mainWindowQt;
    mainWindowQt.setWindowTitle("Image Processing");








    mainWindowQt.show();
    return application.exec();
}
