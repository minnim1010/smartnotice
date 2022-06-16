#include "mainwindow.h"
#include <QApplication>
#include <cstdio>
#include <unistd.h>
#include <signal.h>

//run receptBroadcast program
void receptBroadcast()
{
    pid_t pid;

    pid = fork();

    if(pid == 0){
        if (DEBUG){
            printf("[DEBUG] receptBroadcast program start! \n");
        }
        execl(RECEPT_BROADCAST_PROGRAM_PATH, NULL);
        exit(0);
    }
    else if (pid < 0)
        printf("fork returned error, no child\n");
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.resize(800, 600);
    w.show();
    receptBroadcast();

    return a.exec();
}
