#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->x0->setValidator(new QIntValidator(0, 3000, this));
    ui->x1->setValidator(new QIntValidator(0, 3000, this));
    ui->x2->setValidator(new QIntValidator(0, 3000, this));
    ui->y0->setValidator(new QIntValidator(0, 3000, this));
    ui->y1->setValidator(new QIntValidator(0, 3000, this));
    ui->y2->setValidator(new QIntValidator(0, 3000, this));
    ui->N->setValidator(new QIntValidator(0, 50, this));
    ui->M->setValidator(new QIntValidator(0, 50, this));
    bmp = new ImageBmp;
    picture = new MyGraphicView;
}

MainWindow::~MainWindow()
{
    delete ui;
    delete bmp;
}

void MainWindow::on_color1_clicked()
{
    color1 = QColorDialog::getColor(Qt::black, this, "Выберите цвет");
}

void MainWindow::on_color2_clicked(){
    color2 = QColorDialog::getColor(Qt::black, this, "Выберите цвет");
}

void MainWindow::on_cancel_clicked(){
    ui->x0->clear();
    ui->x1->clear();
    ui->x2->clear();
    ui->y0->clear();
    ui->y1->clear();
    ui->y2->clear();
    ui->N->clear();
    ui->M->clear();
    ui->spinBox->setValue(1);
    ui->checkBox->setChecked(false);
    if(path != ""){
        //ImageBmp::deleteImage();
        int checher = bmp->loadImage(path.toLocal8Bit());
        ui->bmp->setPixmap(path);
    }

}
#include <QDebug>




void MainWindow::on_ok_clicked()
{
    if(path != ""){
        if(ui->x0->text() != "" && ui->x1->text() != "" && ui->x2->text() != "" && ui->y0->text() != "" && ui->y1->text() != "" && ui->y2->text() != ""){
            bmp->triangle(ui->y0->text().toInt(), ui->x0->text().toInt(), ui->y1->text().toInt(), ui->x1->text().toInt(), ui->y2->text().toInt(), ui->x2->text().toInt(), ui->spinBox->value(), ui->checkBox->isChecked(), color1, color2);
            //int checher = bmp->saveImage(tmp);
            //ui->bmp->setPixmap(QString(tmp));

            picture->update(bmp->getPixmap());
        } else{
             QMessageBox::about(this, "error", "Вы не ввели данные");
        }
    }
}

void MainWindow::on_ok_2_clicked()
{
    if(path!= ""){
        if(ui->N->text() != "" && ui->M->text() != ""){
            if(ui->N->text().toInt() * bmp->H >10000 || ui->M->text().toInt() * bmp->W > 10000){
                QMessageBox::about(this, "error", "BИзображение будет сильно большим");
            }
            bmp->collage(ui->N->text().toInt(), ui->M->text().toInt());
            int checher = bmp->saveImage(tmp);
            if(bmp->W > QWidget::width() ||bmp->H > QWidget::height()){
                ui->bmp->setScaledContents(true);
                ui->bmp->resize(QWidget::size());
            } else{
                ui->bmp->resize(bmp->W, bmp->H);
                ui->bmp->setScaledContents(true);
            }
            picture->update(bmp->getPixmap());
            //ui->bmp->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
            //ui->bmp->setPixmap(QString(tmp));
        }else{
            QMessageBox::about(this, "error", "Вы не ввели данные");
        }
    }
}


void MainWindow::on_actionOpen_triggered()
{
    path = QFileDialog::getOpenFileName(nullptr, "Open file", "..","*.bmp");
    if (path != ""){
        int checher = bmp->loadImage(path.toLocal8Bit());
        if(checher == 0){
            picture->update(bmp->getPixmap());
            ui->gridLayout->addWidget(picture);

        } else if(checher == -1){
             QMessageBox::about(this, "error", "unknow format bmp");
        } else if(checher == -2){
             QMessageBox::about(this, "error", "Unable to open blank image");
        } else if(checher == -3){
            QMessageBox::about(this, "error", "The path is entered incorrectly");
        }
    }
}

#include <QDebug>
void MainWindow::on_actionSave_as_triggered()
{
     path = QFileDialog::getSaveFileName(0, "Save as file", "..", "*bmp");
     if (path != ""){
         int checher = bmp->saveImage(path.toLocal8Bit());
         if(checher == 0){
             ui->bmp->setPixmap(path);
         } else if(checher == -1){
              QMessageBox::about(this, "error", "The path to save is entered incorrectly");
         } else if(checher == -2){
              QMessageBox::about(this, "error", "Unable to save blank image");
         }
     }
}

#include<QDebug>
void MainWindow::on_ok_3_clicked()
{
    if(path != ""){
        qDebug()<<color1.red()<<color1.green()<<color1.blue();
        bmp->recolor_rectangle(color1, color2);
        int checher = bmp->saveImage(tmp);
        ui->bmp->setPixmap(QString(tmp));
    }else{
        QMessageBox::about(this, "error", "Вы не ввели данные");
    }
}

void MainWindow::on_color1_2_clicked()
{
     color1 = QColorDialog::getColor(Qt::black, this, "Выберите цвет");
}

void MainWindow::on_color2_2_clicked()
{
     color2 = QColorDialog::getColor(Qt::black, this, "Выберите цвет");
}
