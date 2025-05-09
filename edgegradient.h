#ifndef EDGEGRADIENT_H
#define EDGEGRADIENT_H

#include <QImage>
#include "options.h"
#include "image.h"

namespace EdgeGradient
{
    // struct AbstractMask
    // {
    //     const QVector<QVector<float>>* horizontalDetection;
    //     const QVector<QVector<float>>* verticalDetection;
    //     const unsigned short* size;
    // };
    struct RobertsMask //: AbstractMask
    {
        const QVector<QVector<float>> horizontalDetection={{1,0},{0,-1}};
        const QVector<QVector<float>> verticalDetection={{0,-1},{1,0}};
        const unsigned short size = 2;
    };
    struct PrewittMask //: AbstractMask
    {
        const QVector<QVector<float>> horizontalDetection={{-1,-1,-1},{0,0,0},{1,1,1}};
        const QVector<QVector<float>> verticalDetection={{-1,0,1},{-1,0,1},{-1,0,1}};
        const unsigned short size = 3;
    };
    struct SobelMask //: AbstractMask
    {
        const QVector<QVector<float>> horizontalDetection={{-1,-2,-1},{0,0,0},{1,2,1}};
        const QVector<QVector<float>> verticalDetection={{-1,0,1},{-2,0,2},{-1,0,1}};
        const unsigned short size = 3;
    };


    const static RobertsMask robertsMask;
    const static PrewittMask prewittMask;
    const static SobelMask sobelMask;


    const static inline RobertsMask& getRobertsMask(){return robertsMask;};
    const static inline PrewittMask& getPrewittMask(){return prewittMask;};
    const static inline SobelMask& getSobelMask(){return sobelMask;};

    QImage horizontalDetectionOnChanel(Image& image, const SobelMask& mask, int channel, options::optionsOfPixelsFillingOutsideOfImage option);
    QImage verticalDetectionOnChanel(Image& image, const SobelMask& mask, int channel, options::optionsOfPixelsFillingOutsideOfImage option);// może zamienić tak by pojedyńcze pixele po konvolucji były zwracane a nie cały obraz (trzeba by zmienić convolute z image)
    QImage transform(Image& image, options::optionsOfPixelsFillingOutsideOfImage option);
};

#endif // EDGEGRADIENT_H
