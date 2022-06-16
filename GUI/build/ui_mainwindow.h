/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QToolButton *emrgcall;
    QToolButton *vilAnnce;
    QToolButton *dsstAnnce;
    QToolButton *setting;
    QLabel *user;
    QLabel *datetime;
    QLabel *title;
    QLabel *currentTemp;
    QLabel *weatherDetail;
    QLabel *notice;
    QLabel *weathertxt;
    QLabel *currentTemp_2;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: rgb(245, 245, 249);"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setStyleSheet(QString::fromUtf8("background-color: rgb(245, 245, 249);"));
        emrgcall = new QToolButton(centralwidget);
        emrgcall->setObjectName(QString::fromUtf8("emrgcall"));
        emrgcall->setGeometry(QRect(0, 360, 266, 240));
        QFont font;
        font.setFamily(QString::fromUtf8("NanumBarunGothic"));
        font.setPointSize(36);
        font.setBold(true);
        emrgcall->setFont(font);
        emrgcall->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 211, 220);\n"
"color: rgb(25, 25, 25);"));
        vilAnnce = new QToolButton(centralwidget);
        vilAnnce->setObjectName(QString::fromUtf8("vilAnnce"));
        vilAnnce->setGeometry(QRect(266, 360, 268, 240));
        vilAnnce->setFont(font);
        vilAnnce->setMouseTracking(false);
        vilAnnce->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 240, 207);\n"
