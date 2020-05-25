#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QColorDialog>
#include <QMessageBox>
#include <QFileDialog>
#include <imagebmp.h>
#include "mygraphicsview.h"
#include "info.h"
#include "help.h"

#define DRAW_TR 3

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QColor color1;
    QColor color2;

private slots:
    void selection();

    void on_color1_clicked();

    void on_color2_clicked();

    void on_cancel_clicked();    

    void on_ok_clicked();

    void on_ok_2_clicked();

    void on_actionOpen_triggered();

    void on_actionSave_as_triggered();

    void on_ok_3_clicked();

    void on_color1_2_clicked();

    void on_color2_2_clicked();

    void on_actionInfo_triggered();

    void on_actionHelp_triggered();

private:
    int button_pressed = 0;
    MyGraphicView* picture;
    QString path;
    ImageBmp* bmp;
    char tmp[15] = "tmp.bmp";
    Ui::MainWindow *ui;
    Info* Inform;
    Help* help;
};

#endif // MAINWINDOW_H
