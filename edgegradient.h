#ifndef EDGEGRADIENT_H
#define EDGEGRADIENT_H

#include <QImage>
#include "options.h"
#include "image.h"

class EdgeGradient
{





public:
    inline EdgeGradient(){};
    QImage horizontalDetection(Image& image, const QVector<QVector<float>>& mask, int channel, options::optionsOfPixelsFillingOutsideOfImage option); // może zamienić tak by pojedyńcze pixele po konvolucji były zwracane a nie cały obraz (trzeba by zmienić convolute z image)
    QImage verticalDetection(Image& image, const QVector<QVector<float>>& mask, int channel, options::optionsOfPixelsFillingOutsideOfImage option);// może zamienić tak by pojedyńcze pixele po konvolucji były zwracane a nie cały obraz (trzeba by zmienić convolute z image)
};

#endif // EDGEGRADIENT_H
