#include "edgegradient.h"
#include <QColor>
#include <math.h>
#include <algorithm>
#include "convolution.h"


// konvloucja dla pojedyńczego kierunku (horizontal/vertical)
QImage EdgeGradient::applyDetection(Image& image, const QVector<QVector<float>>& maskMatrix,options::outOfImagePixelFilling option, bool horizontal)
{
    int width = image.getWidth();
    int height = image.getHeight();
    int maskSize = maskMatrix.size();

    QImage resultImage = image.getImage();

    for (int channel = 0; channel < 4; ++channel)
    {
        for (int y = 0; y < height; ++y)
        {
            for (int x = 0; x < width; ++x)
            {
                auto window = image.getWindow(x, y, maskSize, channel, option);
                auto joined = Convolution::join(window, maskMatrix);
                float accumulator = Convolution::sumMatrix(joined);


                int finalValue = std::clamp(static_cast<int>(accumulator), 0, 255);
                QColor color = resultImage.pixelColor(x, y);

                switch (channel)
                {
                case options::chanel::RED: color.setRed(finalValue); break;
                case options::chanel::GREEN: color.setGreen(finalValue); break;
                case options::chanel::BLUE: color.setBlue(finalValue); break;
                case options::chanel::LUMINOSITY:
                {
                    QColor hsl = color.toHsl();
                    hsl.setHsl(hsl.hue(), hsl.saturation(), finalValue);
                    color = hsl.toRgb();
                    break;
                }
                }

                resultImage.setPixelColor(x, y, color);
            }
        }
    }

    return resultImage;
}

QImage EdgeGradient::horizontalDetectionOnChanel(Image& image, const AbstractMaskInterface& mask, options::outOfImagePixelFilling option)
{
    return applyDetection(image, mask.horizontalDetection, option, true);
}

QImage EdgeGradient::verticalDetectionOnChanel(Image& image, const AbstractMaskInterface& mask, options::outOfImagePixelFilling option)
{
    return applyDetection(image, mask.verticalDetection, option, false);
}

const EdgeGradient::AbstractMaskInterface& EdgeGradient::maskLoad(options::edgeDetectionOptions edgeDetectionOption)
{
    if (edgeDetectionOption==options::Roberts)
        return getRobertsMask();
    else if (edgeDetectionOption==options::Prewitt)
        return getPrewittMask();
    else if (edgeDetectionOption==options::Sobel)
        return getSobelMask();
    //else if (edgeDetectionOption==options::Lapsjan)
    //return getLapsjanMask();


    return getRobertsMask();
}

QImage EdgeGradient::transform(Image& image, options::edgeDetectionOptions edgeDetectionOption, options::outOfImagePixelFilling option)
{
    const AbstractMaskInterface& mask = maskLoad(edgeDetectionOption);

    QImage pixmap = image.getImage();
    QImage verticalEdges = verticalDetectionOnChanel(image, mask, option);
    QImage horizontalEdges = horizontalDetectionOnChanel(image, mask, option);

    int width = image.getWidth();
    int height = image.getHeight();

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            QColor vx = verticalEdges.pixelColor(x, y);
            QColor hx = horizontalEdges.pixelColor(x, y);
            QColor base = pixmap.pixelColor(x, y);

            int red = std::clamp(static_cast<int>(std::sqrt(hx.red() * hx.red() + vx.red() * vx.red())), 0, 255);
            int green = std::clamp(static_cast<int>(std::sqrt(hx.green() * hx.green() + vx.green() * vx.green())), 0, 255);
            int blue = std::clamp(static_cast<int>(std::sqrt(hx.blue() * hx.blue() + vx.blue() * vx.blue())), 0, 255);
            int light = std::clamp(static_cast<int>(std::sqrt(hx.lightness() * hx.lightness() + vx.lightness() * vx.lightness())), 0, 255);

            base.setRed(red);
            base.setGreen(green);
            base.setBlue(blue);

            QColor hsl = base.toHsl();
            hsl.setHsl(hsl.hue(), hsl.saturation(), light);
            base = hsl.toRgb();

            pixmap.setPixelColor(x, y, base);
        }
    }

    return pixmap;
}








