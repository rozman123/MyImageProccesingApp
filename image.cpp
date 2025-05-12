#include "image.h"
#include <QFileDialog>
#include<QMessageBox>



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

    imageWidth=image_to_load.width();
    imageHeight=image_to_load.height();
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
QRgb Image::getPixel(int x, int y, options::outOfImagePixelFilling option)
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
QVector<QVector<QColor>> Image::getWindow(int x, int y, int size, options::outOfImagePixelFilling option)
{

    QVector<QVector<QColor>> window(size, QVector<QColor>(size, QColor(0,0,0,0)));


    int half = size / 2;
    int offset_start = (size % 2 == 0) ? -half + 1 : -half;
    int offset_end   = half;

    for (int dy = offset_start; dy <= offset_end; ++dy)
    {
        for (int dx = offset_start; dx <= offset_end; ++dx)
        {
            QRgb pixel = getPixel(x + dx, y + dy, option);
            QColor color(pixel);

            int row = dy - offset_start;
            int col = dx - offset_start;
            window[row][col] = color;
        }
    }

    return window;
}




