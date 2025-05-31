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
QVector<QVector<float>> Convolution::join(QVector<QVector<int>> matrixA, QVector<QVector<float>> matrixB)
{
    unsigned int size = matrixA.size();
    QVector<QVector<float>> AxB(size,QVector<float>(size,0));

    for(unsigned int i = 0;i<size;++i)
        for(unsigned int j = 0;j<size;++j)
            AxB[i][j]+=matrixA[i][j]*matrixB[j][i];

    return AxB;
}

// QVector<QVector<QRgb>> Convolution::accumaulate(QVector<QVector<QRgb>> matrixA, QVector<QVector<float>> matrixB)
// {
//     unsigned int size = matrixA.size();
//     QVector<QVector<QRgb>> AxB(size,QVector<QRgb>(size,0));

//     for (short chanel=0;chanel<options::chanelsNumber;++chanel)
//         for(unsigned int i = 0;i<size;++i)
//             for(unsigned int j = 0;j<size;++j)
//                 AxB[i][j]+=matrixA[i][j]*matrixB[j][i];

//     return AxB;
// }


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


QImage& Convolution::convloute(const QVector<QVector<float> >& mask, Image& image, options::outOfImagePixelFilling pixelOption)
{
    QImage& convoluted_image=image.getImage();

    int maskWeight= sumMatrix(mask);
    const int maskSize=mask.size();
    const unsigned int height=image.getHeight();
    const unsigned int width=image.getWidth();

    for (short chanel=0;chanel<options::chanelsNumber;++chanel)
        for(int width_pos=0;width_pos<width;++width_pos)
            for(int height_pos=0;height_pos<height;++height_pos)
            {
                QVector<QVector<QColor>> window=image.getWindow(width_pos,height_pos,maskSize,pixelOption);
                //QVector<int> acumulator_vectior =



            }

    return convoluted_image;
}



