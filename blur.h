#ifndef BLUR_H
#define BLUR_H

#include <QImage>
#include "options.h"
#include <QFileDialog>
#include<QMessageBox>


class Image;

namespace Blur
{
    QImage convolute(Image& image, const QVector<QVector<float>>& mask,int channel, options::outOfImagePixelFilling option);
    void blurEven(Image &image,int maskSize, options::outOfImagePixelFilling optionForPixelFilling);
    void blurGauss(Image& image,int sizeOfMask,float sigma,options::outOfImagePixelFilling option);
    float gaussFunction(float x, float y, float sigma);
    QVector<QVector<float>> getGaussianMask(int size, float sigma);

};

#endif // BLUR_H
