#include "mainwindowqt.h"
#include "./ui_mainwindowqt.h"
#include <QFileDialog>
#include<QMessageBox>
#include "histogram.h"
#include <fstream>
#include "options.h"

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

void MainWindowQt::load_modified_image(QImage & image_to_load)
{
    scene->clear();
    QPixmap pixmap=QPixmap::fromImage(image_to_load);
    scene->addPixmap(pixmap);
    ui->imageSlot->fitInView(scene->itemsBoundingRect(),Qt::KeepAspectRatio);
    imageHandle.loadImageFromImage(image_to_load);
}

void MainWindowQt::on_loadImage_clicked()
{
    scene->clear();
    QString pathToFile = QFileDialog::getOpenFileName(this,"Load Image","","Images (*.png *.jpeg *.jpg *.bmp *.pbm *.pgm *.ppm *)");

    if(pathToFile.isEmpty())
    {
        return;
    }
    else
    {
        imageHandle.loadImageFromPath(pathToFile);
        if (!imageHandle.getImage().isNull())
        {
            QPixmap pixmap = QPixmap::fromImage(imageHandle.getImage());

            scene->addPixmap(pixmap);
            ui->imageSlot->fitInView(scene->itemsBoundingRect(), Qt::KeepAspectRatio);
        }
        else
        {
            QMessageBox::warning(this, "Error", "Failed to load image!");
        }
    }
}

void MainWindowQt::on_histogram_clicked()
{
    imageHandle.setHistogram();
    imageHandle.showHistogram();
}

void MainWindowQt::on_negative_clicked()
{

    QImage imagemap = imageHandle.getImage();
    int imageWidth=imageHandle.getWidth();
    int imageHeight=imageHandle.getHeight();

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
    load_modified_image(imagemap);
}


void MainWindowQt::on_greyScale_clicked()
{
    QImage imagemap = imageHandle.getImage();
    int imageWidth=imageHandle.getWidth();
    int imageHeight=imageHandle.getHeight();

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
    load_modified_image(imagemap);
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

    QImage imagemap = imageHandle.getImage();
    int imageWidth=imageHandle.getWidth();
    int imageHeight=imageHandle.getHeight();

    for (int i=0;i<imageWidth;++i)
    {
        for (int j=0;j<imageHeight;++j)
        {
            QColor givenPixelColor=imagemap.pixelColor(i,j);
            QColor pixelBrightnesColor= QColor(lut[givenPixelColor.red()],lut[givenPixelColor.green()],lut[givenPixelColor.blue()]);


            imagemap.setPixelColor(i,j,pixelBrightnesColor);
        }
    }
    load_modified_image(imagemap);

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

    QImage imagemap = imageHandle.getImage();
    int imageWidth=imageHandle.getWidth();
    int imageHeight=imageHandle.getHeight();

    for (int i=0;i<imageWidth;++i)
    {
        for (int j=0;j<imageHeight;++j)
        {
            QColor givenPixelColor=imagemap.pixelColor(i,j);
            QColor pixelContrastColor= QColor(lut[givenPixelColor.red()],lut[givenPixelColor.green()],lut[givenPixelColor.blue()]);


            imagemap.setPixelColor(i,j,pixelContrastColor);
        }
    }
    load_modified_image(imagemap);

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

    QImage imagemap = imageHandle.getImage();
    int imageWidth=imageHandle.getWidth();
    int imageHeight=imageHandle.getHeight();

    for (int i=0;i<imageWidth;++i)
    {
        for (int j=0;j<imageHeight;++j)
        {
            QColor givenPixelColor=imagemap.pixelColor(i,j);
            QColor pixelContrastColor= QColor(lut[givenPixelColor.red()],lut[givenPixelColor.green()],lut[givenPixelColor.blue()]);


            imagemap.setPixelColor(i,j,pixelContrastColor);
        }
    }
    load_modified_image(imagemap);
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

    QImage imagemap = imageHandle.getImage();
    int imageWidth=imageHandle.getWidth();
    int imageHeight=imageHandle.getHeight();

    imageHandle.setHistogram();
    Histogram histogram = imageHandle.getHistogram();

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
    load_modified_image(imagemap);
    MainWindowQt::on_histogram_clicked();
}


