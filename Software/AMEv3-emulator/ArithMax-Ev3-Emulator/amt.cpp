
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
        //while(amtinst->screen->keysLocked == NULL)AMTSleep(50);
        loop:while(true)
        {
            //while(amtinst->screen->keysLocked);
            //amtinst->screen->keysLocked = true;
            amtinst->screen->keysLocked.lock();
            if(!amtinst->screen->keys.empty())
            {
                //amtinst->screen->keysLocked.unlock();
                break;
            }
            //amtinst->screen->keysLocked = false;
            amtinst->screen->keysLocked.unlock();
            AMTSleep(50);
        }
        //amtinst->screen->keysLocked = true;
        //amtinst->screen->keysLocked.lock();
        if(amtinst->screen->keys.empty())
        {
            amtinst->screen->keysLocked.unlock();
            goto loop;
        }
        unsigned char tmp = amtinst->screen->keys.front();
        std::cerr << "key found: " << (int)tmp << std::endl;
        amtinst->screen->keys.pop();
        amtinst->screen->keysLocked.unlock();
        return tmp;
    }
}
