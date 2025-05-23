#include "histogram.h"
#include <iostream>

Histogram::Histogram(QImage image)
{
    histChart = QPixmap(255, 256);

    histogramWindow = new QDialog;
    histogramWindow->setWindowTitle("Histogram");

    layout= new QVBoxLayout(histogramWindow);

    histogramChart = new QLabel;


    maxHeigntOfHistogram = 0;
    resetHistogram();
    readPixelDataFrom(image);
}

void Histogram::readPixelDataFrom(QImage image)
{
    resetHistogram();
    for (int i = 0; i < image.width(); ++i)
    {
        for (int j = 0; j < image.height(); ++j)
        {

            QColor pixel = image.pixelColor(i, j);

            Red[pixel.red()]+= 1;
            Green[pixel.green()]+= 1;
            Blue[pixel.blue()]+= 1;
            Lumosity[pixel.lightness()]+= 1;
        }
    }
}

void Histogram::resetHistogram()
{
    maxHeigntOfHistogram = 0;
    for (int i = 0; i <= 255; ++i)
    {
        Red.insert(i, 0);
        Green.insert(i, 0);
        Blue.insert(i, 0);
        Lumosity.insert(i, 0);
    }
}
void Histogram::showHistogram()
{

    histogramChart->setPixmap(histChart);

    layout->addWidget(histogramChart);

    histogramWindow->exec();
}
void Histogram::generateHistogram(QImage image)
{
    readPixelDataFrom(image);
    unsigned int red = std::max_element(Red.begin(), Red.end()).value();
    unsigned int green = std::max_element(Green.begin(), Green.end()).value();
    unsigned int blue = std::max_element(Blue.begin(), Blue.end()).value();
    unsigned int lumosity = std::max_element(Lumosity.begin(), Lumosity.end()).value();

    maxHeigntOfHistogram = std::max({red,green,blue,lumosity});



    histChart.fill(QColor(255,255,255));
    std::cout<<"TUTAJ DOJECHAŁO\n";

    QPainter painter= QPainter(&histChart);
    painter.setRenderHint(QPainter::Antialiasing);

    for (int givenColorValue = 0; givenColorValue < 256; ++givenColorValue)
    {
        int redHeightForGivenValue = Red.value(givenColorValue);
        int greenHeightForGivenValue = Green.value(givenColorValue);
        int blueHeightForGivenValue = Blue.value(givenColorValue);
        int lumosityHeightForGivenValue = Lumosity.value(givenColorValue);

        //pionowe linie zamiast wielkości wartości w qhash
        painter.setPen(Qt::red);
        painter.drawLine(givenColorValue,0, givenColorValue,redHeightForGivenValue*256/maxHeigntOfHistogram);

        painter.setPen(Qt::green);
        painter.drawLine(givenColorValue, 0, givenColorValue, greenHeightForGivenValue*256/maxHeigntOfHistogram);

        painter.setPen(Qt::blue);
        painter.drawLine(givenColorValue, 0,givenColorValue,blueHeightForGivenValue*256/maxHeigntOfHistogram);


        painter.setPen(Qt::gray);
        painter.drawLine(givenColorValue, 0,givenColorValue,lumosityHeightForGivenValue*256/maxHeigntOfHistogram);

    }


}
