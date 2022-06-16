#include "anncelistwindow.h"
#include "ui_anncelistwindow.h"
#include "parson.h"
#include <dirent.h>
#include <QDebug>

anncelistwindow::anncelistwindow(int anncetype, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::anncelistwindow)
{
    this->anncetype = anncetype;
    ui->setupUi(this);

    /* set back button to return main page when clicked */
    connect(ui->back, SIGNAL(clicked()), this, SLOT(back_clicked()));
    /* set annce item to show annce page when clicked */
    connect(ui->annceList,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(ItemClicked(QListWidgetItem*)));

    /* set title, annceitems as stated by anncetype */
    QString titleTxt;
    if (this->anncetype == VILLAGE){
        titleTxt = tr("마을") + tr(" 방송");
        if(!getAnnceFiles(VILLAGE_INFO_FILE_PATH))
            perror("");
    }
    else
    {
        titleTxt = tr("재난") + tr(" 방송");
        if(!getAnnceFiles(DISASTER_INFO_FILE_PATH))
            perror("");
    }

    /* set Text: title, annceitems*/
    ui->title->setText(titleTxt);
    int cnt = 1;
    for (auto file : annceList){
        ui->annceList->addItem(QString::number(cnt) + QString(". ") + parsingAnnceFile(file));
        ++cnt;
    }

}

QString anncelistwindow::parsingAnnceFile(QString annceFilePath){
    JSON_Value *rootValue;
    JSON_Object *rootObject;
    QString rv;

    rootValue = json_parse_file(annceFilePath.toLocal8Bit().data());
    rootObject = json_value_get_object(rootValue);

    rv += json_object_get_string(rootObject, "announceTime");
    rv += "  ";
    rv += json_object_get_string(rootObject, "producer");
    rv += "  ";
    rv += json_object_get_string(rootObject, "title");

    return rv;
}

bool anncelistwindow::getAnnceFiles(const char *path){
    DIR *dir;
    struct dirent *diread;

    dir = opendir(path);
    if (dir == nullptr){
        perror ("opendir-dir");
        return false;
    }

    diread = readdir(dir); // remove . directory
    diread = readdir(dir); // remove .. directory

    while ((diread = readdir(dir)) != nullptr) {
        annceList.push_back(QString(path)+QString("/")+QString(diread->d_name));
    }
    closedir (dir);

    return true;
}

anncelistwindow::~anncelistwindow()
{
    delete ui;
}

void anncelistwindow::back_clicked()
{
    this->close();
}

void anncelistwindow::ItemClicked(QListWidgetItem *item){

    QStringList list = item->data(0).toString().split(".");
    annceDetailWindow = new anncedetailwindow(annceList[list[0].toUInt()-1]);
    annceDetailWindow->show();
}
