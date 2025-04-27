

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
    QString pathToFile = QFileDialog::getOpenFileName(this,"Load Image","","Images (*.png *.jpeg *.jpg *.bmp *.pbm *.pgm *.ppm *)");

    if(pathToFile.isEmpty())
    {
        return;
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
    MainWindowQt::on_histogram_clicked();
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
    MainWindowQt::on_histogram_clicked();
    QImage imagemap = image;

    unsigned long allPixels = imageWidth * imageHeight;

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
            QColor pixel = image.pixelColor(i, j);

            imagemap.setPixelColor(i, j, QColor(redLUT[pixel.red()], greenLUT[pixel.green()], blueLUT[pixel.blue()],lumLUT[pixel.lightness()]));

        }
    }

    loadModifiedImage(imagemap);
    MainWindowQt::on_histogram_clicked();
}


// zwraca pixel na danym miejscu, potrzebna do zwracania
// pixeli poza obrazem w przypadku maski
QRgb MainWindowQt::getPixel(const QImage& image, int x, int y, optionsOfPixelsFillingOutsideOfImage option)
{
    if(option==0)
    {
        x = (x + imageWidth) % imageWidth;
        y = (y + imageHeight) % imageHeight;
        return image.pixel(x, y);
    }
    else if(option==1)
    {
        if (x < 0 || x >= imageWidth || y < 0 || y >= imageHeight)
            return qRgb(0, 0, 0);
        return image.pixel(x, y);
    }
    else if(option==2)
    {
        x = std::clamp(x, 0, imageWidth - 1);
        y = std::clamp(y, 0, imageHeight - 1);
        return image.pixel(x, y);
    }
    return qRgb(0, 0, 0);
}

// zwraca macierz pixeli/ (pixele somsiadujace z danym pikselem) na danym kanale
QVector<QVector<int>> MainWindowQt::getWindow(const QImage& image, int x, int y,int size,int channel, optionsOfPixelsFillingOutsideOfImage option)
{
    QVector<QVector<int>> window(size, QVector<int>(size, 0));
    int offset = size / 2;

    for (int dy = -offset; dy <= offset; ++dy) {
        for (int dx = -offset; dx <= offset; ++dx) {
            QRgb pixel = getPixel(image, x + dx, y + dy, option);
            QColor color(pixel);

            int value = 0;
            switch (channel)
            {
                case 0: value = color.red(); break;
                case 1: value = color.green(); break;
                case 2: value = color.blue(); break;
                default: value = color.lightness(); break;
            }

            window[dy + offset][dx + offset] = value;
        }
    }

    return window;
}

// zwraca maske/macierz size*size z jedynką w środku
QVector<QVector<float> > MainWindowQt::getMask(int size)
{
    QVector<QVector<float>> mask(size, QVector<float>(size, 0.0f));
    int center = size / 2;
    mask[center][center] = 1.0f;
    return mask;
}

//wykonuje iloczyn macierzy element po elemencie
QVector<QVector<float> > MainWindowQt::join(const QVector<QVector<int>>& a, const QVector<QVector<float>>& b)
{
    int rows = a.size();
    int cols = a[0].size();
    QVector<QVector<float>> result(rows, QVector<float>(cols));
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            result[i][j] = a[i][j] * b[i][j];
    return result;
}
//sumuje wszystkie wartości w macierzy
float MainWindowQt::sum(const QVector<QVector<float> >& matrix)
{
    float total = 0.0f;
    for (const auto& row : matrix)
        for (float val : row)
            total += val;
    return total;
}

//zwraca lustrzane odbicie maski
QVector<QVector<float> > MainWindowQt::reflection(const QVector<QVector<float>>& matrix) {
    int size = matrix.size();
    QVector<QVector<float>> result(size, QVector<float>(size));
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            result[i][j] = matrix[size - 1 - i][size - 1 - j];
    return result;
}

