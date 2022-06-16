/********************************************************************************
** Form generated from reading UI file 'anncelistwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ANNCELISTWINDOW_H
#define UI_ANNCELISTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_anncelistwindow
{
public:
    QListWidget *annceList;
    QLabel *title;
    QPushButton *back;

    void setupUi(QWidget *anncelistwindow)
    {
        if (anncelistwindow->objectName().isEmpty())
            anncelistwindow->setObjectName(QString::fromUtf8("anncelistwindow"));
        anncelistwindow->resize(800, 600);
        anncelistwindow->setStyleSheet(QString::fromUtf8("background-color: rgb(245, 245, 249);"));
        annceList = new QListWidget(anncelistwindow);
        annceList->setObjectName(QString::fromUtf8("annceList"));
        annceList->setGeometry(QRect(0, 90, 800, 510));
        QFont font;
        font.setFamily(QString::fromUtf8("NanumBarunGothic"));
        font.setPointSize(20);
        font.setBold(false);
        font.setItalic(false);
        annceList->setFont(font);
        annceList->setStyleSheet(QString::fromUtf8("font: 20pt \"NanumBarunGothic\";\n"
"\n"
"color: rgb(25, 25, 25);"));
        annceList->setSpacing(15);
        title = new QLabel(anncelistwindow);
        title->setObjectName(QString::fromUtf8("title"));
        title->setGeometry(QRect(0, 0, 800, 90));
        QFont font1;
        font1.setFamily(QString::fromUtf8("NanumBarunGothic"));
        font1.setPointSize(30);
        font1.setBold(true);
        title->setFont(font1);
        title->setStyleSheet(QString::fromUtf8("\n"
"color: rgb(25, 25, 25);"));
        title->setAlignment(Qt::AlignCenter);
        back = new QPushButton(anncelistwindow);
        back->setObjectName(QString::fromUtf8("back"));
        back->setGeometry(QRect(15, 20, 100, 50));
        QFont font2;
        font2.setFamily(QString::fromUtf8("NanumBarunGothic"));
        font2.setBold(true);
        font2.setItalic(false);
        back->setFont(font2);
        back->setStyleSheet(QString::fromUtf8("border-radius: 10px;\n"
"background-color: rgb(105, 108, 255);\n"
"color: beige;\n"
"font: bold 20px\n"
""));

        retranslateUi(anncelistwindow);

        QMetaObject::connectSlotsByName(anncelistwindow);
    } // setupUi

    void retranslateUi(QWidget *anncelistwindow)
    {
        anncelistwindow->setWindowTitle(QCoreApplication::translate("anncelistwindow", "Form", nullptr));
        title->setText(QString());
        back->setText(QCoreApplication::translate("anncelistwindow", "\353\217\214\354\225\204\352\260\200\352\270\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class anncelistwindow: public Ui_anncelistwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ANNCELISTWINDOW_H
