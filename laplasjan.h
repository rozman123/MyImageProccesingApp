#ifndef LAPLASJAN_H
#define LAPLASJAN_H

#include <QVector>
#include "image.h"
#include "blur.h"



namespace Laplasjan
{
    QVector<QVector<float>> getLaplasjanMask(unsigned int size);

    QImage LaplasjanConvolute(Image& image,unsigned int maskSize,options::outOfImagePixelFilling option);
    //QImage transformLaplasjan(Image& image,int maskSize, options::outOfImagePixelFilling option);

};

#endif // LAPLASJAN_H
