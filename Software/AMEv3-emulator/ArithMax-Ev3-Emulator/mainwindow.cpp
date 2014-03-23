#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    screen = new QArithMaxScreen(ui->verticalWidget_2);
    ui->verticalLayout_2->addWidget(screen);
    screen->show();
    //this->setCentralWidget(screen);
    kbd = new Keyboard(ui->verticalWidget);
    ui->verticalLayout_3->addWidget(kbd);
    kbd->show();
    AMThread = new QAMThread(screen);
    AMThread->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}
