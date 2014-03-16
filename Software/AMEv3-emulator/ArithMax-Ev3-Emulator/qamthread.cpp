#include "qamthread.h"
#include <cstdlib>
#include <iostream>

QAMThread *amtinst;

extern "C" int AMTlastkey;

QAMThread::QAMThread(QArithMaxScreen *s, QObject *parent) :
    QThread(parent),screen(s)
{
    amtinst = this;
    connect(this,SIGNAL(UpdateScreen()),s,SLOT(update()),Qt::QueuedConnection);
    ScreenBuffer = (unsigned char *)this->screen->ScreenData;
    //AMTlastkey = &(s->lastkey);
}

extern "C" int amt_main(void);

void QAMThread::run()
{
    /*for(;;)
    {
        for(int i = 0;i<12;i++)
        {
            for(int j = 0;j<31;j++)
                screen->ScreenData[i][j] = (unsigned char) (std::rand() % 256);
        }
        UpdateScreen();
        std::cerr << "Updated Screen" << std::endl;
        this->sleep(1);
    }*/
    amt_main();
}

void QAMThread::US()
{
    UpdateScreen();
}
