#include "mainwindowqt.h"
#include "./ui_mainwindowqt.h"
#include <QFileDialog>
#include<QMessageBox>
#include<iostream>
MainWindowQt::MainWindowQt(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindowQt)
{
    scene = new QGraphicsScene(this);
    ui->setupUi(this);
    ui->imageSlot->setScene(scene);
}

MainWindowQt::~MainWindowQt()
{
    delete ui;
}

void MainWindowQt::on_loadImage_clicked()
{
    QString pathToFile = QFileDialog::getOpenFileName(this,"Load Image","","Images (*.png *.jpeg *.jpg *.bmp)");

    if(pathToFile.isEmpty())
    {
        QMessageBox::warning(this,"No File was Given!!","No file was given or given file does not exist","OK");
    }
    else
    {
        loadImage(pathToFile);
    }

}

void MainWindowQt::loadImage(QString pathToImage)
{
    scene->clear();

    image.load(pathToImage);

    imageWidth=image.width();
    imageHeight=image.height();

    if (!image.isNull())
    {
        QPixmap pixmap = QPixmap::fromImage(image);

        scene->addPixmap(pixmap);
        ui->imageSlot->fitInView(scene->itemsBoundingRect(), Qt::KeepAspectRatio);
    }
    else
    {
        QMessageBox::warning(this, "Error", "Failed to load image!");
    }

}

void MainWindowQt::loadModifiedImage(QImage image_to_load)
{
    scene->clear();
    QPixmap pixmap=QPixmap::fromImage(image_to_load);
    scene->addPixmap(pixmap);
    ui->imageSlot->fitInView(scene->itemsBoundingRect(),Qt::KeepAspectRatio);
    image=image_to_load;
}

void MainWindowQt::on_negative_clicked()
{

    QImage imagemap = image;
    for (int i=0;i<imageWidth;++i)
    {
        for (int j=0;j<imageHeight;++j)
        {
            QColor givenPixelColor=imagemap.pixelColor(i,j);
            QColor negativePixelColor= QColor(255-givenPixelColor.red(),
                                               255-givenPixelColor.green(),
                                               255-givenPixelColor.blue());


            imagemap.setPixelColor(i,j,negativePixelColor);
        }
    }
    loadModifiedImage(imagemap);
}


void MainWindowQt::on_greyScale_clicked()
{
    QImage imagemap = image;
    for (int i=0;i<imageWidth;++i)
    {
        for (int j=0;j<imageHeight;++j)
        {
            QColor givenPixelColor=imagemap.pixelColor(i,j);
            double greydPixelColor=(givenPixelColor.red()+
                                      givenPixelColor.green()+
                                      givenPixelColor.blue())/3;
            QColor graySclePixelColor= QColor(greydPixelColor,greydPixelColor,greydPixelColor);


            imagemap.setPixelColor(i,j,graySclePixelColor);
        }
    }
    loadModifiedImage(imagemap);
}



void MainWindowQt::on_Brightnes_clicked()
{
    int lut[256];
    bool ok=false;
    double numberX=ui->numberEditor->text().toDouble(&ok);
    if (ok)
    {
        for (int i=0;i<256;++i)
        {
            if (i+numberX>=256)
                lut[i] = 255;
            else if (i+numberX<0)
                lut[i] = 0;
            else
                lut[i] = i+numberX;
        }
    }
    else
    {
        QMessageBox::warning(this, "Error", "You must give a number for this operation!");
    }

    QImage imagemap = image;
    for (int i=0;i<imageWidth;++i)
    {
        for (int j=0;j<imageHeight;++j)
        {
            QColor givenPixelColor=imagemap.pixelColor(i,j);
            QColor pixelBrightnesColor= QColor(lut[givenPixelColor.red()],lut[givenPixelColor.green()],lut[givenPixelColor.blue()]);


            imagemap.setPixelColor(i,j,pixelBrightnesColor);
        }
    }
    loadModifiedImage(imagemap);

}


void MainWindowQt::on_Contrast_clicked()
{
    int lut[256];
    bool ok=false;
    double numberX=ui->numberEditor->text().toDouble(&ok);
    if (ok)
    {
        for (int i=0;i<256;++i)
        {
            if (i*numberX>=256)
                lut[i] = 255;
            else if (i*numberX<0)
                lut[i] = 0;
            else
                lut[i] = i*numberX;
        }
    }
    else
    {
        QMessageBox::warning(this, "Error", "You must give a number for this operation!");
    }

    QImage imagemap = image;
    for (int i=0;i<imageWidth;++i)
    {
        for (int j=0;j<imageHeight;++j)
        {
            QColor givenPixelColor=imagemap.pixelColor(i,j);
            QColor pixelContrastColor= QColor(lut[givenPixelColor.red()],lut[givenPixelColor.green()],lut[givenPixelColor.blue()]);


            imagemap.setPixelColor(i,j,pixelContrastColor);
        }
    }
    loadModifiedImage(imagemap);

}


void MainWindowQt::on_Gamma_clicked()
{
    int lut[256];
    bool ok=false;
    double numberX=ui->numberEditor->text().toDouble(&ok);
    if (ok)
    {
        for (int i=0;i<256;++i)
        {
            lut[i] = (pow(i,numberX)>=256) ? lut[i] = 255 : pow(i,numberX);
        }
    }
    else
    {
        QMessageBox::warning(this, "Error", "You must give a number for this operation!");
    }

    QImage imagemap = image;
    for (int i=0;i<imageWidth;++i)
    {
        for (int j=0;j<imageHeight;++j)
        {
            QColor givenPixelColor=imagemap.pixelColor(i,j);
            QColor pixelContrastColor= QColor(lut[givenPixelColor.red()],lut[givenPixelColor.green()],lut[givenPixelColor.blue()]);


            imagemap.setPixelColor(i,j,pixelContrastColor);
        }
    }
    loadModifiedImage(imagemap);
}


void MainWindowQt::on_histogram_clicked()
{

    Histogram::showHistogram(image);

}


void MainWindowQt::on_Stretching_clicked()
{
    QImage imagemap = image;
   std::tuple<QHash<int, int>,QHash<int, int>,QHash<int, int>,QHash<int, int> > temp = Histogram::getHistogramChanels();

    QHash<int, int> Red =std::get<0>(temp);
    QHash<int, int> Green=std::get<1>(temp);
    QHash<int, int> Blue=std::get<2>(temp);
    QHash<int, int> Lumosity=std::get<3>(temp);

    // for (int i = 0; i < 256; ++i)
    // {
    //     int minRed = histChanels[j].
    //     int minGreen =
    //     int minBlue =
    //     int minLum =
    // }
    // for (int i = 0; i < 256; ++i)
    // {
    //     if
    //     int maxGreen =
    //     int maxBlue =
    //     int maxRed =
    //     int maxLum =
    // }
    //     for (int i = 0; i < imageWidth; ++i)
    //     {
    //         for (int j = 0; j < imageHeight; ++j)
    //         {
    //             QColor givenPixelColor=imagemap.pixelColor(i,j);
    //             QColor pixelContrastColor= QColor((255/(maxRed-minRed))*(givenPixelColor.red()-minRed),(255/(minGreen-maxGreen))*(givenPixelColor.green()-minGreen),(255/(minBlue-maxBlue))*(givenPixelColor.blue()-minBlue),(255/(minLum-maxLum))*(givenPixelColor.lightness()-minLum));
    //             imagemap.setPixelColor(i,j,pixelContrastColor);
    //         }
    //     }

}

