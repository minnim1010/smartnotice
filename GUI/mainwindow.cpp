#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /* set style */
    this->setStyleSheet("background-color: yellow;");
    this->setStyleSheet("color: white;");

    /* set time */
    set_time();
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(set_time()));
    timer->start(1000);

    /* set username */
    QString usertxt(tr("단주민") + tr("님"));
    ui->user->setText(usertxt);

    /* set vilAnnce button to create vilAnncelistwindow when clicked*/
    connect(ui->vilAnnce, SIGNAL(clicked()), this, SLOT(vilAnnce_clicked()));

    /* set dsstAnnce button to create dsstAnncelistwindow when clicked*/
    connect(ui->dsstAnnce, SIGNAL(clicked()), this, SLOT(dsstAnnce_clicked()));

    /* set emrgcall button to create emrgcallWindow when clicked*/
    connect(ui->emrgcall, SIGNAL(clicked()), this, SLOT(emrgcall_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::set_time()
{
    QString time_format = "yyyy년 MM월 dd일 (ddd) HH:mm:ss";
    QDateTime datetime = QDateTime::currentDateTime();
    QString datetimetxt = datetime.toString(time_format);

    ui -> datetime-> setText(datetimetxt);
}

void MainWindow::vilAnnce_clicked()
{
    annceListWindow = new anncelistwindow(VILLAGE);
    annceListWindow->show();
}

void MainWindow::dsstAnnce_clicked()
{
    annceListWindow = new anncelistwindow(DISASTER);
    annceListWindow->show();
}

void MainWindow::emrgcall_clicked()
{
    emrgCallWindow = new emrgcallwindow();
    emrgCallWindow->show();
}
