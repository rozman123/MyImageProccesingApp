#include "edgegradient.h"

QImage EdgeGradient::horizontalDetection(Image& image, const QVector<QVector<float>>& mask, int channel, options::optionsOfPixelsFillingOutsideOfImage option)
{
    int width = image.getWidth();
    int height = image.getHeight();
    int maskSize = mask.size();
    float weight = sum(mask);

    QImage convolutedImage = image.getImage();

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            auto window = image.getWindow(x, y,maskSize, channel, option);
            auto joined = join(window, mask);
            float accumulator = sum(joined);
            if (weight != 0) accumulator /= weight;
            int finalValue = std::clamp(static_cast<int>(accumulator), 0, 255);
            QColor color = convolutedImage.pixelColor(x, y);
            switch (channel)
            {
            case 0: color.setRed(finalValue); break;
            case 1: color.setGreen(finalValue); break;
            case 2: color.setBlue(finalValue); break;
            default: color = QColor(finalValue, finalValue, finalValue); break;
            }
            convolutedImage.setPixelColor(x, y, color);
        }
    }

    return convolutedImage;
}

QImage EdgeGradient::verticalDetection(Image& image, const QVector<QVector<float>>& mask, int channel, options::optionsOfPixelsFillingOutsideOfImage option)
{
    int width = image.getWidth();
    int height = image.getHeight();
    int maskSize = mask.size();
    float weight = sum(mask);

    QImage convolutedImage = image.getImage();

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            auto window = image.getWindow(x, y,maskSize, channel, option);
            auto joined = join(window, mask);
            float accumulator = sum(joined);
            if (weight != 0) accumulator /= weight;
            int finalValue = std::clamp(static_cast<int>(accumulator), 0, 255);
            QColor color = convolutedImage.pixelColor(x, y);
            switch (channel)
            {
            case 0: color.setRed(finalValue); break;
            case 1: color.setGreen(finalValue); break;
            case 2: color.setBlue(finalValue); break;
            default: color = QColor(finalValue, finalValue, finalValue); break;
            }
            convolutedImage.setPixelColor(x, y, color);
        }
    }

    return convolutedImage;
}

