#ifndef BLUR_H
#define BLUR_H

#include <QImage>
#include "image.h"

class Blur
{
private:

    Image image;

public:
    Blur(){};
    Blur(Image image){image=image;};
    QVector<QVector<float> > getMask(int size);
    QVector<QVector<float> > join(const QVector<QVector<int>>& a, const QVector<QVector<float>>& b);
    float sum(const QVector<QVector<float> >& matrix);
    QVector<QVector<float> > reflection(const QVector<QVector<float>>& matrix);
    QImage convolute(const QImage& image, const QVector<QVector<float>>& mask, int channel, optionsOfPixelsFillingOutsideOfImage option);
    void on_rozmycieRownomierne_clicked();
    void on_rozmycieGausowskie_clicked();
};

#endif // BLUR_H
