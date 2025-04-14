#include "histogram.h"

Histogram::Histogram()
{
    for(int i=0;i<=255;++i)
    {
        Red.insert(i,0);
        Green.insert(i,0);
        Blue.insert(i,0);
        Lumosity.insert(i,0);
    }
}
