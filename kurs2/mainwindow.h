#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QColorDialog>
#include <QMessageBox>
#include <QFileDialog>
#include <imagebmp.h>



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

private:
    QString path;
    ImageBmp* bmp;
    char tmp[15] = "tmp.bmp";
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
