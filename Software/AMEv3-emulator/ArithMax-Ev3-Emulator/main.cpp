#include "mainwindow.h"
#include <QApplication>

#include <stdio.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
    setvbuf(stdout,NULL,_IONBF,0);

    return a.exec();
}
