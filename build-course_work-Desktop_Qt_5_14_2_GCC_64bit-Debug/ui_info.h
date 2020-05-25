/********************************************************************************
** Form generated from reading UI file 'info.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INFO_H
#define UI_INFO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Info
{
public:
    QWidget *widget;
    QGridLayout *gridLayout;
    QLabel *label;
    QLabel *Name;
    QLabel *label_2;
    QLabel *width;
    QLabel *label_3;
    QLabel *height;

    void setupUi(QDialog *Info)
    {
        if (Info->objectName().isEmpty())
            Info->setObjectName(QString::fromUtf8("Info"));
        Info->resize(400, 300);
        widget = new QWidget(Info);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(90, 90, 211, 101));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        Name = new QLabel(widget);
        Name->setObjectName(QString::fromUtf8("Name"));

        gridLayout->addWidget(Name, 0, 1, 1, 1);

        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        width = new QLabel(widget);
        width->setObjectName(QString::fromUtf8("width"));

        gridLayout->addWidget(width, 1, 1, 1, 1);

        label_3 = new QLabel(widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        height = new QLabel(widget);
        height->setObjectName(QString::fromUtf8("height"));

        gridLayout->addWidget(height, 2, 1, 1, 1);


        retranslateUi(Info);

        QMetaObject::connectSlotsByName(Info);
    } // setupUi

    void retranslateUi(QDialog *Info)
    {
        Info->setWindowTitle(QCoreApplication::translate("Info", "HELP", nullptr));
        label->setText(QCoreApplication::translate("Info", "Name File :", nullptr));
        Name->setText(QCoreApplication::translate("Info", "fafafafa", nullptr));
        label_2->setText(QCoreApplication::translate("Info", "Width :", nullptr));
        width->setText(QCoreApplication::translate("Info", "TextLabel", nullptr));
        label_3->setText(QCoreApplication::translate("Info", "Height :", nullptr));
        height->setText(QCoreApplication::translate("Info", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Info: public Ui_Info {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INFO_H
