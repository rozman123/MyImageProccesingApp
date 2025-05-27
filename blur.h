#ifndef BLUR_H
#define BLUR_H

#include <QImage>
#include "options.h"
#include <QFileDialog>
#include<QMessageBox>


class Image;

namespace Blur
{
    QVector<QVector<float> > join(const QVector<QVector<int>>& a, const QVector<QVector<float>>& b);
    float sum(const QVector<QVector<float> >& matrix);
    QVector<QVector<float> > reflection(const QVector<QVector<float>>& matrix);
    QImage convolute(Image& image, const QVector<QVector<float>>& mask,int channel, options::outOfImagePixelFilling option);
    void blurEven(Image &image,int maskSize, options::outOfImagePixelFilling optionForPixelFilling);
    void blurGauss(Image& image,int sizeOfMask,float sigma,options::outOfImagePixelFilling option);
};

#endif // BLUR_H
