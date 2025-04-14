#ifndef HISTOGRAM_H
#define HISTOGRAM_H
#include <qhash.h>

class Histogram
{
private:
    static QHash<int, int> Red, Green, Blue, Lumosity;
public:
    Histogram();
    static void addValueToHistogram(int red,int green, int blue, int lumosity);
};

#endif // HISTOGRAM_H
