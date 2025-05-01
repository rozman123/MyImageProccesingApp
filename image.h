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

public:
    Image();
    int getWidth();
    int getHeight();
    void loadImageFromPath(QString pathToImage);
    void loadImageFromImage(QImage image_to_load);
    Histogram getHistogram();
    QImage getImage();
};

#endif // IMAGE_H
