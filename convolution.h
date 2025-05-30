#ifndef CONVOLUTION_H
#define CONVOLUTION_H

#include <QVector>

namespace Convolution
{

    QVector<QVector<float>> getMask(unsigned int size);
    QVector<QVector<float>> join(QVector<QVector<int>> matrixA, QVector<QVector<float>> matrixB);
    QVector<QVector<float>> reflectionMatrix(const QVector<QVector<float> >& matrix);

    float sumMatrix(const QVector<QVector<float> >& matrix);

}

#endif // CONVOLUTION_H
