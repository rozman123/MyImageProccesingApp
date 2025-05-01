#include "image.h"
#include "mainwindowqt.h"
#include "./ui_mainwindowqt.h"
#include <QFileDialog>
#include<QMessageBox>
#include<iostream>



Image::Image() {}

QImage Image::getImage()
{
    return image;
}

void Image::loadImageFromPath(QString pathToImage)
{
    image.load(pathToImage);

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
