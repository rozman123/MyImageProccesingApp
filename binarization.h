#ifndef BINARIZATION_H
#define BINARIZATION_H

#include <QImage>
#include "image.h"


namespace Binariztion
{

    QImage& manual_binarization(Image& imageHandle,int threshold);


}



#endif // BINARIZATION_H
