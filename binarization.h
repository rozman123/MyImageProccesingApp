#ifndef BINARIZATION_H
#define BINARIZATION_H

#include <QImage>
#include "image.h"


namespace Binariztion
{

    QImage& manual_binarization(Image& imageHandle,int threshold);
    QImage& auto_binarization(Image& imageHandle);
    QImage& bimodal_binarization(Image& imageHandle);
    QImage& otsu_binarization(Image& imageHandle);
    QImage niblack_binarization(Image& image, int windowSize, double alpha, options::outOfImagePixelFilling fillOption, int channel=3);

}



#endif // BINARIZATION_H
