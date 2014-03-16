#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    screen = new QArithMaxScreen(this);
    screen->show();
    this->setCentralWidget(screen);
    AMThread = new QAMThread(screen);
    AMThread->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}
