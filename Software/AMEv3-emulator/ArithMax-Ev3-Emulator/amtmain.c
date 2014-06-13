#include "main.h"
#include "usart.h"
#include "stn.h"
#include "sdcard.h"
#include "spiflash.h"
#include "key.h"
#include "powerman.h"
//#include "dac.h"

uint8_t brightness=30;
uint32_t sf_size,voltage;

u8 ShiftState;

const char* menu_string[]=
{
  "计算器","电子书","游戏","设置"
};

uint8_t ShiftState;//最低位：Shift状态 第二位：Alpha状态

/*__IO uint32_t FlashID = 0;
__IO uint32_t TimingDelay;*/

void Delay(uint32_t nTime)
{
  //TimingDelay = nTime;

  //while(TimingDelay != 0);
    AMTSleep(nTime);
}

/**
  * @brief  Decrements the TimingDelay variable.
  * @param  None
  * @retval None
  */
/*void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0x00)
  { 
    TimingDelay--;
  }
}*/

/*unsigned int SPI_FLASH_GetSize()
{
  unsigned int size;
  FlashID = SPI_FLASH_ReadID();
  size = mypow(2,(FlashID&0xff));
  return size;
}*/

void About_main()
{
 LCD_Clear(0);
 LCD_String_5X7(0,0 ,(unsigned char*)"ArithMax E301 r1",1);
 LCD_String_5X7(0,8 ,(unsigned char*)"Software:1.0.DEV",1);
 LCD_String_5X7(0,16,(unsigned char*)"",1);
 LCD_String_5X7(0,24,(unsigned char*)"Designed by Zweb",1);
 LCD_Update();
 GetKey();
}

void Info_main()
{
  char str[17]="Designed by Zweb";
  sprintf(str,"Flash:%dKB",(sf_size>>10));
  LCD_Clear(0);
  LCD_String_5X7(0,0 ,(unsigned char*)"Emulator",1);
  LCD_String_5X7(0,8 ,str,1);
  /*sprintf(str,"SD:%dMB",SDCardInfo.CardCapacity>>20);
  LCD_String_5X7(0,16,str,1);
  voltage=PM_GetVolt();
  sprintf(str,"Volt:%dmV",voltage);
  LCD_String_5X7(0,24,str,1);*/
  LCD_Update();
  GetKey();
}
  
void Contrast_main()
{
      u8 cont=1;
      u8 key;
      
      LCD_Clear(0x00);
  LCD_String_5X7(0,0 ,"CONTRAST        ",1);
  LCD_String_5X7(0,16,"LIGHT       DARK",1);
  LCD_String_5X7(0,24," [<]        [>] ",1);
  LCD_Update();
  while (cont)
  {
    key=GetKey(); 
    switch (key)
    {
    case KEY_CTRL_LEFT:if (brightness>0) brightness-=1; LCD_SetBrightness(brightness);break;
    case KEY_CTRL_RIGHT:if (brightness<64) brightness+=1; LCD_SetBrightness(brightness);break;
    case KEY_CTRL_AC:cont=0;break;
    } 
  }
}

void Diag_main()
{
  u8 key;
  u16 i;
  LCD_Clear(0);
  LCD_String_5X7(0,1 ,"DIAGNOSTIC",1);
  LCD_Update();
  key=GetKey();
  if (key!=KEY_CHAR_9) return;
  LCD_Clear(0xff);
  LCD_Update();
  /*LCD_WriteCmd(0xee);
  LCD_WriteCmd(0xb8);
  LCD_WriteCmd(0x12);
  LCD_WriteCmd(0x04);
  LCD_WriteCmd(0xe0); 
  for (i=0;i<96;i++)
    LCD_WriteDat(0x01);*/
  WaitForCertainKey(KEY_CTRL_EXE);
  LCD_Clear(0x00);
  /*LCD_Update();
  LCD_WriteCmd(0xee);
  LCD_WriteCmd(0xb8);
  LCD_WriteCmd(0x12);
  LCD_WriteCmd(0x04);
  LCD_WriteCmd(0xe0); 
  for (i=0;i<96;i++)
    LCD_WriteDat(0x00);*/
  WaitForCertainKey(KEY_CTRL_EXE);
  LCD_Line(0,0,95,0,1);
  LCD_Line(0,0,0,30,1);
  LCD_Line(0,30,95,30,1);
  LCD_Line(95,0,95,30,1);
  LCD_Update();
  WaitForCertainKey(KEY_CTRL_EXE);
  for (i=0;i<384;i+=2)
  {
      LCD_FB[i]=0xAA;
      LCD_FB[i+1]=0x55;
  }
  LCD_StatusSet(LCD_STB_Shift,1);
  LCD_StatusSet(LCD_STB_Alpha,1);
  LCD_StatusSet(LCD_STB_M,1);
  LCD_StatusSet(LCD_STB_RCL,1);
  LCD_StatusSet(LCD_STB_STAT,1);
  LCD_StatusSet(LCD_STB_MAT,1);
  LCD_StatusSet(LCD_STB_G,1);
  LCD_StatusSet(LCD_STB_FIX,1);
  LCD_StatusSet(LCD_STB_Math,1);
  LCD_StatusSet(LCD_STB_Disp,1);
  WaitForCertainKey(KEY_CTRL_EXE);
  for (i=0;i<384;i+=2)
  {
      LCD_FB[i]=0x55;
      LCD_FB[i+1]=0xAA;
  }
  LCD_Update();
/*  LCD_WriteCmd(0xee);
  LCD_WriteCmd(0xb8);
  LCD_WriteCmd(0x12);
  LCD_WriteCmd(0x04);
  LCD_WriteCmd(0xe0);
  for (i=0;i<96;i++)
    LCD_WriteDat(0x00);*/
  LCD_StatusSet(LCD_STB_STO,1);
  LCD_StatusSet(LCD_STB_CMPLX,1);
  LCD_StatusSet(LCD_STB_VCT,1);
  LCD_StatusSet(LCD_STB_D,1);
  LCD_StatusSet(LCD_STB_R,1);
  LCD_StatusSet(LCD_STB_SCI,1);
  LCD_StatusSet(LCD_STB_Down,1);
  LCD_StatusSet(LCD_STB_Up,1);
  WaitForCertainKey(KEY_CTRL_EXE);
  LCD_Clear(0);
  /*LCD_WriteCmd(0xee);
  LCD_WriteCmd(0xb8);
  LCD_WriteCmd(0x12);
  LCD_WriteCmd(0x04);
  LCD_WriteCmd(0xe0); 
  for (i=0;i<96;i++)
    LCD_WriteDat(0x00);*/
  LCD_String_5X7(0,1 ,"ArithMax E300",1);
  LCD_String_5X7(0,8 ,"EVT For DEV Only",1);
  LCD_String_5X7(0,24,"Press AC",1);
  LCD_Update();
  WaitForCertainKey(KEY_CTRL_AC);
  Contrast_main();
  LCD_Clear(0);
  LCD_Update();
  while (key!=KEY_CTRL_EXE)
  {
    key=GetKey();
    LCD_DispNum_5X7(0,0,key,3,1);
    LCD_Update();
  }
}


