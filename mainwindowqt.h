#ifndef MAINWINDOWQT_H
#define MAINWINDOWQT_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QImage>

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
};
#endif // MAINWINDOWQT_H
