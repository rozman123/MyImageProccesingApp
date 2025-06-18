#include "binarization.h"


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









