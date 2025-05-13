#include "edgegradient.h"
#include <math.h>
#include <iostream>


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
QImage EdgeGradient::horizontalDetectionOnChanel(Image& image, const AbstractMaskInterface& mask, options::outOfImagePixelFilling option)
{
    int width = image.getWidth();
    int height = image.getHeight();
    int maskSize = mask.size;
    float weight = sum(mask.horizontalDetection);

    QImage convolutedImage = image.getImage();

    for (int chanel = 0; chanel < 4; ++chanel)
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            auto window = image.getWindow(x, y,maskSize,chanel, option);
            auto joined = join(window, mask.horizontalDetection);
            float accumulator = sum(joined);
            if (weight != 0) accumulator /= weight;
            int finalValue = std::clamp(static_cast<int>(accumulator), 0, 255);
            QColor color = convolutedImage.pixelColor(x, y);

            color.setRed(finalValue);
            color.setGreen(finalValue);
            color.setBlue(finalValue);
            QColor hsl = color.toHsl();
            hsl.setHsl(hsl.hue(), hsl.saturation(), finalValue);
            color = hsl.toRgb();


            convolutedImage.setPixelColor(x, y, color);
        }
    }

    return convolutedImage;
}

QImage EdgeGradient::verticalDetectionOnChanel(Image& image, const AbstractMaskInterface& mask, options::outOfImagePixelFilling option)
{
    int width = image.getWidth();
    int height = image.getHeight();
    int maskSize = mask.size;
    float weight = sum(mask.verticalDetection);


    QImage convolutedImage = image.getImage();

    for (int chanel = 0; chanel < 4; ++chanel)
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            auto window = image.getWindow(x, y,maskSize,chanel, option);
            auto joined = join(window, mask.verticalDetection);
            float accumulator = sum(joined);
            if (weight != 0) accumulator /= weight;
            int finalValue = std::clamp(static_cast<int>(accumulator), 0, 255);
            QColor color = convolutedImage.pixelColor(x, y);

            color.setRed(finalValue);
            color.setGreen(finalValue);
            color.setBlue(finalValue);
            QColor hsl = color.toHsl();
            hsl.setHsl(hsl.hue(), hsl.saturation(), finalValue);
            color = hsl.toRgb();

            convolutedImage.setPixelColor(x, y, color);
        }
    }

    return convolutedImage;
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

QImage EdgeGradient::transform(Image& image,options::edgeDetectionOptions edgeDetectionOption, options::outOfImagePixelFilling option)
{

    AbstractMaskInterface mask = maskLoad(edgeDetectionOption);


    std::cout<<mask.size;

    QImage imagemap = image.getImage();

    short imageHeight=image.getHeight();
    short imageWidth=image.getWidth();


        QImage verticalEdges = verticalDetectionOnChanel(image,mask,option);
        QImage horizontalEdges = horizontalDetectionOnChanel(image,mask,option);

    for (int y = 0; y < imageHeight; ++y)
    {
        for (int x = 0; x < imageWidth; ++x)
        {
            QColor original = imagemap.pixelColor(x, y);

            QColor edgeColorX = horizontalEdges.pixelColor(x, y);
            QColor edgeColorY = verticalEdges.pixelColor(x, y);


            QColor newColor = sqrt(pow(edgeColorX.red(),2)+pow(edgeColorY.red(),2));
            original.setRed(newColor.red());

            newColor = sqrt(pow(edgeColorX.green(),2)+pow(edgeColorY.green(),2));
            original.setGreen(newColor.green());

            newColor = sqrt(pow(edgeColorX.blue(),2)+pow(edgeColorY.blue(),2));
            original.setBlue(newColor.blue());

            newColor = sqrt(pow(edgeColorX.lightness(),2)+pow(edgeColorY.lightness(),2));
            QColor hsl = original.toHsl();
            hsl.setHsl(hsl.hue(), hsl.saturation(), newColor.lightness());
            original = hsl.toRgb();


            imagemap.setPixelColor(x, y, original);
        }
    }





    return imagemap;

}


