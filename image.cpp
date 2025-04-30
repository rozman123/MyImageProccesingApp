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

void Image::loadImage(QString pathToImage)
{
    image.load(pathToImage);

    imageWidth=image.width();
    imageHeight=image.height();
}

void Image::loadModifiedImage(QImage image_to_load)
{
    scene->clear();
    QPixmap pixmap=QPixmap::fromImage(image_to_load);
    scene->addPixmap(pixmap);
    ui->imageSlot->fitInView(scene->itemsBoundingRect(),Qt::KeepAspectRatio);
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
