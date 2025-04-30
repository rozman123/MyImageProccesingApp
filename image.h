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
    void loadImage(QString pathToImage);
    void loadModifiedImage(QImage image_to_load);
    QImage getImage();
};

#endif // IMAGE_H
