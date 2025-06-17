#include "EdgeLaplaceOfGauss.h"
#include "convolution.h"


float EdgeLaplaceOfGauss::getLoG(int x, int y, float sigma)
{
    float s2 = sigma * sigma;
    return ((x * x + y * y - 2) / s2) * Blur::gaussFunction(x, y, sigma);
}


QVector<QVector<float>> EdgeLaplaceOfGauss::getMask(int size, float sigma)
{
    QVector<QVector<float>> mask(size, QVector<float>(size, 0.0f));
    int center = size / 2;

    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            // wspórzendne 0,0 to inaczje środek dla getLaplacjanOfGauss
            int x = j - center;
            int y = i - center;
            mask[i][j] = getLoG(x, y, sigma);
        }
    }

    return mask;
}

QVector<QVector<float>> EdgeLaplaceOfGauss::convoluteLoG(const QVector<QVector<float>>& mask, Image& image, options::outOfImagePixelFilling pixelOption)
{
    const int maskSize = mask.size();
    const unsigned int height = image.getHeight();
    const unsigned int width = image.getWidth();

    QVector<QVector<float>> output(height, QVector<float>(width, 0.0f));

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            QVector<QVector<QColor>> window = image.getWindow(y, x, maskSize, pixelOption);
            auto joined = Convolution::accumaulate(window, mask);
            QVector<float> result = Convolution::sumMatrix(joined);
            output[y][x] = result[options::chanel::LUMINOSITY];
        }
    }

    return output;
}

QImage EdgeLaplaceOfGauss::zeroCrossing(const QVector<QVector<float>>& rawLoG, int t)
{
    int height = rawLoG.size();
    int width = rawLoG[0].size();
    QImage output(width, height, QImage::Format_RGB32);

    for (int y = 1; y < height - 1; ++y)
    {
        for (int x = 1; x < width - 1; ++x)
        {
            float minVal = rawLoG[y][x];
            float maxVal = rawLoG[y][x];

            for (int j = -1; j <= 1; ++j)
            {
                for (int i = -1; i <= 1; ++i)
                {
                    float val = rawLoG[y + j][x + i];
                    minVal = std::min(minVal, val);
                    maxVal = std::max(maxVal, val);
                }
            }

            if ((minVal < - t) && (maxVal >  t))
                output.setPixel(x, y, qRgb(0, 0, 0));  // edge (black)
            else
                output.setPixel(x, y, qRgb(255, 255, 255)); // non-edge (white)
        }
    }

    return output;
}


QImage EdgeLaplaceOfGauss::LaplacjanOfGauss(Image& image, int maskSize, double sigma, int t, options::outOfImagePixelFilling options)
{
    auto mask = EdgeLaplaceOfGauss::getMask(maskSize, sigma);

    auto rawLoG = convoluteLoG(mask, image, options);

    QImage result = zeroCrossing(rawLoG, t);
    return result;
}

