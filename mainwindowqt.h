#ifndef MAINWINDOWQT_H
#define MAINWINDOWQT_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindowQt;
}
QT_END_NAMESPACE

class MainWindowQt : public QMainWindow
{
    Q_OBJECT

public:
    MainWindowQt(QWidget *parent = nullptr);
    ~MainWindowQt();

private:
    Ui::MainWindowQt *ui;
};
#endif // MAINWINDOWQT_H
