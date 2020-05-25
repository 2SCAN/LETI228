#include "info.h"
#include "ui_info.h"

Info::Info(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Info)
{
    ui->setupUi(this);
}

Info::~Info()
{
    delete ui;
}

void Info::writeinformation(){
    ui->Name->setText(date.firsthelp.toLocal8Bit().constData());
    ui->width->setText(QString::number(date.width));
    ui->height->setText(QString::number(date.height));
};
