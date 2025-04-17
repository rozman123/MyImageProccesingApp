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
    static std::vector<QHash<int, int> > HistogramChanels;
    static int maxHeigntOfHistogram;
    static QDialog *histogramWindow;
    static QLabel *histogramChart;
    static QVBoxLayout* layout;
public:
    Histogram();
    static void readPixelDataFrom(QImage image);
    static void resetHistogram();
    static void showHistogram(QImage image);
    static std::vector<QHash<int, int> > & getHistogramChanelsVector();
};

#endif // HISTOGRAM_H
