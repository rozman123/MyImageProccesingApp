#ifndef IMAGE_H
#define IMAGE_H

#include <QImage>
#include "histogram.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <filesystem>
#include <fstream>

class Image
{
private:
    QImage image;  // stores image data
    int imageWidth=0;
    int imageHeight=0;
    Histogram histogram;

    enum optionsOfPixelsFillingOutsideOfImage{cyclicPixels=0,blackPixels=1,repeatPixels=2};


public:
    Image();
    int getWidth();
    int getHeight();
    void loadImageFromPath(QString pathToImage);
    void loadImageFromImage(QImage image_to_load);
    Histogram getHistogram();
    QImage getImage();
    QRgb getPixel(const Image & image, int x, int y, optionsOfPixelsFillingOutsideOfImage option);
    QVector<QVector<int> > getWindow(const QImage& image, int x, int y,int size, int channel, optionsOfPixelsFillingOutsideOfImage option);

};

#endif // IMAGE_H
