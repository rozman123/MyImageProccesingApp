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

    QVector<float> sumMatrix(std::array<const QVector<QVector<float>>,options::chanelsNumber>& matrix);
    float sumMatrix(const QVector<QVector<float> >& matrix);

    QImage& convloute(const QVector<QVector<float> >& mask,Image& image, options::outOfImagePixelFilling pixelOption);

    std::array<QVector<QVector<float>>,options::chanelsNumber> accumaulate(QVector<QVector<QColor>> matrixA, QVector<QVector<float>> matrixB);
}

#endif // CONVOLUTION_H
