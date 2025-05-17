#include "laplasjan.h"

QVector<QVector<float>> Laplasjan::getLaplasjanMask(unsigned int size)
{
    QVector<QVector<float>> laplasjanMask(size,QVector<float>(size,-1));
    unsigned short center=size/2+1;
    laplasjanMask[center][center]=size*size-1;
    return laplasjanMask;
};

QImage Laplasjan::LaplasjanConvolute(Image& image,unsigned int maskSize,options::outOfImagePixelFilling option)
{
    QVector<QVector<float>> mask=getLaplasjanMask(maskSize);
    int imageWidth = image.getWidth();
    int imageHeight = image.getHeight();


    QImage imagemap;
    for (int channel = 0; channel < 4; ++channel)
    {
        imagemap=Blur::convolute(image,mask,channel,option);


        for (int y = 0; y < imageHeight; ++y)
        {
            for (int x = 0; x < imageWidth; ++x)
            {
                QColor original = image.getImage().pixelColor(x, y);
                QColor EdgeDetectionColor = imagemap.pixelColor(x, y);

                // Ustawiamy tylko rozmyty kanał, pozostałe zostają bez zmian
                switch (channel)
                {
                    case 0: original.setRed(EdgeDetectionColor.red()); break;
                    case 1: original.setGreen(EdgeDetectionColor.green()); break;
                    case 2: original.setBlue(EdgeDetectionColor.blue()); break;
                    case 3:
                    {
                        QColor hsl = original.toHsl();
                        hsl.setHsl(hsl.hue(), hsl.saturation(), EdgeDetectionColor.lightness());
                        original = hsl.toRgb();
                        break;
                    }
                }

                imagemap.setPixelColor(x, y, original);
            }
        }
    }

    return imagemap;

}


// QImage Laplasjan::transformLaplasjan(Image& image,int maskSize, options::outOfImagePixelFilling option)
// {


//     QImage imagemap = image.getImage();

//     short imageHeight=image.getHeight();
//     short imageWidth=image.getWidth();


//     QImage verticalEdges = LaplasjanConvolute(image,maskSize,option);
//     QImage horizontalEdges = LaplasjanConvolute(image,maskSize,option);

//     for (int y = 0; y < imageHeight; ++y)
//     {
//         for (int x = 0; x < imageWidth; ++x)
//         {
//             QColor original = imagemap.pixelColor(x, y);

//             QColor edgeColorX = horizontalEdges.pixelColor(x, y);
//             QColor edgeColorY = verticalEdges.pixelColor(x, y);


//             QColor newColor = sqrt(pow(edgeColorX.red(),2)+pow(edgeColorY.red(),2));
//             original.setRed(newColor.red());

//             newColor = sqrt(pow(edgeColorX.green(),2)+pow(edgeColorY.green(),2));
//             original.setGreen(newColor.green());

//             newColor = sqrt(pow(edgeColorX.blue(),2)+pow(edgeColorY.blue(),2));
//             original.setBlue(newColor.blue());

//             newColor = sqrt(pow(edgeColorX.lightness(),2)+pow(edgeColorY.lightness(),2));
//             QColor hsl = original.toHsl();
//             hsl.setHsl(hsl.hue(), hsl.saturation(), newColor.lightness());
//             original = hsl.toRgb();


//             imagemap.setPixelColor(x, y, original);
//         }
//     }



//     return imagemap;

// }
