#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include <qhash.h>
#include <qimage.h>
#include <QLabel>
#include <QVBoxLayout>
#include <qdialog.h>
#include <QPainter>

class Histogram
{

private:
    QHash<int, int> Red;
    QHash<int, int> Green;
    QHash<int, int> Blue;
    QHash<int, int> Lumosity;

    QPixmap histChart;

    int maxHeigntOfHistogram;
    QDialog *histogramWindow;
    QLabel *histogramChart;
    QVBoxLayout* layout;


public:
    Histogram(){};
    Histogram(QImage image);

    void readPixelDataFrom(QImage image);
    void resetHistogram();
    void generateHistogram(QImage image);
    void showHistogram();

    inline QHash<int, int> getRedChanel(){return Red;}
    inline QHash<int, int> getGreenChanel(){return Green;}
    inline QHash<int, int> getBlueChanel(){return Blue;}
    inline QHash<int, int> getLumosityChanel(){return Lumosity;}
};

#endif // HISTOGRAM_H
