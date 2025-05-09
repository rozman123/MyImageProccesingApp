#include "edgegradient.h"
#include <math.h>

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
QImage EdgeGradient::horizontalDetectionOnChanel(Image& image, const SobelMask& mask, int channel, options::optionsOfPixelsFillingOutsideOfImage option)
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

QImage EdgeGradient::verticalDetectionOnChanel(Image& image, const SobelMask& mask, int channel, options::optionsOfPixelsFillingOutsideOfImage option)
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

QImage EdgeGradient::transform(Image& image, options::optionsOfPixelsFillingOutsideOfImage option)
{
    QImage imagemap = image.getImage();

    short imageHeight=image.getHeight();
    short imageWidth=image.getWidth();


    for (int i=0; i<4;++i)
    {
        QImage verticalEdges = verticalDetectionOnChanel(image,sobelMask,i,option);
        QImage horizontalEdges = horizontalDetectionOnChanel(image,sobelMask,i,option);

        for (int y = 0; y < imageHeight; ++y)
        {
            for (int x = 0; x < imageWidth; ++x)
            {
                QColor original = imagemap.pixelColor(x, y);

                QColor edgeColorX = horizontalEdges.pixelColor(x, y);
                QColor edgeColorY = verticalEdges.pixelColor(x, y);

                switch (i)
                {
                case 0:
                {
                    QColor newColor = sqrt(pow(edgeColorX.red(),2)+pow(edgeColorY.red(),2));
                    original.setRed(newColor.red());
                    break;
                }
                case 1:
                {
                    QColor newColor = sqrt(pow(edgeColorX.green(),2)+pow(edgeColorY.green(),2));
                    original.setGreen(newColor.green());
                    break;
                }
                case 2:
                {
                    QColor newColor = sqrt(pow(edgeColorX.blue(),2)+pow(edgeColorY.blue(),2));
                    original.setBlue(newColor.blue());
                    break;
                }
                case 3:
                {
                    QColor newColor = sqrt(pow(edgeColorX.lightness(),2)+pow(edgeColorY.lightness(),2));
                    QColor hsl = original.toHsl();
                    hsl.setHsl(hsl.hue(), hsl.saturation(), newColor.lightness());
                    original = hsl.toRgb();
                    break;
                }
                }

                imagemap.setPixelColor(x, y, original);
            }
        }


    }


    return imagemap;

}


