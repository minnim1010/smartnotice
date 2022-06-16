/********************************************************************************
** Form generated from reading UI file 'anncedetailwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ANNCEDETAILWINDOW_H
#define UI_ANNCEDETAILWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_anncedetailwindow
{
public:
    QLabel *title;
    QLabel *content;
    QPushButton *replay;
    QPushButton *back;
    QLabel *producer;
    QLabel *announceTime;
    QSlider *seekBar;
    QSlider *volumeBar;
    QPushButton *play;

    void setupUi(QWidget *anncedetailwindow)
    {
        if (anncedetailwindow->objectName().isEmpty())
            anncedetailwindow->setObjectName(QString::fromUtf8("anncedetailwindow"));
        anncedetailwindow->resize(600, 500);
        anncedetailwindow->setStyleSheet(QString::fromUtf8("background-color: rgb(245, 245, 249);"));
        title = new QLabel(anncedetailwindow);
        title->setObjectName(QString::fromUtf8("title"));
        title->setGeometry(QRect(0, 0, 600, 60));
        QFont font;
        font.setPointSize(40);
        title->setFont(font);
        title->setStyleSheet(QString::fromUtf8("\n"
"color: rgb(25, 25, 25);"));
        title->setAlignment(Qt::AlignCenter);
        content = new QLabel(anncedetailwindow);
        content->setObjectName(QString::fromUtf8("content"));
        content->setGeometry(QRect(10, 130, 580, 221));
        QFont font1;
        font1.setPointSize(25);
        content->setFont(font1);
        content->setStyleSheet(QString::fromUtf8("\n"
"color: rgb(25, 25, 25);"));
        content->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        replay = new QPushButton(anncedetailwindow);
        replay->setObjectName(QString::fromUtf8("replay"));
        replay->setGeometry(QRect(10, 450, 275, 40));
        QFont font2;
        font2.setBold(true);
        font2.setItalic(false);
        replay->setFont(font2);
        replay->setStyleSheet(QString::fromUtf8("border-radius: 10px;\n"
"background-color: rgb(105, 108, 255);\n"
"color: beige;\n"
"font: bold 20px\n"
""));
        back = new QPushButton(anncedetailwindow);
        back->setObjectName(QString::fromUtf8("back"));
        back->setGeometry(QRect(315, 450, 275, 40));
        back->setFont(font2);
        back->setStyleSheet(QString::fromUtf8("border-radius: 10px;\n"
"background-color: rgb(105, 108, 255);\n"
"color: beige;\n"
"font: bold 20px\n"
""));
        producer = new QLabel(anncedetailwindow);
        producer->setObjectName(QString::fromUtf8("producer"));
        producer->setGeometry(QRect(10, 70, 260, 51));
        QFont font3;
        font3.setPointSize(20);
        producer->setFont(font3);
        producer->setStyleSheet(QString::fromUtf8("\n"
"color: rgb(25, 25, 25);"));
        producer->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        announceTime = new QLabel(anncedetailwindow);
        announceTime->setObjectName(QString::fromUtf8("announceTime"));
        announceTime->setGeometry(QRect(290, 70, 300, 51));
        announceTime->setFont(font3);
        announceTime->setStyleSheet(QString::fromUtf8("\n"
"color: rgb(25, 25, 25);"));
        announceTime->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        seekBar = new QSlider(anncedetailwindow);
        seekBar->setObjectName(QString::fromUtf8("seekBar"));
        seekBar->setGeometry(QRect(10, 370, 579, 20));
        seekBar->setMouseTracking(true);
        seekBar->setFocusPolicy(Qt::NoFocus);
        seekBar->setAcceptDrops(false);
        seekBar->setStyleSheet(QString::fromUtf8("background-color: rgb(109, 108, 110);\n"
"color: rgb(25, 25, 25);"));
        seekBar->setMaximum(1000);
        seekBar->setOrientation(Qt::Horizontal);
        volumeBar = new QSlider(anncedetailwindow);
        volumeBar->setObjectName(QString::fromUtf8("volumeBar"));
        volumeBar->setGeometry(QRect(470, 400, 121, 20));
        volumeBar->setFocusPolicy(Qt::NoFocus);
        volumeBar->setMaximum(100);
        volumeBar->setValue(100);
        volumeBar->setOrientation(Qt::Horizontal);
        volumeBar->setInvertedAppearance(false);
        volumeBar->setInvertedControls(false);
        play = new QPushButton(anncedetailwindow);
        play->setObjectName(QString::fromUtf8("play"));
        play->setGeometry(QRect(10, 400, 31, 31));
        play->setFocusPolicy(Qt::NoFocus);
        play->setStyleSheet(QString::fromUtf8("\n"
"color: rgb(25, 25, 25);"));
        play->setCheckable(true);
        play->setChecked(true);

        retranslateUi(anncedetailwindow);

        QMetaObject::connectSlotsByName(anncedetailwindow);
    } // setupUi

    void retranslateUi(QWidget *anncedetailwindow)
    {
        anncedetailwindow->setWindowTitle(QCoreApplication::translate("anncedetailwindow", "Form", nullptr));
        title->setText(QString());
        content->setText(QString());
        replay->setText(QCoreApplication::translate("anncedetailwindow", "\353\213\244\354\213\234 \353\223\243\352\270\260", nullptr));
        back->setText(QCoreApplication::translate("anncedetailwindow", "\353\213\253\352\270\260", nullptr));
        producer->setText(QString());
        announceTime->setText(QString());
        play->setText(QCoreApplication::translate("anncedetailwindow", "O", nullptr));
    } // retranslateUi

};

namespace Ui {
    class anncedetailwindow: public Ui_anncedetailwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ANNCEDETAILWINDOW_H
