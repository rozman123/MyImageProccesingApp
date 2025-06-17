#ifndef EDGEGRADIENT_H
#define EDGEGRADIENT_H

#include <QImage>
#include "options.h"
#include "image.h"

namespace EdgeGradient
{

    struct AbstractMaskInterface
    {
        const QVector<QVector<float>> horizontalDetection;
        const QVector<QVector<float>> verticalDetection;
        const unsigned short size=0;

        inline AbstractMaskInterface(const QVector<QVector<float>>& h,const QVector<QVector<float>>& v,const unsigned short& s):horizontalDetection(std::move(h)),verticalDetection(std::move(v)),size(s){};
        virtual inline ~AbstractMaskInterface()=default;

    };
    struct RobertsMask : AbstractMaskInterface
    {
        RobertsMask() : AbstractMaskInterface({{1,0},{0,-1}},{{0,-1},{1,0}},2){};
    };
    struct PrewittMask : AbstractMaskInterface
    {
        PrewittMask() : AbstractMaskInterface({{-1,-1,-1},{0,0,0},{1,1,1}},{{-1,0,1},{-1,0,1},{-1,0,1}},3){};
    };
    struct SobelMask : AbstractMaskInterface
    {
        SobelMask() : AbstractMaskInterface({{-1,-2,-1},{0,0,0},{1,2,1}},{{-1,0,1},{-2,0,2},{-1,0,1}},3){};
    };



    const static inline RobertsMask& getRobertsMask(){const static RobertsMask robertsMask; return robertsMask;};
    const static inline PrewittMask& getPrewittMask(){const static PrewittMask prewittMask; return prewittMask;};
    const static inline SobelMask& getSobelMask(){const static SobelMask sobelMask; return sobelMask;};





    QImage horizontalDetectionOnChanel(Image& image, const AbstractMaskInterface& mask, options::outOfImagePixelFilling option);
    QImage verticalDetectionOnChanel(Image& image, const AbstractMaskInterface& mask, options::outOfImagePixelFilling option);
    QImage transform(Image& image,options::edgeDetectionOptions edgeDetectionOption, options::outOfImagePixelFilling option);

    const AbstractMaskInterface& maskLoad(options::edgeDetectionOptions edgeDetectionOption);

    QImage applyDetection(Image& image, const QVector<QVector<float>>& maskMatrix,options::outOfImagePixelFilling option, bool horizontal);


};

#endif // EDGEGRADIENT_H
