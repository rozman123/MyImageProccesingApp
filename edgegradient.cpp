#include "edgegradient.h"


//wykonuje iloczyn macierzy element po elemencie
QVector<QVector<float> > join(const QVector<QVector<int>>& a, const QVector<QVector<float>>& b)// ta metoda jest powielona w blur może umieść gdzieś indziej.
{
    int rows = a.size();
    int cols = a[0].size();
    QVector<QVector<float>> result(rows, QVector<float>(cols));
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            result[i][j] = a[i][j] * b[i][j];
    return result;
}
//sumuje wszystkie wartości w macierzy
float sum(const QVector<QVector<float> >& matrix)  // ta metoda jest powielona w blur może umieść gdzieś indziej.
{
    float total = 0.0f;
    for (const auto& row : matrix)
        for (float val : row)
            total += val;
    return total;
}


// neesds to be reimplemented
QImage EdgeGradient::horizontalDetection(Image& image, const SobelMask& mask, int channel, options::optionsOfPixelsFillingOutsideOfImage option)
{
    int width = image.getWidth();
    int height = image.getHeight();
    int maskSize = mask.size;
    float weight = sum(mask.horizontalDetection);

    QImage convolutedImage = image.getImage();

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            auto window = image.getWindow(x, y,maskSize, channel, option);
            auto joined = join(window, mask.horizontalDetection);
            float accumulator = sum(joined);
            if (weight != 0) accumulator /= weight;
            int finalValue = std::clamp(static_cast<int>(accumulator), 0, 255);
            QColor color = convolutedImage.pixelColor(x, y);
            switch (channel)
            {
            case 0: color.setRed(finalValue); break;
            case 1: color.setGreen(finalValue); break;
            case 2: color.setBlue(finalValue); break;
            case 3:
            {
                QColor hsl = color.toHsl();
                hsl.setHsl(hsl.hue(), hsl.saturation(), finalValue);
                color = hsl.toRgb();
                break;
            }
            default: color = QColor(finalValue, finalValue, finalValue); break;
            }
            convolutedImage.setPixelColor(x, y, color);
        }
    }

    return convolutedImage;
}

QImage EdgeGradient::verticalDetection(Image& image, const SobelMask& mask, int channel, options::optionsOfPixelsFillingOutsideOfImage option)
{
    int width = image.getWidth();
    int height = image.getHeight();
    int maskSize = mask.size;
    float weight = sum(mask.verticalDetection);

    QImage convolutedImage = image.getImage();

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            auto window = image.getWindow(x, y,maskSize, channel, option);
            auto joined = join(window, mask.verticalDetection);
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

QImage transform(Image& image)
{

}


