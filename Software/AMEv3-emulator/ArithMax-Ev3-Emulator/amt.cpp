
#include "qamthread.h"

#include "stdio.h"

extern "C"{
    unsigned char *ScreenBuffer;
    int *AMTlastkey;
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
}
