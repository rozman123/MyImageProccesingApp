#ifndef LAPLASJAN_H
#define LAPLASJAN_H

#include <QVector>

namespace Laplasjan
{
    static inline QVector<QVector<float>>& getLaplasjanMask(unsigned int& size)
    {
        static QVector<QVector<float>> laplasjanMask(size,QVector<float>(-1));
        unsigned short center=size/2+1;
        laplasjanMask[center][center]=size*size-1;
        return laplasjanMask;
    };



};

#endif // LAPLASJAN_H
