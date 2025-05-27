#include "convolution.h"

// zwraca maske/macierz size*size z jedynką w środku
QVector<QVector<float>> Convolution::getMask(unsigned int size)
{

    QVector<QVector<float>> mask = QVector<QVector<float>>(size,QVector<float>(size,0.0f));
    unsigned int center = static_cast<unsigned int>(size /2);
    mask[center][center] = 1.0f;
    return mask;
}







