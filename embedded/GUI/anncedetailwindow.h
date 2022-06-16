#ifndef ANNCEDETAILWINDOW_H
#define ANNCEDETAILWINDOW_H

#include <QWidget>
#include <QtMultimedia/QMediaPlayer>
#include <QTimer>
#include "parson.h"
#include "info.h"

namespace Ui {
class anncedetailwindow;
}

class anncedetailwindow : public QWidget
{
    Q_OBJECT

public:
    explicit anncedetailwindow(QString anncePath, QWidget *parent = nullptr);
    ~anncedetailwindow();
    QString getAudioFilePath(QString annceFilePath);
    void parsingAnnceFile(QString annceFilePath);

public slots:
    void back_clicked();
    void play_clicked();
    void seekBar_sliderMoved(int progress);
    void volumeBar_valueChanged(int value);
    void replay_clicked();
    void update();

private:
    Ui::anncedetailwindow *ui;
    QTimer *updater = new QTimer(this);
    QMediaPlayer *player = new QMediaPlayer();
    QString anncePath;
    QString audioFilePath;
    QString title, producer, announceTime, content;
};

#endif // ANNCEDETAILWINDOW_H