// Funkcja pomocnicza do twożenia LUT dla Wyrównywania
QVector<int> createLUT(const QHash<int, int>& hist,unsigned long pixelCount)
{
    QVector<float> prob(256, 0.0f);
    QVector<int> LUT(256, 0);
    float cumulative = 0.0f;

    for (int i = 0; i < 256; ++i)
        prob[i] = static_cast<float>(hist.value(i)) / pixelCount;

    for (int i = 0; i < 256; ++i)
    {
        cumulative += prob[i];
        LUT[i] = std::round(cumulative * 255);
    }
    return LUT;
};


void MainWindowQt::on_wyrownanie_clicked()
{

    QImage imagemap = imageHandle.getImage();
    int imageWidth=imageHandle.getWidth();
    int imageHeight=imageHandle.getHeight();

    unsigned long allPixels = imageWidth * imageHeight;

    imageHandle.setHistogram();
    Histogram histogram = imageHandle.getHistogram();

    QHash<int, int> Red =histogram.getRedChanel();
    QHash<int, int> Green=histogram.getGreenChanel();
    QHash<int, int> Blue=histogram.getBlueChanel();
    QHash<int, int> Lumosity=histogram.getLumosityChanel();

    // LUT dla kanałów
    QVector<int> redLUT = createLUT(Red,allPixels);
    QVector<int> greenLUT = createLUT(Green,allPixels);
    QVector<int> blueLUT = createLUT(Blue,allPixels);
    QVector<int> lumLUT = createLUT(Lumosity,allPixels);

    // Przekształcenie obrazu
    for (int i = 0; i < imageWidth; ++i)
    {
        for (int j = 0; j < imageHeight; ++j)
        {
            QColor pixel = imagemap.pixelColor(i, j);

            imagemap.setPixelColor(i, j, QColor(redLUT[pixel.red()], greenLUT[pixel.green()], blueLUT[pixel.blue()],lumLUT[pixel.lightness()]));

        }
    }

    load_modified_image(imagemap);
    MainWindowQt::on_histogram_clicked();
}

void MainWindowQt::on_rozmycieRownomierne_clicked()
{
    bool ok1=false;
    bool ok2=false;
    int sizeOfMask=ui->maskSize->text().toInt(&ok1);
    int temp=ui->optionOfFillingpixelsOutOfImage->text().toInt(&ok2);

    options::optionsOfPixelsFillingOutsideOfImage option=static_cast<options::optionsOfPixelsFillingOutsideOfImage>(temp);

    if (ok1&&ok2)
    {
        Blur::blurEven(imageHandle,sizeOfMask,option);
        load_modified_image(imageHandle.getImage());
    }
    else
    {
        QMessageBox::warning(this, "Error", "You must give a size of mask on left and a number of the filling of pixels outside of image for this operation!");
    }
}

void MainWindowQt::on_rozmycieGausowskie_clicked()
{
    bool ok1 = false, ok2 = false, ok3 = false;
    int sizeOfMask = ui->maskSize->text().toInt(&ok1);
    float sigma = ui->sigma->text().toFloat(&ok2);
    int temp = ui->optionOfFillingpixelsOutOfImage->text().toInt(&ok3);

    options::optionsOfPixelsFillingOutsideOfImage option=static_cast<options::optionsOfPixelsFillingOutsideOfImage>(temp);


    if (ok1 && ok2 && ok3)
    {
        Blur::blurGauss(imageHandle,sizeOfMask,sigma,option);
        load_modified_image(imageHandle.getImage());
    }
    else
    {
        QMessageBox::warning(this, "Error", "Please provide valid values for mask size, sigma and pixel fill option.");
    }

}

