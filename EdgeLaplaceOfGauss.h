#ifndef EDGELAPLACEOFGAUSS_H
#define EDGELAPLACEOFGAUSS_H

#include <QImage>
#include <QVector>
#include "options.h"
#include "image.h"

namespace EdgeLaplaceOfGauss
{

    float getLoG(int x, int y, float sigma);
    QVector<QVector<float>> getMask(int size, float sigma);

    QImage LaplacjanOfGauss(Image& image, int maskSize, double sigma, int t, options::outOfImagePixelFilling options);
    QImage zeroCrossing(const QVector<QVector<float>>& rawLoG, int t);
    QVector<QVector<float>> convoluteLoG(const QVector<QVector<float>>& mask, Image& image, options::outOfImagePixelFilling pixelOption);

}


#endif // EDGELAPLACEOFGAUSS_H
