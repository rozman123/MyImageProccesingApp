

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
    histogram = Histogram(image);
}
float getFirstNonZeroPixelFromLeft(QHash<int,int> histChanel)
{

    for (int i=0;i<=255;++i)
    {
        //std::cout<<i<<"  "<<histChanel.value(i)<<std::endl;
        if(histChanel.value(i))
        {
            return i;
        }
    }

    return 0.0;
}

float getFirstNonZeroPixelFromRignt(QHash<int,int> histChanel)
{

    for (int i=255;i>=0;--i)
    {
        //std::cout<<i<<"  "<<histChanel.value(255-i)<<std::endl;
        if(histChanel.value(i))
        {
            return i;
        }
    }

    return 0.0;
}

void MainWindowQt::on_Stretching_clicked()
{
    QImage imagemap = image;

    QHash<int, int> Red =histogram.getRedChanel();
    QHash<int, int> Green=histogram.getGreenChanel();
    QHash<int, int> Blue=histogram.getBlueChanel();
    QHash<int, int> Lumosity=histogram.getLumosityChanel();

    float minRed = getFirstNonZeroPixelFromLeft(Red);
    float minGreen =getFirstNonZeroPixelFromLeft(Green);
    float minBlue =getFirstNonZeroPixelFromLeft(Blue);
    float minLum =getFirstNonZeroPixelFromLeft(Lumosity);



    float maxRed =getFirstNonZeroPixelFromRignt(Red);
    float maxGreen =getFirstNonZeroPixelFromRignt(Green);
    float maxBlue =getFirstNonZeroPixelFromRignt(Blue);
    float maxLum =getFirstNonZeroPixelFromRignt(Lumosity);


    // std::cout<<"Red: "<<minRed<<"    "<<maxRed<<std::endl;
    // std::cout<<"Green: "<<minGreen<<"    "<<maxGreen<<std::endl;
    // std::cout<<"Blue: "<<minBlue<<"    "<<maxBlue<<std::endl;
    // std::cout<<"Lum: "<<minLum<<"    "<<maxLum<<std::endl;
    for (int i = 0; i < imageWidth; ++i)
    {
        for (int j = 0; j < imageHeight; ++j)
        {
            QColor givenPixelColor=imagemap.pixelColor(i,j);
            QColor pixelContrastColor=givenPixelColor;
            if ((maxRed!=minRed) && (maxGreen!=minGreen)&&(maxBlue!=minBlue)&&(maxLum!=minLum))
                pixelContrastColor= QColor(static_cast<int>(255.0/(maxRed-minRed))*(givenPixelColor.red()-minRed),static_cast<int>(255.0/(maxGreen-minGreen))*(givenPixelColor.green()-minGreen),static_cast<int>(255.0/(maxBlue-minBlue))*(givenPixelColor.blue()-minBlue),static_cast<int>(255.0/(maxLum-minLum))*(givenPixelColor.lightness()-minLum));
            imagemap.setPixelColor(i,j,pixelContrastColor);
        }
    }
    loadModifiedImage(imagemap);
}