QImage MainWindowQt::convolute(const QImage& image, const QVector<QVector<float>>& mask, int channel, optionsOfPixelsFillingOutsideOfImage option)
{
    int width = image.width();
    int height = image.height();
    int maskSize = mask.size();
    float weight = sum(mask);

    QImage result = image;

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            auto window = getWindow(image, x, y,maskSize, channel, option);
            auto joined = join(window, mask);
            float accumulator = sum(joined);
            if (weight != 0) accumulator /= weight;
            int finalValue = std::clamp(static_cast<int>(accumulator), 0, 255);
            QColor color = result.pixelColor(x, y);
            switch (channel)
            {
            case 0: color.setRed(finalValue); break;
            case 1: color.setGreen(finalValue); break;
            case 2: color.setBlue(finalValue); break;
            default: color = QColor(finalValue, finalValue, finalValue); break;
            }
            result.setPixelColor(x, y, color);
        }
    }

    return result;
}


// wykonuje operację splotu na obrazie/uwzględniając konkretny kanał
void MainWindowQt::on_rozmycieRownomierne_clicked()
{
    bool ok1=false;
    bool ok2=false;
    int sizeOfMask=ui->maskSize->text().toInt(&ok1);
    int option1=ui->optionOfFillingpixelsOutOfImage->text().toInt(&ok2);

    optionsOfPixelsFillingOutsideOfImage option = cyclicPixels;

    switch(option1)
    {
    case 0: { option = cyclicPixels; break;}
    case 1: { option = blackPixels; break;}
    case 2: { option = repeatPixels; break;}
    default: { option = cyclicPixels; break;}
    }


    if (ok1&&ok2)
    {
        QVector<QVector<float>> mask(sizeOfMask, QVector<float>(sizeOfMask, 1.0f / (sizeOfMask * sizeOfMask)));

        QImage imagemap=image;
        // przetwarza każdy kanał RGB osobno
        for (int channel = 0; channel < 4; ++channel)
        {
            QImage blurred = convolute(imagemap, mask, channel, option);

            for (int y = 0; y < imageHeight; ++y)
            {
                for (int x = 0; x < imageWidth; ++x)
                {
                    QColor original = imagemap.pixelColor(x, y);
                    QColor blurredColor = blurred.pixelColor(x, y);

                    // Ustawiamy tylko rozmyty kanał, pozostałe zostają bez zmian
                    switch (channel)
                    {
                    case 0: original.setRed(blurredColor.red()); break;
                    case 1: original.setGreen(blurredColor.green()); break;
                    case 2: original.setBlue(blurredColor.blue()); break;
                    case 3:
                    {
                        QColor hsl = original.toHsl();
                        hsl.setHsl(hsl.hue(), hsl.saturation(), blurredColor.lightness());
                        original = hsl.toRgb();
                        break;
                    }
                    }

                    imagemap.setPixelColor(x, y, original);
                }
            }
        }
        loadModifiedImage(imagemap);

    }
    else
    {
        QMessageBox::warning(this, "Error", "You must give a size of mask on left and a number of the filling of pixels outside of image for this operation!");
    }
}

//funkcja z obliczaniem gausa
float gaussFunction(float x, float y, float sigma)
{
    float coefficient = 1.0f / (2.0f * M_PI * sigma * sigma);
    float exponent = -(x * x + y * y) / (2.0f * sigma * sigma);
    return coefficient * std::exp(exponent);
}

//tworzy maske gausa
QVector<QVector<float>> getGaussianMask(int size, float sigma)
{
    QVector<QVector<float>> mask(size, QVector<float>(size));
    int center = size / 2;
    float total = 0.0f;

    for (int y = 0; y < size; ++y)
    {
        for (int x = 0; x < size; ++x)
        {
            float gaussValue = gaussFunction(x - center, y - center, sigma);
            mask[y][x] = gaussValue;
            total += gaussValue;
        }
    }

    // nrmalizacja maski// suma elementów to 1
    for (int y = 0; y < size; ++y)
    {
        for (int x = 0; x < size; ++x)
        {
            mask[y][x] /= total;
        }
    }

    return mask;
}