void Setup_main()
{
  u8 key;
  u8 cont =1;
  
  LCD_Clear(0x00);
  LCD_String_5X7(0,0 ,"1:Deg   2:Rad   ",1);
  LCD_String_5X7(0,8 ,"3:Gra   4:Cmplx ",1);
  LCD_String_5X7(0,16,"5:Cont. 6:Diag. ",1);
  LCD_String_5X7(0,24,"7:Info  8:About ",1);
  LCD_Update();
    while (cont==1)
  {
     key=GetKey();
    cont=0;
     switch (key)
     {
    case KEY_CHAR_6:Diag_main();break;
     case KEY_CHAR_5:Contrast_main();break;
     case KEY_CHAR_7:Info_main();break;
     case KEY_CHAR_8:About_main();break;
    case KEY_CTRL_AC:cont=0;break;
    default:LCD_StatusSet(LCD_STB_Disp,1);Delay(10);LCD_StatusSet(LCD_STB_Disp,0);cont=1;break;
     }
  }

}

void Mode_main()
{
  LCD_Clear(0);
  LCD_String_5X7(0,0 ,"1:COMP  2:CAS   ",1);
  LCD_String_5X7(0,8 ,"3:STAT  4:VECTOR",1);
  LCD_String_5X7(0,16,"5:TABLE 6:GRAPH ",1);
  LCD_String_5X7(0,24,"7:PRGM  8:USRAPP",1);
 LCD_Update();
 GetKey();
}

int amt_main(void)
{
  SD_Error state;
  //RCC_ClocksTypeDef RCC_Clocks;
  uint16_t i;
  uint8_t key;
  
  //USART1_Config();
        
  printf("\r\n\r\nSTM32F2 Development Platform\r\nBuild by Zweb.\r\n");
  printf("Ready to turn on the Systick.\r\n");
        
  /* SysTick end of count event each 10ms */
 /* RCC_GetClocksFreq(&RCC_Clocks);
  SysTick_Config(RCC_Clocks.HCLK_Frequency / 100);*/
  
  printf("Systick opened successfully.\r\n");
  //printf("Main Clock Frequency: %d MHz\r\n",(RCC_Clocks.HCLK_Frequency/1000000));

  //NVIC_Config();
  
  //DAC1_Config();
  //printf("DAC Inited.\r\n");
  LCD_Init();
  LCD_StatusClear();
  //LCD_SelectFont((u8 *)Font_Ascii_5X7E);
  LCD_SelectFont(Font_Ascii_5X7E_Menu);
  printf("LCD Inited.\r\n");
  //LCD_Clear(0x00);
  /*SPI_FLASH_Init();
  Delay(5);
  sf_size = SPI_FLASH_GetSize();*/
  
 /*打印芯片的ID及设备ID*/
  //printf("SPIFLASH芯片ID为：0x%X , 容量为%d KB \r\n", FlashID, (sf_size>>10));
  
  //KBD_Config();
  //TODO: KBD will be soon added
  
  //PM_Config();
  
  LCD_Clear(0x00);
  LCD_Update();
  //for (i=0;i<=100;i++)
  //{
  //  LCD_SetBrightness(i);
  //  Delay(1);
  //}
  //KBD_TIMConfig();
  //KBD_EXTIConfig();
  //PM_LDO_On();
  //state=SD_Init();
  
  //PM_SetCPUFreq(16);
  
  while(1)
  {
    //Mode_main();
      //LCD_Clear(0);
      //LCD_String_5X7(0,0,"1:COMP  2:CAS   ",1);
    eigenmath_main();
    //  for(;;);
  }
  
}
