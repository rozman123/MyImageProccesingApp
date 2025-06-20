#include "blur.h"
#include "image.h"
#include "convolution.h"


// this needs to be changed it cannot be chalel wise
QImage Blur::convolute(Image& image, const QVector<QVector<float>>& mask,int channel, options::outOfImagePixelFilling option)
{
    int width = image.getWidth();
    int height = image.getHeight();
    int maskSize = mask.size();
    float weight = Convolution::sumMatrix(mask);

    QImage convolutedImage = image.getImage();

    for (int channel = 0; channel < 4; ++channel)
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            auto window = image.getWindow(x, y,maskSize,channel, option);
            auto joined = Convolution::join(window, mask);
            float accumulator = Convolution::sumMatrix(joined);
            if (weight != 0) accumulator /= weight;
            int finalValue = std::clamp(static_cast<int>(accumulator), 0, 255);
            QColor color = convolutedImage.pixelColor(x, y);

            switch(channel)
            {

                case 0: color.setRed(finalValue);break;
                case 1: color.setGreen(finalValue);break;
                case 2: color.setBlue(finalValue);break;
                case 3:
                {
                    QColor hsl = color.toHsl();
                    hsl.setHsl(hsl.hue(), hsl.saturation(), finalValue);
                    color = hsl.toRgb();
                    break;
                }
            }


            convolutedImage.setPixelColor(x, y, color);
        }
    }

    return convolutedImage;
}


// wykonuje operację splotu na obrazie/uwzględniając konkretny kanał
void Blur::blurEven(Image& image,int maskSize, options::outOfImagePixelFilling optionForPixelFilling)
{
    QVector<QVector<float>> mask=Convolution::getMask(maskSize);

    options::outOfImagePixelFilling option = options::cyclicPixels;

    switch(optionForPixelFilling)
    {
        case 0: { option  = options::cyclicPixels; break;}
        case 1: { option = options::blackPixels; break;}
        case 2: { option = options::repeatPixels; break;}
        default: { option = options::cyclicPixels; break;}
    }

    QImage blurred = Convolution::convolute(mask,image, option);
    image.loadImageFromImage(blurred);

}

//funkcja z obliczaniem gausa
float Blur::gaussFunction(float x, float y, float sigma)
{
    float coefficient = 1.0f / (2.0f * M_PI * sigma * sigma);
    float exponent = -(x * x + y * y) / (2.0f * sigma * sigma);
    return coefficient * std::exp(exponent);
}

//tworzy maske gausa
QVector<QVector<float>> Blur::getGaussianMask(int size, float sigma)
{
    QVector<QVector<float>> mask(size, QVector<float>(size));
    int center = size / 2;
    float total = 0.0f;

    for (int y = 0; y < size; ++y)
    {
        for (int x = 0; x < size; ++x)
        {
            float gaussValue = gaussFunction(x - center, y - center, sigma);
            mask[y][x] = gaussValue;
            total += gaussValue;
        }
    }

    // nrmalizacja maski// suma elementów to 1
    for (int y = 0; y < size; ++y)
    {
        for (int x = 0; x < size; ++x)
        {
            mask[y][x] /= total;
        }
    }

    return mask;
}

void Blur::blurGauss(Image& image,int sizeOfMask,float sigma,options::outOfImagePixelFilling optionForPixelFilling)
{
    options::outOfImagePixelFilling option = options::cyclicPixels;

    switch(optionForPixelFilling)
    {
    case 0: option = options::cyclicPixels; break;
    case 1: option = options::blackPixels; break;
    case 2: option = options::repeatPixels; break;
    default: option = options::cyclicPixels; break;
    }

    QVector<QVector<float>> mask = getGaussianMask(sizeOfMask, sigma);

    QImage blurred = Convolution::convolute(mask, image,option);
    image.loadImageFromImage(blurred);

}
