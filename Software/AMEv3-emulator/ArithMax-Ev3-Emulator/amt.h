#ifndef AMT_H
#define AMT_H

extern unsigned char *ScreenBuffer;
extern int AMTlastkey;
extern void UpdateScreenBuffer();
extern void AMTSleep();
extern void AMTUSleep();
extern unsigned char AcquireKey();

#endif // AMT_H
