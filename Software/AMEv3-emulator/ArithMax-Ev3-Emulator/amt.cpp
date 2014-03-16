
#include "qamthread.h"

#include "stdio.h"

#include <QtCore>

extern "C"{
    unsigned char *ScreenBuffer;
    int AMTlastkey;
    void UpdateScreenBuffer()
    {
        amtinst->US();
        //printf("\n Screen Updated \n");
    }
    void AMTSleep(unsigned long ms)
    {
        amtinst->msleep(ms);
    }
    void AMTUSleep(unsigned long us)
    {
        amtinst->usleep(us);
    }
    void AMTUnSche()
    {
    }
    unsigned char AcquireKey()
    {
        while(amtinst->screen->keysLocked || amtinst->screen->keys.length() == 0);
        amtinst->screen->keysLocked = true;
        unsigned char tmp = (unsigned char)amtinst->screen->keys.at(0);
        amtinst->screen->keys.removeAt(0);
        amtinst->screen->keysLocked = false;
        return tmp;
    }
}
