#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "anncelistwindow.h"
#include "emrgcallwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void set_time();
    void vilAnnce_clicked();
    void dsstAnnce_clicked();
    void emrgcall_clicked();


private:
    Ui::MainWindow *ui;
    QTimer *timer;
    anncelistwindow *annceListWindow;
    emrgcallwindow *emrgCallWindow;
};
#endif // MAINWINDOW_H
