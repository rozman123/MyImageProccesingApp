#ifndef IMAGE_H
#define IMAGE_H

#include "blur.h"
#include <QImage>
#include "histogram.h"
#include <sys/stat.h>
#include <sys/types.h>
#include "options.h"


class Image
{
private:
    QImage image;  // stores image data
    QImage orginalImage;  // stores orginal image for quick reset
    int imageWidth=0;
    int imageHeight=0;
    Histogram histogram;



public:
    inline Image(){};

    int getWidth();
    int getHeight();

    void loadImageFromPath(QString pathToImage);
    void loadImageFromImage(QImage image_to_load);

    Histogram getHistogram();
    void setHistogram();
    void showHistogram();
    inline QImage& getImage(){return image;};
    inline QImage& getOrginalImage(){return orginalImage;};
    QRgb getPixel(int x, int y, options::outOfImagePixelFilling option);
    QVector<QVector<int>> getWindow(int x, int y, int size,int channel, options::outOfImagePixelFilling option);
    QVector<QVector<QColor>> getWindow(const int& x_ofCenter,const int& y_ofCenter,const int& size, options::outOfImagePixelFilling option);

};

#endif // IMAGE_H