"color: rgb(25, 25, 25);"));
        dsstAnnce = new QToolButton(centralwidget);
        dsstAnnce->setObjectName(QString::fromUtf8("dsstAnnce"));
        dsstAnnce->setGeometry(QRect(534, 360, 266, 240));
        dsstAnnce->setFont(font);
        dsstAnnce->setStyleSheet(QString::fromUtf8("background-color: rgb(207, 237, 236);\n"
"color: rgb(25, 25, 25);"));
        setting = new QToolButton(centralwidget);
        setting->setObjectName(QString::fromUtf8("setting"));
        setting->setGeometry(QRect(720, 30, 63, 30));
        QFont font1;
        font1.setFamily(QString::fromUtf8("NanumBarunGothic"));
        font1.setBold(true);
        font1.setItalic(false);
        setting->setFont(font1);
        setting->setStyleSheet(QString::fromUtf8("color: rgb(25, 25, 25);\n"
"background-color: rgb(104, 103, 105);\n"
"border-radius: 10px;\n"
"color: beige;\n"
"font: bold 15px\n"
""));
        user = new QLabel(centralwidget);
        user->setObjectName(QString::fromUtf8("user"));
        user->setGeometry(QRect(610, 0, 91, 90));
        QFont font2;
        font2.setFamily(QString::fromUtf8("NanumBarunGothic"));
        font2.setPointSize(13);
        user->setFont(font2);
        user->setStyleSheet(QString::fromUtf8("color: rgb(25, 25, 25);"));
        user->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        datetime = new QLabel(centralwidget);
        datetime->setObjectName(QString::fromUtf8("datetime"));
        datetime->setGeometry(QRect(270, 90, 500, 60));
        QFont font3;
        font3.setFamily(QString::fromUtf8("NanumBarunGothic"));
        font3.setPointSize(20);
        font3.setBold(false);
        datetime->setFont(font3);
        datetime->setStyleSheet(QString::fromUtf8("color: rgb(25, 25, 25);\n"
"border-bottom-color: rgb(26, 26, 26);"));
        datetime->setAlignment(Qt::AlignCenter);
        title = new QLabel(centralwidget);
        title->setObjectName(QString::fromUtf8("title"));
        title->setEnabled(true);
        title->setGeometry(QRect(0, 0, 800, 90));
        QFont font4;
        font4.setFamily(QString::fromUtf8("NanumBarunGothic"));
        font4.setPointSize(25);
        font4.setBold(true);
        title->setFont(font4);
        title->setStyleSheet(QString::fromUtf8("color: rgb(25, 25, 25);\n"
"border-bottom-color: rgb(26, 26, 26);"));
        title->setAlignment(Qt::AlignCenter);
        currentTemp = new QLabel(centralwidget);
        currentTemp->setObjectName(QString::fromUtf8("currentTemp"));
        currentTemp->setGeometry(QRect(20, 150, 110, 110));
        QFont font5;
        font5.setFamily(QString::fromUtf8("NanumBarunGothic"));
        font5.setPointSize(50);
        currentTemp->setFont(font5);
        currentTemp->setStyleSheet(QString::fromUtf8("color: rgb(25, 25, 25);"));
        currentTemp->setAlignment(Qt::AlignCenter);
        weatherDetail = new QLabel(centralwidget);
        weatherDetail->setObjectName(QString::fromUtf8("weatherDetail"));
        weatherDetail->setGeometry(QRect(20, 250, 220, 110));
        QFont font6;
        font6.setFamily(QString::fromUtf8("NanumBarunGothic"));
        font6.setPointSize(20);
        weatherDetail->setFont(font6);
        weatherDetail->setStyleSheet(QString::fromUtf8("color: rgb(25, 25, 25);"));
        weatherDetail->setAlignment(Qt::AlignCenter);
        notice = new QLabel(centralwidget);
        notice->setObjectName(QString::fromUtf8("notice"));
        notice->setGeometry(QRect(270, 150, 500, 210));
        QFont font7;
        font7.setPointSize(20);
        notice->setFont(font7);
        notice->setStyleSheet(QString::fromUtf8("color: rgb(25, 25, 25);"));
        notice->setAlignment(Qt::AlignCenter);
        weathertxt = new QLabel(centralwidget);
        weathertxt->setObjectName(QString::fromUtf8("weathertxt"));
        weathertxt->setGeometry(QRect(20, 90, 220, 60));
        weathertxt->setFont(font3);
        weathertxt->setStyleSheet(QString::fromUtf8("color: rgb(25, 25, 25);\n"
"border-bottom-color: rgb(26, 26, 26);"));
        weathertxt->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        currentTemp_2 = new QLabel(centralwidget);
        currentTemp_2->setObjectName(QString::fromUtf8("currentTemp_2"));
        currentTemp_2->setGeometry(QRect(130, 150, 110, 110));
        QFont font8;
        font8.setFamily(QString::fromUtf8("NanumBarunGothic"));
        font8.setPointSize(30);
        currentTemp_2->setFont(font8);
        currentTemp_2->setStyleSheet(QString::fromUtf8("color: rgb(25, 25, 25);"));
        currentTemp_2->setAlignment(Qt::AlignCenter);
        MainWindow->setCentralWidget(centralwidget);
        title->raise();
        emrgcall->raise();
        vilAnnce->raise();
        dsstAnnce->raise();
        setting->raise();
        user->raise();
        datetime->raise();
        currentTemp->raise();
        weatherDetail->raise();
        notice->raise();
        weathertxt->raise();
        currentTemp_2->raise();

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        emrgcall->setText(QCoreApplication::translate("MainWindow", "\352\270\264\352\270\211 \355\230\270\354\266\234", nullptr));
        vilAnnce->setText(QCoreApplication::translate("MainWindow", "\353\247\210\354\235\204 \353\260\251\354\206\241", nullptr));
        dsstAnnce->setText(QCoreApplication::translate("MainWindow", "\354\236\254\353\202\234 \353\260\251\354\206\241", nullptr));
        setting->setText(QCoreApplication::translate("MainWindow", "\354\204\244\354\240\225", nullptr));
        user->setText(QString());
        datetime->setText(QString());
        title->setText(QCoreApplication::translate("MainWindow", "\354\212\244\353\247\210\355\212\270 \353\247\210\354\235\204 \354\225\214\353\246\274 \354\213\234\354\212\244\355\205\234", nullptr));
        currentTemp->setText(QCoreApplication::translate("MainWindow", "24\302\260", nullptr));
        weatherDetail->setText(QCoreApplication::translate("MainWindow", "\354\265\234\354\240\200:14\302\260 \354\265\234\352\263\240:28\302\260", nullptr));
        notice->setText(QCoreApplication::translate("MainWindow", "\355\230\204\354\236\254 \354\213\244\353\202\264 \354\230\250\353\217\204\353\212\224 14\302\260\354\236\205\353\213\210\353\213\244.\n"
" \354\266\224\354\232\260\354\213\234\353\213\244\353\251\264 \354\230\250\353\217\204\353\245\274 \354\241\260\352\270\210 \354\230\254\353\240\244\354\243\274\354\204\270\354\232\224!", nullptr));
        weathertxt->setText(QCoreApplication::translate("MainWindow", "\354\230\244\353\212\230 \353\202\240\354\224\250", nullptr));
        currentTemp_2->setText(QCoreApplication::translate("MainWindow", "\355\235\220\353\246\274", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
