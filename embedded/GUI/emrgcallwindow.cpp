#include "emrgcallwindow.h"
#include "ui_emrgcallwindow.h"
#include <unistd.h>

emrgcallwindow::emrgcallwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::emrgcallwindow)
{
    ui->setupUi(this);

    /* set back button to return main page when clicked */
    connect(ui->back, SIGNAL(clicked()), this, SLOT(back_clicked()));
    emergcall();
}

//run Emergency call program
void emrgcallwindow::emergcall()
{
    pid_t pid;
    char *arg[] = {EMERGCALL_PROGRAM_PATH, NULL};

    pid = fork();

    if(pid == 0){
        printf("pid=%d, I'm child\n", pid);
        execv(arg[0], NULL);
        exit(0);
    }
    else if (pid > 0){
        printf("pid=%d, I'm parent\n", pid);
    }
    else
        printf("fork returned error, no child\n");
}

emrgcallwindow::~emrgcallwindow()
{
    delete ui;
}

void emrgcallwindow::back_clicked()
{
    this->close();
}
