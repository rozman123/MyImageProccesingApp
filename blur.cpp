#include "blur.h"
#include <QFileDialog>
#include<QMessageBox>

// zwraca maske/macierz size*size z jedynką w środku
void Blur::setMask(int size)
{
    mask = QVector<QVector<float>> (size, QVector<float>(size, 0.0f));
    int center = size / 2;
    mask[center][center] = 1.0f;

}
//wykonuje iloczyn macierzy element po elemencie
QVector<QVector<float> > Blur::join(const QVector<QVector<int>>& a, const QVector<QVector<float>>& b)
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
float Blur::sum(const QVector<QVector<float> >& matrix)
{
    float total = 0.0f;
    for (const auto& row : matrix)
        for (float val : row)
            total += val;
    return total;
}

//zwraca lustrzane odbicie maski
QVector<QVector<float> > Blur::reflection(const QVector<QVector<float>>& matrix) {
    int size = matrix.size();
    QVector<QVector<float>> result(size, QVector<float>(size));
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            result[i][j] = matrix[size - 1 - i][size - 1 - j];
    return result;
}

QImage Blur::convolute(const QVector<QVector<float>>& mask, int channel, options::optionsOfPixelsFillingOutsideOfImage option)
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


// wykonuje operację splotu na obrazie/uwzględniając konkretny kanał
void Blur::blurEven(int maskSize, options::optionsOfPixelsFillingOutsideOfImage optionForPixelFilling)
{
    setMask(maskSize);
    int imageWidth = image.getWidth();
    int imageHeight = image.getHeight();

    options::optionsOfPixelsFillingOutsideOfImage option = options::cyclicPixels;

    switch(optionForPixelFilling)
    {
        case 0: { option  = options::cyclicPixels; break;}
        case 1: { option = options::blackPixels; break;}
        case 2: { option = options::repeatPixels; break;}
        default: { option = options::cyclicPixels; break;}
    }
        QImage imagemap=image.getImage();
        // przetwarza każdy kanał RGB osobno
        for (int channel = 0; channel < 4; ++channel)
        {
            QImage blurred = convolute(mask, channel, option);

            for (int y = 0; y < imageHeight; ++y)
            {
                for (int x = 0; x < imageWidth; ++x)
                {
                    QColor original = imagemap.pixelColor(x, y);
                    QColor blurredColor = blurred.pixelColor(x, y);

                    // Ustawiamy tylko rozmyty kanał, pozostałe zostają bez zmian
                    switch (channel)
                    {
                    case 0: original.setRed(blurredColor.red()); break;
                    case 1: original.setGreen(blurredColor.green()); break;
                    case 2: original.setBlue(blurredColor.blue()); break;
                    case 3:
                    {
                        QColor hsl = original.toHsl();
                        hsl.setHsl(hsl.hue(), hsl.saturation(), blurredColor.lightness());
                        original = hsl.toRgb();
                        break;
                    }
                    }

                    imagemap.setPixelColor(x, y, original);
                }
            }
        }
        image.loadImageFromImage(imagemap);



}

//funkcja z obliczaniem gausa
float gaussFunction(float x, float y, float sigma)
{
    float coefficient = 1.0f / (2.0f * M_PI * sigma * sigma);
    float exponent = -(x * x + y * y) / (2.0f * sigma * sigma);
    return coefficient * std::exp(exponent);
}

//tworzy maske gausa
QVector<QVector<float>> getGaussianMask(int size, float sigma)
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

void Blur::blurGauss(int sizeOfMask,float sigma,options::optionsOfPixelsFillingOutsideOfImage optionForPixelFilling)
{
    int imageWidth = image.getWidth();
    int imageHeight = image.getHeight();

    options::optionsOfPixelsFillingOutsideOfImage option = options::cyclicPixels;

    switch(optionForPixelFilling)
    {
    case 0: option = options::cyclicPixels; break;
    case 1: option = options::blackPixels; break;
    case 2: option = options::repeatPixels; break;
    default: option = options::cyclicPixels; break;
    }

    QVector<QVector<float>> mask = getGaussianMask(sizeOfMask, sigma);

    QImage imagemap = image.getImage();

    for (int channel = 0; channel < 4; ++channel)
    {
        QImage blurred = convolute( mask, channel, option);

        for (int y = 0; y < imageHeight; ++y)
        {
            for (int x = 0; x < imageWidth; ++x)
            {
                QColor original = imagemap.pixelColor(x, y);
                QColor blurredColor = blurred.pixelColor(x, y);

                switch (channel)
                {
                case 0: original.setRed(blurredColor.red()); break;
                case 1: original.setGreen(blurredColor.green()); break;
                case 2: original.setBlue(blurredColor.blue()); break;
                case 3:
                {
                    QColor hsl = original.toHsl();
                    hsl.setHsl(hsl.hue(), hsl.saturation(), blurredColor.lightness());
                    original = hsl.toRgb();
                    break;
                }
                }

                imagemap.setPixelColor(x, y, original);
            }
        }
    }
    image.loadImageFromImage(imagemap);

}
