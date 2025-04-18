#ifndef HISTOGRAM_H
#define HISTOGRAM_H
#include <algorithm>
#include <qhash.h>
#include <qimage.h>
#include <QLabel>
#include <QVBoxLayout>
class Histogram
{

private:
    static QHash<int, int> Red;
    static QHash<int, int> Green;
    static QHash<int, int> Blue;
    static QHash<int, int> Lumosity;
    static int maxHeigntOfHistogram;
    static QDialog *histogramWindow;
    static QLabel *histogramChart;
    static QVBoxLayout* layout;
public:
    Histogram();
    static void readPixelDataFrom(QImage image);
    static void resetHistogram();
    static void showHistogram(QImage image);
    static std::tuple<QHash<int, int>,QHash<int, int>,QHash<int, int>,QHash<int, int> > getHistogramChanels();
};

#endif // HISTOGRAM_H
