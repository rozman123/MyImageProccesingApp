#ifndef EDGEGRADIENT_H
#define EDGEGRADIENT_H

#include <QImage>
#include "options.h"
#include "image.h"

class EdgeGradient
{

    struct RobertsMask
    {
        QVector<QVector<float>> horizontalDetection={{1,0},{0,-1}};
        QVector<QVector<float>> verticalDetection={{0,-1},{1,0}};
    };
    struct PrewittMask
    {
        QVector<QVector<float>> horizontalDetection={{-1,-1,-1},{0,0,0},{1,1,1}};
        QVector<QVector<float>> verticalDetection={{-1,0,1},{-1,0,1},{-1,0,1}};
    };
    struct SobelMask
    {
        QVector<QVector<float>> horizontalDetection={{-1,-2,-1},{0,0,0},{1,2,1}};
        QVector<QVector<float>> verticalDetection={{-1,0,1},{-2,0,2},{-1,0,1}};
    };

    static RobertsMask robertsMask;
    static PrewittMask prewittMask;
    static SobelMask sobelMask;




public:
    inline EdgeGradient(){};

    static inline RobertsMask getRobertsMask(){return robertsMask;};
    static inline PrewittMask getPrewittMask(){return prewittMask;};
    static inline SobelMask getSobelMask(){return sobelMask;};

    QImage horizontalDetection(Image& image, const QVector<QVector<float>>& mask, int channel, options::optionsOfPixelsFillingOutsideOfImage option); // może zamienić tak by pojedyńcze pixele po konvolucji były zwracane a nie cały obraz (trzeba by zmienić convolute z image)
    QImage verticalDetection(Image& image, const QVector<QVector<float>>& mask, int channel, options::optionsOfPixelsFillingOutsideOfImage option);// może zamienić tak by pojedyńcze pixele po konvolucji były zwracane a nie cały obraz (trzeba by zmienić convolute z image)
};

#endif // EDGEGRADIENT_H
