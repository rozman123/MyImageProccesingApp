#include "histogram.h"
#include <qdialog.h>
#include<QPainter>
#include <QVBoxLayout>
QHash<int, int> Histogram::Red;
QHash<int, int> Histogram::Green;
QHash<int, int> Histogram::Blue;
QHash<int, int> Histogram::Lumosity;

int Histogram::maxHeigntOfHistogram = 0;
QDialog *Histogram::histogramWindow;
QLabel *Histogram::histogramChart;

Histogram::Histogram()
{
    histogramWindow = new QDialog;
    histogramWindow->setWindowTitle("Histogram");

    histogramChart = new QLabel;

    maxHeigntOfHistogram = 0;
    for (int i = 0; i <= 255; ++i) {
        Red.insert(i, 0);
        Green.insert(i, 0);
        Blue.insert(i, 0);
        Lumosity.insert(i, 0);
    }
}

void Histogram::readPixelDataFrom(QImage image)
{
    resetHistogram();
    for (int i = 0; i < image.width(); ++i)
    {
        for (int j = 0; j < image.height(); ++j)
        {
            QColor pixel = image.pixelColor(i, j);
            Red[pixel.red()] += 1;
            Green[pixel.green()] += 1;
            Blue[pixel.blue()] += 1;
            Lumosity[pixel.lightness()] += 1;
        }
    }
}

void Histogram::resetHistogram()
{
    maxHeigntOfHistogram = 0;
    for (int i = 0; i <= 255; ++i) {
        Red.insert(i, 0);
        Green.insert(i, 0);
        Blue.insert(i, 0);
        Lumosity.insert(i, 0);
    }
}

void Histogram::showHistogram(QImage image)
{
    readPixelDataFrom(image);
    unsigned int red = std::max_element(Red.begin(), Red.end()).value();
    unsigned int green = std::max_element(Green.begin(), Green.end()).value();
    unsigned int blue = std::max_element(Green.begin(), Green.end()).value();
    unsigned int lumosity = std::max_element(Green.begin(), Green.end()).value();

    maxHeigntOfHistogram = std::max({red,green,blue,lumosity});

    QPixmap histChart = QPixmap(255, 220);

    histChart.fill(QColor(255,255,255));


    QPainter painter= QPainter(&histChart);
    painter.setRenderHint(QPainter::Antialiasing);


    QVBoxLayout* layout = new QVBoxLayout(histogramWindow);


    histogramChart->setPixmap(histChart);

    layout->addWidget(histogramChart);

    histogramWindow->exec();

  }
