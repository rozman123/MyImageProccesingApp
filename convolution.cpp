#include "convolution.h"

// zwraca maske/macierz size*size z jedynką w środku
QVector<QVector<float>> Convolution::getMask(unsigned int size)
{

    QVector<QVector<float>> mask = QVector<QVector<float>>(size,QVector<float>(size,0.0f));
    unsigned int center = static_cast<unsigned int>(size /2);
    mask[center][center] = 1.0f;
    return mask;
}

//wykonuje iloczyn macierzy element po elemencie
QVector<QVector<float>> Convolution::join(QVector<QVector<float>> matrixA, QVector<QVector<float>> matrixB)
{
    unsigned int size = matrixA.size();
    QVector<QVector<float>> AxB(size,QVector<float>(size,0));

    for(unsigned int i = 0;i<size;++i)
        for(unsigned int j = 0;j<size;++j)
            AxB[i][j]+=matrixA[i][j]*matrixB[j][i];

    return AxB;
}


//zwraca lustrzane odbicie maski
QVector<QVector<float>> Convolution::reflectionMatrix(const QVector<QVector<float> >& matrix)
{
    unsigned int size=matrix.size();
    QVector<QVector<float>>  reflectedMatrix(size,QVector<float>(size,0));

    for( int i=0;i<size;++i)
        for(int j=0;j<size;++j)
            reflectedMatrix[size-i][size-j]=matrix[i][j];

    return reflectedMatrix;
}



//sumuje wszystkie wartości w macierzy
float Convolution::sumMatrix(const QVector<QVector<float> >& matrix)
{
    float sum = 0.0f;
    unsigned int size=matrix.size();
    for(unsigned int i = 0;i<size;++i)
        for(unsigned int j = 0;j<size;++j)
            sum+=matrix[i][j];
    return sum;
}

//sumuje wszystkie wartości w macierzy w danych kanałach
QVector<float> Convolution::sumMatrix(std::array<QVector<QVector<float>>,options::chanelsNumber>& matrix)
{
    QVector<float> sum(options::chanelsNumber,0.0f);
    unsigned int size=matrix[0].size();
    for(short chanel =0;chanel<options::chanelsNumber;++chanel)
        for(unsigned int i = 0;i<size;++i)
            for(unsigned int j = 0;j<size;++j)
                sum[chanel]+=matrix[chanel][i][j];
    return sum;
}
std::array<QVector<QVector<float>>,options::chanelsNumber> Convolution::accumaulate(QVector<QVector<QColor>> matrixA, QVector<QVector<float>> matrixB)
{
    unsigned int size = matrixA.size();
    std::array<QVector<QVector<float>>,options::chanelsNumber> AxB={QVector<QVector<float>>(size,QVector<float>(size,0.0f)),QVector<QVector<float>>(size,QVector<float>(size,0.0f)),QVector<QVector<float>>(size,QVector<float>(size,0.0f)),QVector<QVector<float>>(size,QVector<float>(size,0.0f))};

        for(unsigned int i = 0;i<size;++i)
            for(unsigned int j = 0;j<size;++j)
            {

                AxB[options::chanel::RED][i][j]+=matrixA[i][j].red()*matrixB[j][i];
                AxB[options::chanel::GREEN][i][j]+=matrixA[i][j].green()*matrixB[j][i];
                AxB[options::chanel::BLUE][i][j]+=matrixA[i][j].blue()*matrixB[j][i];

                QColor hsl = matrixA[i][j].toHsl();
                AxB[options::chanel::LUMINOSITY][i][j] += hsl.lightness()*matrixB[j][i];

            }

    return AxB;
}


QImage& Convolution::convolute(const QVector<QVector<float> >& mask, Image& image, options::outOfImagePixelFilling pixelOption)
{
    QImage& convoluted_image=image.getImage();

    int maskWeight= sumMatrix(mask);
    const int maskSize=mask.size();
    const unsigned int height=image.getHeight();
    const unsigned int width=image.getWidth();


        for(int width_pos=0;width_pos<width;++width_pos)
            for(int height_pos=0;height_pos<height;++height_pos)
            {
                QVector<QVector<QColor>> window=image.getWindow(height_pos,width_pos,maskSize,pixelOption);
                std::array<QVector<QVector<float>>,options::chanelsNumber> joined_vector_of_matrixes = accumaulate(window,mask);
                QVector<float> sumedMatrixes = sumMatrix(joined_vector_of_matrixes);

                if (maskWeight!=0)
                    for (auto &suma:sumedMatrixes)
                        suma=std::clamp(static_cast<int>(suma/=maskWeight), 0, 255);

                QColor pixelColor;

                pixelColor.setRed(std::clamp(static_cast<int>(sumedMatrixes[options::chanel::RED]), 0, 255));
                pixelColor.setGreen(std::clamp(static_cast<int>(sumedMatrixes[options::chanel::GREEN]), 0, 255));
                pixelColor.setBlue(std::clamp(static_cast<int>(sumedMatrixes[options::chanel::BLUE]), 0, 255));

                QColor hsl = pixelColor.toHsl();
                hsl.setHsl(hsl.hue(), hsl.saturation(), std::clamp(static_cast<int>(sumedMatrixes[options::chanel::LUMINOSITY]), 0, 255));
                pixelColor = hsl.toRgb();

                convoluted_image.setPixelColor(height_pos,width_pos,pixelColor);
            }

    return convoluted_image;
}



