#ifndef MAINWINDOWQT_H
#define MAINWINDOWQT_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QImage>
#include "histogram.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <filesystem>
#include <fstream>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindowQt;
}
QT_END_NAMESPACE

class MainWindowQt : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindowQt *ui;
    QGraphicsScene *scene;
    QImage image;  // stores image data
    int imageWidth=0;
    int imageHeight=0;
    Histogram histogram;
    enum optionsOfPixelsFillingOutsideOfImage{cyclicPixels,blackPixels,repeatPixels};

public:
    MainWindowQt(QWidget *parent = nullptr);
    ~MainWindowQt();

private slots:
    void on_loadImage_clicked();
    void loadImage(QString pathToImage);
    void loadModifiedImage(QImage image_to_load);
    void on_negative_clicked();
    void on_greyScale_clicked();
    void on_Contrast_clicked();
    void on_Gamma_clicked();
    void on_Brightnes_clicked();
    void on_histogram_clicked();
    void on_Stretching_clicked();
    void on_wyrownanie_clicked();
    QRgb getPixel(const QImage& image, int x, int y, optionsOfPixelsFillingOutsideOfImage option);
    QVector<QVector<int> > getWindow(const QImage& image, int x, int y,int size, int channel, optionsOfPixelsFillingOutsideOfImage option);
    QVector<QVector<float> > getMask(int size);
    QVector<QVector<float> > join(const QVector<QVector<int>>& a, const QVector<QVector<float>>& b);
    float sum(const QVector<QVector<float> >& matrix);
    QVector<QVector<float> > reflection(const QVector<QVector<float>>& matrix);
    QImage convolute(const QImage& image, const QVector<QVector<float>>& mask, int channel, optionsOfPixelsFillingOutsideOfImage option);
    void on_rozmycieRownomierne_clicked();
    void on_rozmycieGausowskie_clicked();
    void on_Save_as_clicked();
};
#endif // MAINWINDOWQT_H
