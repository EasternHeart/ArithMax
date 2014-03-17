
#include "qamthread.h"

#include "stdio.h"

#include <QtCore>
#include <iostream>

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
        amtinst->MSleep(ms);
    }
    void AMTUSleep(unsigned long us)
    {
        amtinst->USleep(us);
    }
    void AMTUnSche()
    {
    }
    unsigned char AcquireKey()
    {
       // while(amtinst->screen->keysLocked || amtinst->screen->keys.length() == 0);
        loop:while(true)
        {
            while(amtinst->screen->keysLocked);
            amtinst->screen->keysLocked = true;
            if(!amtinst->screen->keys.empty())break;
            amtinst->screen->keysLocked = false;
            AMTSleep(50);
        }
        amtinst->screen->keysLocked = true;
        if(amtinst->screen->keys.empty())goto loop;
        unsigned char tmp = (unsigned char)amtinst->screen->keys.front();
        std::cerr << "key found: " << (int)tmp << std::endl;
        amtinst->screen->keys.pop_front();
        amtinst->screen->keysLocked = false;
        return tmp;
    }
}
