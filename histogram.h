#ifndef HISTOGRAM_H
#define HISTOGRAM_H
#include <algorithm>
#include <qhash.h>
#include <qimage.h>
#include <QLabel>

class Histogram
{

private:
    static QHash<int, int> Red, Green, Blue, Lumosity;
    static int maxHeigntOfHistogram;
    static QDialog *histogramWindow;
    static QLabel *histogramChart;

public:
    Histogram();
    static void readPixelDataFrom(QImage image);
    static void resetHistogram();
    static void showHistogram(QImage image);
};

#endif // HISTOGRAM_H
