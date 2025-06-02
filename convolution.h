#ifndef CONVOLUTION_H
#define CONVOLUTION_H

#include <QVector>
#include <qimage.h>
#include "options.h"
#include "image.h"

namespace Convolution
{

    QVector<QVector<float>> getMask(unsigned int size);
    QVector<QVector<float>> join(QVector<QVector<int>> matrixA, QVector<QVector<float>> matrixB);
    QVector<QVector<float>> reflectionMatrix(const QVector<QVector<float> >& matrix);

    float sumMatrix(const QVector<QVector<float> >& matrix);

    QImage& convloute(const QVector<QVector<float> >& mask,Image& image, options::outOfImagePixelFilling pixelOption);

    QVector<QVector<QRgb>> accumaulate(QVector<QVector<QRgb>> matrixA, QVector<QVector<float>> matrixB);
}

#endif // CONVOLUTION_H