void MainWindowQt::on_rozmycieGausowskie_clicked()
{
    bool ok1 = false, ok2 = false, ok3 = false;
    int sizeOfMask = ui->maskSize->text().toInt(&ok1);
    float sigma = ui->sigma->text().toFloat(&ok2);
    int option1 = ui->optionOfFillingpixelsOutOfImage->text().toInt(&ok3);

    optionsOfPixelsFillingOutsideOfImage option = cyclicPixels;
    switch(option1)
    {
    case 0: option = cyclicPixels; break;
    case 1: option = blackPixels; break;
    case 2: option = repeatPixels; break;
    default: option = cyclicPixels; break;
    }

    if (ok1 && ok2 && ok3)
    {
        QVector<QVector<float>> mask = getGaussianMask(sizeOfMask, sigma);

        QImage imagemap = image;
        for (int channel = 0; channel < 4; ++channel)
        {
            QImage blurred = convolute(imagemap, mask, channel, option);

            for (int y = 0; y < imageHeight; ++y)
            {
                for (int x = 0; x < imageWidth; ++x)
                {
                    QColor original = imagemap.pixelColor(x, y);
                    QColor blurredColor = blurred.pixelColor(x, y);

                    switch (channel)
                    {
                        case 0: original.setRed(blurredColor.red()); break;
                        case 1: original.setGreen(blurredColor.green()); break;
                        case 2: original.setBlue(blurredColor.blue()); break;
                        case 3:
                        {
                            QColor hsl = original.toHsl();
                            hsl.setHsl(hsl.hue(), hsl.saturation(), blurredColor.lightness());
                            original = hsl.toRgb();
                            break;
                        }
                    }

                    imagemap.setPixelColor(x, y, original);
                }
            }
        }
        loadModifiedImage(imagemap);
    }
    else
    {
        QMessageBox::warning(this, "Error", "Please provide valid values for mask size, sigma and pixel fill option.");
    }

}

QImage MainWindowQt::blackAndWhite()
{
    on_greyScale_clicked();
    QImage imagemap=image;
    for (int i = 0; i < imageHeight; ++i)
    {
        for (int j = 0; j < imageWidth; ++j)
        {

            QColor pixel=image.pixelColor(j,i);
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
                QColor pixel=image.pixelColor(j,i);
                fileHandler<<pixel.red()<<" "<<pixel.green()<<" "<<pixel.blue()<<"\n";
            }

        }

        fileHandler.close();

    }
    else if(selectedFilter.contains("ASCII PGM"))
    {
        on_greyScale_clicked();
        std::ofstream fileHandler;
        fileHandler.open(fileName.toStdString());

        fileHandler << "P2\n";
        fileHandler << imageWidth << " " << imageHeight << "\n";
        fileHandler << "255\n";

        for (int i = 0; i < imageHeight; ++i)
        {
            for (int j = 0; j < imageWidth; ++j)
            {
                QColor pixel=image.pixelColor(j,i);
                fileHandler<<pixel.lightness()<<"\n";
            }

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
                fileHandler<<pixel.lightness()<<"\n";  // źle jest to zapisywane do pliku bo mają być tylko 1 i 0
            }
        }

        fileHandler.close();
    }
    else if(selectedFilter.contains("Binary PPM"))
    {
        image.save(fileName.toStdString().c_str(),"ppm");
    }
    else if(selectedFilter.contains("Binary PGM"))
    {
        on_greyScale_clicked();
        image.save(fileName.toStdString().c_str(),"pgm");
    }
    else if(selectedFilter.contains("Binary PBM"))
    {
        QImage imagemap= blackAndWhite();
        imagemap.save(fileName.toStdString().c_str(),"pbm");
    }


}

