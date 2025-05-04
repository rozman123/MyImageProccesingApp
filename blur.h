#ifndef BLUR_H
#define BLUR_H

#include <QImage>
#include "image.h"
#include "options.h"


class Blur
{
private:

    Image image;
    QVector<QVector<float>> mask;

public:
    Blur(){};
    Blur(Image image){image=image;};
    QVector<QVector<float> > getMask(){return mask;};
    void setMask(int size);
    QVector<QVector<float> > join(const QVector<QVector<int>>& a, const QVector<QVector<float>>& b);
    float sum(const QVector<QVector<float> >& matrix);
    QVector<QVector<float> > reflection(const QVector<QVector<float>>& matrix);
    QImage convolute(const QVector<QVector<float>>& mask, int channel, options::optionsOfPixelsFillingOutsideOfImage option);
    void blurEven(int maskSize, options::optionsOfPixelsFillingOutsideOfImage optionForPixelFilling);
    void blurGauss(int sizeOfMask,float sigma,options::optionsOfPixelsFillingOutsideOfImage option);
};

#endif // BLUR_H
