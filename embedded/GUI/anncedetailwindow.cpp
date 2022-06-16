#include "anncedetailwindow.h"
#include "ui_anncedetailwindow.h"

anncedetailwindow::anncedetailwindow(QString anncePath, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::anncedetailwindow)
{
    ui->setupUi(this);
    this->anncePath = anncePath;
    this->audioFilePath = getAudioFilePath(anncePath);

    /* set title, producer, announceTime, content */
    parsingAnnceFile(anncePath);
    ui->title->setText(this->title);
    ui->producer->setText(QString("방송자: ") + this->producer);
    ui->announceTime->setText(QString("방송 시각: ") + this->announceTime);
    ui->content->setText(this->content);

    player->setMedia(QUrl::fromLocalFile(audioFilePath));
    player->setVolume(100);

    /* connect button */
    connect(ui->back, SIGNAL(clicked()), this, SLOT(back_clicked()));
    connect(ui->replay, SIGNAL(clicked()), this, SLOT(replay_clicked()));
    connect(ui->play, SIGNAL(clicked()), this, SLOT(play_clicked()));
    connect(ui->seekBar, SIGNAL(sliderMoved(int)), this, SLOT(seekBar_sliderMoved(int)));
    connect(ui->volumeBar, SIGNAL(valueChanged(int)),this, SLOT(volumeBar_valueChanged(int)));
    connect(updater, SIGNAL(timeout()), this, SLOT(update()));

    player->play();
    updater->start();
}

anncedetailwindow::~anncedetailwindow()
{
    delete ui;
}

void anncedetailwindow::parsingAnnceFile(QString annceFilePath){
    JSON_Value *rootValue;
    JSON_Object *rootObject;

    rootValue = json_parse_file(annceFilePath.toLocal8Bit().data());
    rootObject = json_value_get_object(rootValue);

    this->title = QString(json_object_get_string(rootObject, "title"));
    this->producer = QString(json_object_get_string(rootObject, "producer"));
    this->content = QString(json_object_get_string(rootObject, "textData"));
    this->announceTime = QString(json_object_get_string(rootObject, "announceTime"));
}

QString anncedetailwindow::getAudioFilePath(QString annceFilePath){
    JSON_Value *rootValue;
    JSON_Object *rootObject;
    QString rv;

    rootValue = json_parse_file(annceFilePath.toLocal8Bit().data());
    rootObject = json_value_get_object(rootValue);

    rv += json_object_get_string(rootObject, "VOICE_FILE_PATH");

    return rv;
}

void anncedetailwindow::play_clicked()
{
    if(player->state() == QMediaPlayer::PlayingState)
        player->pause();
   else
        player->play();
}

void anncedetailwindow::back_clicked()
{
    this->close();
}

void anncedetailwindow::seekBar_sliderMoved(int progress)
{
    player->setPosition(this->player->duration() / 1000 * progress);
    player->play();
}

void anncedetailwindow::volumeBar_valueChanged(int value)
{
    player->setVolume(value);
}

void anncedetailwindow::replay_clicked()
{
       player->setPosition(0);
       player->play();

}

void anncedetailwindow::update()
{
    if(!ui->seekBar->isSliderDown())
        ui->seekBar->setValue((double)player->position()/player->duration() * 1000);
}
