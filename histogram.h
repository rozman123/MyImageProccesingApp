#ifndef HISTOGRAM_H
#define HISTOGRAM_H
#include <qhash.h>
#include <qimage.h>

class Histogram
{
private:
    static QHash<int, int> Red, Green, Blue, Lumosity;
public:
    Histogram();
    static void generate(QImage image);
};

#endif // HISTOGRAM_H
