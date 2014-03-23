#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "arithmaxscreen.h"
#include <QThread>
#include "qamthread.h"
#include "keyboard.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;
    QArithMaxScreen *screen;
    QAMThread *AMThread;
    Keyboard *kbd;
};

#endif // MAINWINDOW_H
