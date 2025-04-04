#include "mainwindowqt.h"
#include "./ui_mainwindowqt.h"
#include <QFileDialog>
#include<QMessageBox>
MainWindowQt::MainWindowQt(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindowQt)
{
    scene = new QGraphicsScene(this);
    ui->setupUi(this);
    ui->imageSlot->setScene(scene);
}

MainWindowQt::~MainWindowQt()
{
    delete ui;
}

void MainWindowQt::on_loadImage_clicked()
{
    QString pathToFile = QFileDialog::getOpenFileName(this,"Load Image","","Images (*.png *.jpeg *.jpg *.bmp)");

    if(pathToFile.isEmpty())
    {
        QMessageBox::warning(this,"No File was Given!!","No file was given or given file does not exist","OK");
    }
    else
    {
        loadImage(pathToFile);
    }

}

void MainWindowQt::loadImage(QString pathToImage)
{
    scene->clear();

    image.load(pathToImage);
    if (!image.isNull())
    {
        QPixmap pixmap = QPixmap::fromImage(image);

        scene->addPixmap(pixmap);
        ui->imageSlot->fitInView(scene->itemsBoundingRect(), Qt::KeepAspectRatio);
    }
    else
    {
        QMessageBox::warning(this, "Error", "Failed to load image!");
    }




}


