#ifndef MAINWINDOWQT_H
#define MAINWINDOWQT_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QImage>
#include <sys/stat.h>
#include <sys/types.h>
#include "image.h"
#include "edgegradient.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindowQt;
}
QT_END_NAMESPACE

class MainWindowQt : public QMainWindow
{
    Q_OBJECT

private:

    Image imageHandle;
    Ui::MainWindowQt *ui;
    QGraphicsScene *scene;

public:
    MainWindowQt(QWidget *parent = nullptr);
    ~MainWindowQt();

private slots:
    void on_loadImage_clicked();
    void on_negative_clicked();
    void on_greyScale_clicked();
    void on_Contrast_clicked();
    void on_Gamma_clicked();
    void on_Brightnes_clicked();
    void on_histogram_clicked();
    void on_Stretching_clicked();
    void on_wyrownanie_clicked();
    void on_Save_as_clicked();
    void load_modified_image(QImage & image_to_load);
    void on_rozmycieRownomierne_clicked();
    void on_rozmycieGausowskie_clicked();
    QImage blackAndWhite();

    void on_EdgeDetection_clicked();
};
#endif // MAINWINDOWQT_H
