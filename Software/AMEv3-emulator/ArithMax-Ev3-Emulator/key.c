#include "key.h"
#include "stn.h"

uint8_t __IO LastKey = 255;
uint8_t __IO NowKey = 255;

void KBD_Config(void)
{

}

void KBD_EXTIConfig(void)
{

}

void KBD_TIMConfig(void)
{

}

void DelayUs(u32 us)
{
    //u32 time=100*us/7;
    //while(--time);
    AMTUSleep(us);
}

uint8_t KBD_Scan(void)
{
  /*uint8_t i;
  uint32_t line,rowb,rowa;
  uint8_t key;
  
  GPIOA->ODR &= 0xffffff00;//PA0-PA7��0
  line = 0x00000002;//��PA1��ʼɨ��
  key=255;
  for(i=0;i<7;i++)
  {
    GPIOA->ODR |= 0xff;
    GPIOA->ODR &= (~line);//��Ӧ����0
    //Delay(1);//�ȴ�IO״̬�仯
    //asm("nop");
		//_nop_();
    rowb=0xff;
    rowa=0x00;
    while(rowb!=rowa)
    {
      rowb = (GPIOE->IDR)&0x7f;//������Ӧ����
      //Delay(1);//10msȥ��
      DelayUs(1);
      rowa = (GPIOE->IDR)&0x7f;//�ٴζ���
      if (rowb==rowa) //״̬��ͬ
      switch(rowb)
      {
        case 0x7e:key=0*7+i;break;
        case 0x7d:key=1*7+i;break;
        case 0x7b:key=2*7+i;break;
        case 0x77:key=3*7+i;break;
        case 0x6f:key=4*7+i;break;
        case 0x5f:key=5*7+i;break;
        case 0x3f:key=6*7+i;break;
      }
    }
    line = line << 1;//����һλ
  }
  return key;*/
}

void WaitForKey(void)
{
  uint8_t key=255;
  while (key==255)
  {
    key=LastKey;
  }
}

unsigned char GetKey(void)
{
    return AcquireKey();
    /*int tmp;
    while(AMTlastkey == 0xFF || AMTlastkey == 130);
    tmp = AMTlastkey;
    fprintf(stdout,"Key:%d\n",AMTlastkey);
    AMTlastkey = 0xFF;
    return (unsigned char) (tmp);*/

}
