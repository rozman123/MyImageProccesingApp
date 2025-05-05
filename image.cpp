#include "image.h"
#include <QFileDialog>
#include<QMessageBox>



Image::Image() {}

QImage& Image::getImage()
{
    return image;
}

void Image::loadImageFromPath(QString pathToImage)
{
    image.load(pathToImage);

    histogram = Histogram(image);

    imageWidth=image.width();
    imageHeight=image.height();
}

void Image::loadImageFromImage(QImage image_to_load)
{
    image=image_to_load;
}

int Image::getWidth()
{
    return imageWidth;
}
int Image::getHeight()
{
    return imageHeight;
}

Histogram Image::getHistogram()
{
    return histogram;
}

void Image::setHistogram()
{
    histogram.generateHistogram(image);
}
void Image::showHistogram()
{
    histogram.showHistogram();
}
// zwraca pixel na danym miejscu, potrzebna do zwracania
// pixeli poza obrazem w przypadku maski
QRgb Image::getPixel(int x, int y, options::optionsOfPixelsFillingOutsideOfImage option)
{
    if(option==0)
    {
        x = (x + imageWidth) % imageWidth;
        y = (y + imageHeight) % imageHeight;
        return image.pixel(x, y);
    }
    else if(option==1)
    {
        if (x < 0 || x >= imageWidth || y < 0 || y >= imageHeight)
            return qRgb(0, 0, 0);
        return image.pixel(x, y);
    }
    else if(option==2)
    {
        x = std::clamp(x, 0, imageWidth - 1);
        y = std::clamp(y, 0, imageHeight - 1);
        return image.pixel(x, y);
    }
    return qRgb(0, 0, 0);
}

// zwraca macierz pixeli/ (pixele somsiadujace z danym pikselem) na danym kanale
QVector<QVector<int> > Image::getWindow(int x, int y,int size,int channel, options::optionsOfPixelsFillingOutsideOfImage option)
{
    QVector<QVector<int>> window(size, QVector<int>(size, 0));
    int offset = size / 2;

    for (int dy = -offset; dy <= offset; ++dy)
    {
        for (int dx = -offset; dx <= offset; ++dx)
        {
            QRgb pixel = getPixel(x + dx, y + dy, option);
            QColor color(pixel);

            int value = 0;
            switch (channel)
            {
            case 0: value = color.red(); break;
            case 1: value = color.green(); break;
            case 2: value = color.blue(); break;
            default: value = color.lightness(); break;
            }

            window[dy + offset][dx + offset] = value;
        }
    }

    return window;
}





