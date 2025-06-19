#include "binarization.h"
#include <QHash>
#include <cmath>
#include "mainwindowqt.h"
#include <math.h>

QImage& Binariztion::manual_binarization(Image& imageHandle,int threshold)
{

    QImage& imagemap = imageHandle.getImage();
    int imageWidth=imageHandle.getWidth();
    int imageHeight=imageHandle.getHeight();

    for (int i=0;i<imageWidth;++i)
    {
        for (int j=0;j<imageHeight;++j)
        {
            QColor color = imagemap.pixelColor(i,j);
            if (color.lightness()>threshold)
            {
                imagemap.setPixel(i,j,qRgb(255,255,255));
            }
            else
            {
                imagemap.setPixel(i,j,qRgb(0,0,0));
            }

        }
    }
    return imagemap;

}


double wyznaczProgGradientowy(const QImage& image)
{


    int width = image.width();
    int height = image.height();

    double licznik = 0.0;
    double mianownik = 0.0;

    for (int y = 1; y < height - 1; ++y) {
        const uchar* prev = image.scanLine(y - 1);
        const uchar* curr = image.scanLine(y);
        const uchar* next = image.scanLine(y + 1);

        for (int x = 1; x < width - 1; ++x) {
            int gx = next[x] - prev[x];             // Gx pyerwsza linia
            int gy = curr[x + 1] - curr[x - 1];      // Gy droga linia
            int gmax = std::max(std::abs(gx), std::abs(gy));

            licznik += gmax * curr[x];
            mianownik += gmax;
        }
    }

    return (mianownik != 0.0) ? (licznik / mianownik) : 0.0;
}


QImage& Binariztion::auto_binarization(Image& imageHandle)
{
    QImage& imagemap=imageHandle.getImage();

    int threshold = static_cast<int>(wyznaczProgGradientowy(imagemap));

    imagemap = manual_binarization(imageHandle,threshold);

    return imagemap;

}

int wyznaczProgBimodalny(const QHash<int, int>& lum)
{
    int T = 128; // prug startowy
    int Tnew = T;

    do {
        T = Tnew;

        // obliczennie u0 i u1
        double sum0 = 0.0, sum1 = 0.0;
        double count0 = 0.0, count1 = 0.0;

        for (int i = 0; i < T; ++i) {
            int h = lum.value(i, 0);
            sum0 += h * i;
            count0 += h;
        }

        for (int i = T; i < 256; ++i) {
            int h = lum.value(i, 0);
            sum1 += h * i;
            count1 += h;
        }

        double mu0 = (count0 > 0.0) ? (sum0 / count0) : 0.0;
        double mu1 = (count1 > 0.0) ? (sum1 / count1) : 0.0;

        // owy prug
        Tnew = static_cast<int>((mu0 + mu1) / 2.0);

    } while (Tnew != T);

    return Tnew;
}

QImage& Binariztion::bimodal_binarization(Image& imageHandle)
{

    int threshold = static_cast<int>(wyznaczProgBimodalny(imageHandle.getHistogram().getLumosityChanel()));

    QImage&  imagemap = manual_binarization(imageHandle,threshold);

    return imagemap;

}

int wyznaczProgOtsu(const QHash<int, int>& histo)
{
    double maxEta = -1.0;
    int najlepszyProg = 0;


    // wstępne sumy
    QVector<int> h(256, 0);
    for (int i = 0; i < 256; ++i)
        h[i] = histo.value(i, 0);

    // tablice sum czesciowych
    QVector<double> sumaH(256, 0.0);
    QVector<double> sumaHi(256, 0.0);

    sumaH[0] = h[0];
    sumaHi[0] = h[0] * 0;
    for (int i = 1; i < 256; ++i) {
        sumaH[i] = sumaH[i - 1] + h[i];
        sumaHi[i] = sumaHi[i - 1] + h[i] * i;
    }

    double sumaHCalkowita = sumaH[255];
    double sumaHiCalkowita = sumaHi[255];

    for (int t = 1; t < 255; ++t) {
        double P0 = sumaH[t - 1] / sumaHCalkowita;
        double P1 = 1.0 - P0;

        if (P0 == 0.0 || P1 == 0.0) continue;

        double mu0 = sumaHi[t - 1] / sumaH[t - 1];
        double mu1 = (sumaHiCalkowita - sumaHi[t - 1]) / (sumaHCalkowita - sumaH[t - 1]);

        double eta = P0 * P1 * (mu0 - mu1) * (mu0 - mu1);

        if (eta > maxEta) {
            maxEta = eta;
            najlepszyProg = t;
        }
    }

    return najlepszyProg;
}

QImage& Binariztion::otsu_binarization(Image& imageHandle)
{

    int threshold = static_cast<int>(wyznaczProgOtsu(imageHandle.getHistogram().getLumosityChanel()));

    QImage&  imagemap = manual_binarization(imageHandle,threshold);

    return imagemap;

}

QImage Binariztion::niblack_binarization(Image& image, int windowSize, double alpha, options::outOfImagePixelFilling fillOption, int channel)
{
    QImage result(image.getHeight(), image.getHeight(), QImage::Format_Grayscale8);

    for (int y = 0; y < image.getHeight(); ++y)
    {
        uchar* dst = result.scanLine(y);// tu jest pointer do lini
        for (int x = 0; x < image.getHeight(); ++x)
        {

            // pobiar a okno
            QVector<QVector<float>> okno = image.getWindow(x, y, windowSize, channel, fillOption);

            // oblicza srednia i odhylenie standardowee
            double suma = 0.0;
            double sumaKwadratow = 0.0;
            int licznik = 0;

            for (const auto& wiersz : okno)
            {
                for (float val : wiersz) {
                    suma += val;

                    ++licznik;
                }
            }
            double srednia = suma / licznik;
            for (const auto& wiersz : okno)
            {
                for (float val : wiersz)
                {
                    sumaKwadratow += pow(val - srednia,2);
                }
            }



            double wariancja = sumaKwadratow/(licznik-1);
            double odchylenie = std::sqrt(wariancja);

            // poblicz próg t(x, y)
            double prog = srednia + alpha * odchylenie;

            // sprawdz wartośc centralnego pixela
            float wartość = image.getWindow(x, y, 1, channel, fillOption)[0][0]; // pojedynczy piksel

            dst[x] = (wartość > prog) ? 255 : 0; // tu jest pointer do lini
        }
    }

    return result;
}



