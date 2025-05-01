#ifndef BLUR_H
#define BLUR_H

#include <QImage>


class Blur
{
private:

    enum optionsOfPixelsFillingOutsideOfImage{cyclicPixels,blackPixels,repeatPixels};

public:
    Blur();
    QRgb getPixel(const QImage& image, int x, int y, optionsOfPixelsFillingOutsideOfImage option);
    QVector<QVector<int> > getWindow(const QImage& image, int x, int y,int size, int channel, optionsOfPixelsFillingOutsideOfImage option);
    QVector<QVector<float> > getMask(int size);
    QVector<QVector<float> > join(const QVector<QVector<int>>& a, const QVector<QVector<float>>& b);
    float sum(const QVector<QVector<float> >& matrix);
    QVector<QVector<float> > reflection(const QVector<QVector<float>>& matrix);
    QImage convolute(const QImage& image, const QVector<QVector<float>>& mask, int channel, optionsOfPixelsFillingOutsideOfImage option);
    void on_rozmycieRownomierne_clicked();
    void on_rozmycieGausowskie_clicked();
};

#endif // BLUR_H
