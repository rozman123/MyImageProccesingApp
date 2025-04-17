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
    std::vector<QHash<int, int> > histChanels=Histogram::getHistogramChanelsVector();

        int minRed =histChanels[0][0]; // to musi być zrobione tak żeby nie dzieliło przez zero
        int maxRed =histChanels[0][255];
        int minGreen =histChanels[1][0];
        int maxGreen =histChanels[1][255];
        int minBlue =histChanels[2][0];
        int maxBlue =histChanels[2][255];
        int minLum =histChanels[3][0];
        int maxLum =histChanels[3][255];
        for (int i = 0; i < imageWidth; ++i)
        {
            for (int j = 0; j < imageHeight; ++j)
            {
                QColor givenPixelColor=imagemap.pixelColor(i,j);
                QColor pixelContrastColor= QColor(255/(maxRed-minRed),255/(minGreen-maxGreen),255/(minBlue-maxBlue),255/(minLum-maxLum));


                imagemap.setPixelColor(i,j,pixelContrastColor);
            }
        }

}

