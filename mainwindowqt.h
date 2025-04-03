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

public:
    MainWindowQt(QWidget *parent = nullptr);
    ~MainWindowQt();


private slots:
    void on_loadImage_clicked();
    void loadImage(QString pathToImage);


};
#endif // MAINWINDOWQT_H
