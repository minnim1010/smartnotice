#ifndef EMRGCALLWINDOW_H
#define EMRGCALLWINDOW_H

#include <QWidget>
#include "info.h"

namespace Ui {
class emrgcallwindow;
}

class emrgcallwindow : public QWidget
{
    Q_OBJECT

public:
    explicit emrgcallwindow(QWidget *parent = nullptr);
    void emergcall();
    ~emrgcallwindow();

public slots:
    void back_clicked();

private:
    Ui::emrgcallwindow *ui;
};

#endif // EMRGCALLWINDOW_H