QImage MainWindowQt::blackAndWhite()
{
    on_greyScale_clicked();

    QImage imagemap = imageHandle.getImage();
    int imageWidth=imageHandle.getWidth();
    int imageHeight=imageHandle.getHeight();

    for (int i = 0; i < imageHeight; ++i)
    {
        for (int j = 0; j < imageWidth; ++j)
        {

            QColor pixel=imagemap.pixelColor(j,i);
            if(pixel.lightness()>=128)
            {
                imagemap.setPixelColor(j,i,Qt::black);
            }
            else
            {
                imagemap.setPixelColor(j,i,Qt::white);
            }

        }

    }
    return imagemap;
}

void MainWindowQt::on_Save_as_clicked()
{
    QImage imagemap = imageHandle.getImage();
    int imageWidth=imageHandle.getWidth();
    int imageHeight=imageHandle.getHeight();

    QString selectedFilter;
    QString fileName = QFileDialog::getSaveFileName(nullptr,"Save image","","Binary PPM (*.ppm);;Binary PGM (*.pgm);;Binary PBM (*.pbm);;ASCII PPM (*.ppm);;ASCII PGM (*.pgm);;ASCII PBM (*.pbm)",&selectedFilter);

    if (fileName.isEmpty())
        return;

    if (selectedFilter.contains("ASCII PPM"))
    {

        std::ofstream fileHandler;
        fileHandler.open(fileName.toStdString());

        fileHandler << "P3\n";
        fileHandler << imageWidth << " " << imageHeight << "\n";
        fileHandler << "255\n";

        for (int i = 0; i < imageHeight; ++i)
        {
            for (int j = 0; j < imageWidth; ++j)
            {
                QColor pixel=imagemap.pixelColor(j,i);
                fileHandler<<pixel.red()<<" "<<pixel.green()<<" "<<pixel.blue()<<" ";
            }
            fileHandler<<"\n";
        }

        fileHandler.close();

    }
    else if(selectedFilter.contains("ASCII PGM"))
    {
        on_greyScale_clicked();

        QImage imagemap = imageHandle.getImage();
        int imageWidth=imageHandle.getWidth();
        int imageHeight=imageHandle.getHeight();

        std::ofstream fileHandler;
        fileHandler.open(fileName.toStdString());

        fileHandler << "P2\n";
        fileHandler << imageWidth << " " << imageHeight << "\n";
        fileHandler << "255\n";

        for (int i = 0; i < imageHeight; ++i)
        {
            for (int j = 0; j < imageWidth; ++j)
            {
                QColor pixel=imagemap.pixelColor(j,i);
                fileHandler<<pixel.lightness()<<" ";
            }
            fileHandler<<"\n";
        }

        fileHandler.close();
    }
    else if(selectedFilter.contains("ASCII PBM"))
    {
        std::ofstream fileHandler;
        fileHandler.open(fileName.toStdString());

        fileHandler << "P1\n";
        fileHandler << imageWidth << " " << imageHeight << "\n";

        QImage imagemap= blackAndWhite();
        for (int i = 0; i < imageHeight; ++i)
        {
            for (int j = 0; j < imageWidth; ++j)
            {
                QColor pixel=imagemap.pixelColor(j,i);
                if(pixel==Qt::black)
                    fileHandler<<1<<" ";
                else
                    fileHandler<<0<<" ";
            }
            fileHandler<<"\n";
        }

        fileHandler.close();
    }
    else if(selectedFilter.contains("Binary PPM"))
    {
        QImage imagemap = imageHandle.getImage();
        imagemap.save(fileName,"ppm");
    }
    else if(selectedFilter.contains("Binary PGM"))
    {
        on_greyScale_clicked();
        QImage imagemap = imageHandle.getImage();
        imagemap.save(fileName,"pgm");
    }
    else if(selectedFilter.contains("Binary PBM"))
    {
        QImage imagemap= blackAndWhite();
        imagemap.save(fileName,"pbm");
    }


}


void MainWindowQt::on_pushButton_clicked()
{
    QImage imagemap = EdgeGradient::transform(imageHandle,options::cyclicPixels);
    load_modified_image(imagemap);
}

