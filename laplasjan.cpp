#include "laplasjan.h"
#include "convolution.h"

QVector<QVector<float>> Laplasjan::getLaplasjanMask(unsigned int size)
{
    QVector<QVector<float>> laplasjanMask(size,QVector<float>(size,-1));
    unsigned short center=size/2+1;
    laplasjanMask[center][center]=size*size-1;
    return laplasjanMask;
};

QImage Laplasjan::LaplasjanConvolute(Image& image,unsigned int maskSize,options::outOfImagePixelFilling option)
{

    int width = image.getWidth();
    int height = image.getHeight();
    auto laplasjanMask = getLaplasjanMask(maskSize);

    QImage resultImage = image.getImage();

    for (int channel = 0; channel < 4; ++channel)
    {
        for (int y = 0; y < height; ++y)
        {
            for (int x = 0; x < width; ++x)
            {
                auto window = image.getWindow(x, y, maskSize, channel, option);
                auto joined = Convolution::join(window, laplasjanMask);
                float accumulator = Convolution::sumMatrix(joined);

                int finalValue = std::clamp(static_cast<int>(accumulator), 0, 255);
                QColor color = resultImage.pixelColor(x, y);

                switch (channel)
                {
                case options::chanel::RED:
                    color.setRed(finalValue);
                    break;
                case options::chanel::GREEN:
                    color.setGreen(finalValue);
                    break;
                case options::chanel::BLUE:
                    color.setBlue(finalValue);
                    break;
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

