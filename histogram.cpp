#include "histogram.h"
#include <qdialog.h>
#include<QPainter>
#include <QVBoxLayout>

int Histogram::maxHeigntOfHistogram = 0;
QDialog *Histogram::histogramWindow;
QLabel *Histogram::histogramChart;
QVBoxLayout *Histogram::layout;
std::vector<QHash<int, int> > Histogram::HistogramChanels;


Histogram::Histogram()
{

    histogramWindow = new QDialog;
    histogramWindow->setWindowTitle("Histogram");

    layout= new QVBoxLayout(histogramWindow);

    histogramChart = new QLabel;

    QHash<int, int> temp;

    maxHeigntOfHistogram = 0;
    for (int i = 0; i <= 255; ++i)
    {
        temp.insert(i, 0);
    }
    HistogramChanels.push_back(temp);
    HistogramChanels.push_back(temp);
    HistogramChanels.push_back(temp);
    HistogramChanels.push_back(temp);
}

void Histogram::readPixelDataFrom(QImage image)
{
    resetHistogram();
    for (int i = 0; i < image.width(); ++i)
    {
        for (int j = 0; j < image.height(); ++j)
        {

            QColor pixel = image.pixelColor(i, j);

            HistogramChanels[0][pixel.red()]+= 1;
            HistogramChanels[1][pixel.green()]+= 1;
            HistogramChanels[2][pixel.blue()]+= 1;
            HistogramChanels[3][pixel.lightness()]+= 1;
        }
    }
}

void Histogram::resetHistogram()
{
    maxHeigntOfHistogram = 0;
    for (int i=0;i<HistogramChanels.size();++i)
    for (int j = 0; j <= 255; ++j)
    {
        HistogramChanels[i][j]= 0;
    }
}

void Histogram::showHistogram(QImage image)
{
    readPixelDataFrom(image);
    unsigned int red = std::max_element(HistogramChanels[0].begin(), HistogramChanels[0].end()).value();
    unsigned int green = std::max_element(HistogramChanels[1].begin(), HistogramChanels[1].end()).value();
    unsigned int blue = std::max_element(HistogramChanels[2].begin(), HistogramChanels[2].end()).value();
    unsigned int lumosity = std::max_element(HistogramChanels[3].begin(), HistogramChanels[3].end()).value();

    maxHeigntOfHistogram = std::max({red,green,blue,lumosity});

    QPixmap histChart = QPixmap(255, 256);

    histChart.fill(QColor(255,255,255));


    QPainter painter= QPainter(&histChart);
    painter.setRenderHint(QPainter::Antialiasing);

    for (int givenColorValue = 0; givenColorValue < 256; ++givenColorValue)
    {
        int redHeightForGivenValue = HistogramChanels[0].value(givenColorValue);
        int greenHeightForGivenValue = HistogramChanels[1].value(givenColorValue);
        int blueHeightForGivenValue = HistogramChanels[2].value(givenColorValue);
        int lumosityHeightForGivenValue = HistogramChanels[3].value(givenColorValue);

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


    histogramChart->setPixmap(histChart);

    layout->addWidget(histogramChart);

    histogramWindow->exec();

}


std::vector<QHash<int, int> > & Histogram::getHistogramChanelsVector()
{

    return HistogramChanels;

}
