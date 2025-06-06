#ifndef OPTIONS_H
#define OPTIONS_H


namespace options
{
    enum outOfImagePixelFilling {cyclicPixels=0,blackPixels=1,repeatPixels=2};

    enum edgeDetectionOptions {Roberts=0,Prewitt=1,Sobel=2,Lapsjan=3,Zero=4,Canny=5};

    enum {chanelsNumber=4};

    enum chanel {RED=0,GREEN=1,BLUE=2,LUMINOSITY=3};

}


#endif // OPTIONS_H
