/********************************************************************************
** Form generated from reading UI file 'emrgcallwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EMRGCALLWINDOW_H
#define UI_EMRGCALLWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_emrgcallwindow
{
public:
    QLabel *description;
    QPushButton *back;
    QLabel *emrgicon;

    void setupUi(QWidget *emrgcallwindow)
    {
        if (emrgcallwindow->objectName().isEmpty())
            emrgcallwindow->setObjectName(QString::fromUtf8("emrgcallwindow"));
        emrgcallwindow->resize(800, 600);
        emrgcallwindow->setStyleSheet(QString::fromUtf8("background-color: rgb(245, 245, 249);"));
        description = new QLabel(emrgcallwindow);
        description->setObjectName(QString::fromUtf8("description"));
        description->setGeometry(QRect(0, 400, 800, 100));
        description->setAutoFillBackground(false);
        description->setStyleSheet(QString::fromUtf8("\n"
"color: rgb(25, 25, 25);\n"
"font: bold 20px"));
        description->setAlignment(Qt::AlignCenter);
        back = new QPushButton(emrgcallwindow);
        back->setObjectName(QString::fromUtf8("back"));
        back->setGeometry(QRect(10, 520, 780, 70));
        back->setStyleSheet(QString::fromUtf8("border-radius: 10px;\n"
"background-color: rgb(105, 108, 255);\n"
"color: beige;\n"
"font: bold 25px\n"
""));
        emrgicon = new QLabel(emrgcallwindow);
        emrgicon->setObjectName(QString::fromUtf8("emrgicon"));
        emrgicon->setGeometry(QRect(0, 0, 800, 400));
        emrgicon->setStyleSheet(QString::fromUtf8("font: 700 48pt \"NanumBarunGothic\";"));
        emrgicon->setPixmap(QPixmap(QString::fromUtf8(":/icon/emrgicon.png")));
        emrgicon->setAlignment(Qt::AlignCenter);

        retranslateUi(emrgcallwindow);

        QMetaObject::connectSlotsByName(emrgcallwindow);
    } // setupUi

    void retranslateUi(QWidget *emrgcallwindow)
    {
        emrgcallwindow->setWindowTitle(QCoreApplication::translate("emrgcallwindow", "Form", nullptr));
        description->setText(QCoreApplication::translate("emrgcallwindow", "\353\263\264\355\230\270\354\236\220\353\245\274 \352\270\264\352\270\211 \355\230\270\354\266\234\355\225\230\354\230\200\354\212\265\353\213\210\353\213\244.", nullptr));
        back->setText(QCoreApplication::translate("emrgcallwindow", "\353\213\253\352\270\260", nullptr));
        emrgicon->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class emrgcallwindow: public Ui_emrgcallwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EMRGCALLWINDOW_H
