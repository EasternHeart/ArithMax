#include "arithmaxscreen.h"
#include <QPaintEvent>
#include <QPainter>
#include <cstdlib>
#include <iostream>

extern "C" {extern int AMTlastkey;}

QArithMaxScreen::QArithMaxScreen(QWidget *parent) :
    QWidget(parent), keysLocked(QMutex::Recursive)
{
    for(int i = 0;i<12;i++)
    {
        for(int j = 0;j<31;j++)
            ScreenData[i][j] = (unsigned char) (std::rand() % 256);
    }
    //grabKeyboard();
    //keysLocked = new QSemaphore(1);
    //keysLocked = false;
}

void QArithMaxScreen::paintEvent(QPaintEvent *event)
{
    QSize size = this->size();
    QPainter painter(this);
    int xperpoint = size.width() / 96;
    int yperpoint = size.height() / 31;
    for(int i = 0;i<12;i++)
    {
        for(int j = 0;j<32;j++)
        {
#define DRAWPOINT(a) do{ \
            painter.save(); \
            if(ScreenData[i][j] & (1 << a) ) painter.setPen(QColor(0,0,0)); else painter.setPen(QColor(255,255,255)); \
            painter.fillRect((i*8+ a ) * xperpoint,j * yperpoint,xperpoint,yperpoint, \
                ( (ScreenData[i][j] & (1 << a)) ? QColor(0,0,0) : QColor(255,255,255) )); \
            painter.restore(); \
            }while(0)
            DRAWPOINT(0);
            DRAWPOINT(1);
            DRAWPOINT(2);
            DRAWPOINT(3);
            DRAWPOINT(4);
            DRAWPOINT(5);
            DRAWPOINT(6);
            DRAWPOINT(7);
#undef DRAWPOINT
        }
    }

    //std::cerr << "\nUpdated\n" << std::endl;

}

