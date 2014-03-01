#include "lcd.h"
#include "image.h"

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

uint8_t m=1;
uint32_t TimerPeriod;
uint32_t TimerCCR;

//����PWM����
void TIM1_GPIO_Config(void)
{
  //PA11���
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
  
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA,&GPIO_InitStructure);
  
  GPIO_PinAFConfig(GPIOA,GPIO_PinSource11,GPIO_AF_TIM1);   
}

//TIM1��PWM���
void TIM1_Config(void)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
  TIM_OCInitTypeDef TIM_OCInitStructure;
  
  TimerPeriod =  (SystemCoreClock / 20000 ) - 1; //Ƶ��20KHz
  TimerCCR = 0;  //ռ�ձ�
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
  //ʱ����ʼ��
  TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1; //���������á�
  TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;  //����������
  TIM_TimeBaseInitStructure.TIM_Prescaler = 0;   //Timer clock = sysclock /(TIM_Prescaler+1) = 120M
  TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
  TIM_TimeBaseInitStructure.TIM_Period = TimerPeriod - 1;    //Period = (TIM counter clock / TIM output clock) - 1 = 20K
  TIM_TimeBaseInit(TIM1,&TIM_TimeBaseInitStructure);

  
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
  TIM_OCInitStructure.TIM_Pulse = TimerCCR;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
  TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCPolarity_High;
  TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
  TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;

  TIM_OC4Init(TIM1,&TIM_OCInitStructure);
  
  TIM_Cmd(TIM1,ENABLE);
  TIM_CtrlPWMOutputs(TIM1,ENABLE);
}

void LCD_SetBrightness(uint8_t percent)
{
  TimerCCR = (TimerPeriod * percent)/100;  //ռ�ձ�
  TIM1->CCR4 = TimerCCR;
}

void LCD_FSMC_Config(void)
{
  FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
  FSMC_NORSRAMTimingInitTypeDef  p;
   
  p.FSMC_AddressSetupTime = 0x04;	        //��ַ����ʱ��
    p.FSMC_AddressHoldTime = 0x04;	        //��ַ����ʱ��
    p.FSMC_DataSetupTime = 0x04;		//���ݽ���ʱ��
    p.FSMC_BusTurnAroundDuration = 0x00;
    p.FSMC_CLKDivision = 0x00;
    p.FSMC_DataLatency = 0x00;
    p.FSMC_AccessMode = FSMC_AccessMode_B;	 // һ��ʹ��ģʽB������LCD   

    FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM1;
    FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;
    FSMC_NORSRAMInitStructure.FSMC_MemoryType = FSMC_MemoryType_SRAM;
    FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;
    FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;
    FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
    FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;
    FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
    FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;
    FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
    FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable;
    FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;
    FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &p;
    FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &p; 
    
    FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure); 
    
    /* Enable FSMC Bank1_SRAM Bank */
    FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM1, ENABLE);
}


/**************************************************************************************************************
 * ��������GPIO_AF_FSMC_Config()
 * ����  ��void
 * ���  ��void
 * ����  ������LCD���ӵ�GPIO�������ӵ�FSMC,F4��F103vet6���ŷ���ʱ�е㲻ͬ��������һ����Ҫ������
 * ����  ���ڲ�����        
 *****************************************************************************************************************/
static void LCD_AF_FSMC_Config(void)
{
  /*����GPIOD��Ӧ�ĹܽŸ������ӵ�FSMC*/
  GPIO_PinAFConfig(GPIOD,GPIO_PinSource0,GPIO_AF_FSMC);	        //����GPIOD��Pin0�������ӵ�FSMC
  GPIO_PinAFConfig(GPIOD,GPIO_PinSource1,GPIO_AF_FSMC);			//����GPIOD��Pin1�������ӵ�FSMC
  GPIO_PinAFConfig(GPIOD,GPIO_PinSource4,GPIO_AF_FSMC);			//����GPIOD��Pin4�������ӵ�FSMC
  GPIO_PinAFConfig(GPIOD,GPIO_PinSource5,GPIO_AF_FSMC);			//����GPIOD��Pin5�������ӵ�FSMC
  GPIO_PinAFConfig(GPIOD,GPIO_PinSource7,GPIO_AF_FSMC);			//����GPIOD��Pin7�������ӵ�FSMC
  GPIO_PinAFConfig(GPIOD,GPIO_PinSource8,GPIO_AF_FSMC);			//����GPIOD��Pin8�������ӵ�FSMC
  GPIO_PinAFConfig(GPIOD,GPIO_PinSource9,GPIO_AF_FSMC);			//����GPIOD��Pin9�������ӵ�FSMC
  GPIO_PinAFConfig(GPIOD,GPIO_PinSource10,GPIO_AF_FSMC);		//����GPIOD��Pin10�������ӵ�FSMC
  GPIO_PinAFConfig(GPIOD,GPIO_PinSource11,GPIO_AF_FSMC);		//����GPIOD��Pin11�������ӵ�FSMC
  GPIO_PinAFConfig(GPIOD,GPIO_PinSource14,GPIO_AF_FSMC);		//����GPIOD��Pin14�������ӵ�FSMC
  GPIO_PinAFConfig(GPIOD,GPIO_PinSource15,GPIO_AF_FSMC);		//����GPIOD��Pin15�������ӵ�FSMC
   /*����GPIOE��Ӧ�ĹܽŸ������ӵ�FSMC*/
  GPIO_PinAFConfig(GPIOE,GPIO_PinSource7,GPIO_AF_FSMC);			//����GPIOE��Pin7�������ӵ�FSMC
  GPIO_PinAFConfig(GPIOE,GPIO_PinSource8,GPIO_AF_FSMC);			//����GPIOE��Pin8�������ӵ�FSMC
  GPIO_PinAFConfig(GPIOE,GPIO_PinSource9,GPIO_AF_FSMC);			//����GPIOE��Pin9�������ӵ�FSMC
  GPIO_PinAFConfig(GPIOE,GPIO_PinSource10,GPIO_AF_FSMC);		//����GPIOE��Pin10�������ӵ�FSMC
  GPIO_PinAFConfig(GPIOE,GPIO_PinSource11,GPIO_AF_FSMC);		//����GPIOE��Pin11�������ӵ�FSMC
  GPIO_PinAFConfig(GPIOE,GPIO_PinSource12,GPIO_AF_FSMC);		//����GPIOE��Pin12�������ӵ�FSMC
  GPIO_PinAFConfig(GPIOE,GPIO_PinSource13,GPIO_AF_FSMC);	    //����GPIOE��Pin13�������ӵ�FSMC
  GPIO_PinAFConfig(GPIOE,GPIO_PinSource14,GPIO_AF_FSMC);		//����GPIOE��Pin14�������ӵ�FSMC
  GPIO_PinAFConfig(GPIOE,GPIO_PinSource15,GPIO_AF_FSMC);		//����GPIOE��Pin15�������ӵ�FSMC
}

void LCD_GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

/* Enable the FSMC Clock */
    RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_FSMC, ENABLE); 
    
    /* config lcd gpio clock base on FSMC */
/* Enable GPIOs clock */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOE,ENABLE);
     
    
    /* config tft data lines base on FSMC
	 * data lines,FSMC-D0~D15: PD 14 15 0 1,PE 7 8 9 10 11 12 13 14 15,PD 8 9 10
	 */	
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_8 | GPIO_Pin_9 |
                                  GPIO_Pin_10| GPIO_Pin_14| GPIO_Pin_15;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | 
                                  GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | 
                                  GPIO_Pin_15;
    GPIO_Init(GPIOE, &GPIO_InitStructure); 
    
    /* config tft control lines base on FSMC
     * PD4-FSMC_NOE  :LCD-RD
     * PD5-FSMC_NWE  :LCD-WR
     * PD7-FSMC_NE1  :LCD-CS
     * PD11-FSMC_A16 :LCD-DC
   */

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4; 
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5; 
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7; 
    GPIO_Init(GPIOD, &GPIO_InitStructure);  
    
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 ; 
    GPIO_Init(GPIOD, &GPIO_InitStructure);  
    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    
    /* config tft rst gpio */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; 	 
    GPIO_Init(GPIOD, &GPIO_InitStructure); 
   
    LCD_AF_FSMC_Config();

}

static void LCD_Rst(void)
{			
    GPIO_ResetBits(GPIOD, GPIO_Pin_6);
    Delay(10);					   
    GPIO_SetBits(GPIOD, GPIO_Pin_6 );		 	 
    Delay(10);	
}


/*
 * ???:LCD_WR_REG
 * ??  :ILI9325 ??????
 * ??  :-index ???
 * ??  :????
 */
static void LCD_WriteCmd(u16 index)
{
    //*(__IO u16 *) (Bank1_LCD_C) = index;
		LCD_C = index;
}



/*
 * ???:LCD_WR_REG
 * ??  :?ILI9325??????
 * ??  :-index ???
 *         -val   ?????
 */
static void LCD_WriteReg(u16 index, u16 val)
{	
    //*(__IO u16 *) (Bank1_LCD_C) = index;	
    //*(__IO u16 *) (Bank1_LCD_D) = val;
		LCD_C = index;
		LCD_D = val;
}



/*
 * ???:LCD_WR_Data
 * ??  :?ILI9325 GRAM ????
 * ??  :-val ?????,16bit        
 */
static void LCD_WriteDat(unsigned int val)
{   
    //*(__IO u16 *) (Bank1_LCD_D) = val; 	
		LCD_D = val;
}

static unsigned short LCD_ReadReg(unsigned char reg_addr)
{
    unsigned short val=0;
    LCD_WriteCmd(reg_addr);
    //val = *(__IO u16 *)(Bank1_LCD_D);
		val = LCD_D;
    return (val);
}

/*
 * ???:LCD_WR_REG
 * ??  :? ILI9325 RAM ??
 * ??  :?????,16bit *         
 */
static u16 LCD_ReadDat(void)
{
    u16 a = 0;
    //a = (*(__IO u16 *) (Bank1_LCD_D)); 	//Dummy	
    //a = *(__IO u16 *) (Bank1_LCD_D);     //L
    a = LCD_D;
		a = LCD_D;
    return(a);	
}

void LCD_Init(void)
{
    LCD_GPIO_Config();
    printf("GPIO Initaled.\r\n");
    LCD_FSMC_Config();	
    printf("FSMC Configed.\r\n");
    LCD_Rst();
    printf("LCD Reseted.\r\n");
    
    //printf("Invalid LCD ID:%08X\r\n",LCD_ReadReg(0x00));
    
    LCD_WriteCmd(0xe2);//system reset
    Delay(20);   
    LCD_WriteCmd(0xae);        
    LCD_WriteCmd(0xf8);   
    LCD_WriteCmd(0x00);
    LCD_WriteCmd(0xa2);
    LCD_WriteCmd(0xa0);
    LCD_WriteCmd(0xc0);
    LCD_WriteCmd(0xa6);
    LCD_WriteCmd(0xa4);
    LCD_WriteCmd(0xe0);
    LCD_WriteCmd(0xac);
    LCD_WriteCmd(0x00);
    LCD_WriteCmd(0x21);
    LCD_WriteCmd(0x81);
    LCD_WriteCmd(0x1e);        
    LCD_WriteCmd(0x2f);   
    LCD_WriteCmd(0x40);
    LCD_WriteCmd(0xaf);
    LCD_WriteCmd(0xb0);
    LCD_WriteCmd(0x12);
    LCD_WriteCmd(0x04);
    LCD_WriteCmd(0xe0);
    LCD_WriteCmd(0xe0);
}

void LCD_SetWindow(u16 x0,u16 y0,u16 x1,u16 y1)
{
    
}

void LCD_DispBmp(u16 x0,u16 y0,u16 x1,u16 y1,u8 *pic)
{
  u16 i,j,c;

  LCD_SetWindow(x0,y0,x0+x1,y0+y1);
  for(i=0;i<=y1;i++)
  {
    for(j=0;j<=x1;j++)
    {
      c=(*pic++);
      LCD_WriteDat((c<<8)|(*pic++));
    }
  }
}

void LCD_DispBmp4bpp(u16 x0,u16 y0,u16 x1,u16 y1,u8 *pic)
{
  u16 i,j;
  u8 c;
  u8 b1,b2;
  
  LCD_SetWindow(x0,y0,x0+x1-1,y0+y1-1);
  for(i=0;i<y1;i++)
  {
    for(j=0;j<(x1/2);j++)
    {
      c=(*pic++);
      b1=(c&0xf0);
      b2=(c&0xf)<<4;
      b1=255-(b1|(b1>>4));
      b2=255-(b2|(b2>>4));
      LCD_WriteDat(RGB(b1,b1,b1));
      LCD_WriteDat(RGB(b2,b2,b2));
    }
  }
}

void LCD_Fill(u16 x0,u16 y0,u16 x1,u16 y1,u16 c)
{
  u16 i,j;

  LCD_SetWindow(x0,y0,x1,y1);
  for(i=y0;i<=y1;i++)
  {
    for(j=x0;j<=x1;j++)
    {
      LCD_WriteDat(c);
    }
  }
}

void LCD_Clear(u16 c)
{
  u16 i,j;

  LCD_SetWindow(0,0,319,239);
  for(i=0;i<=239;i++)
  {
    for(j=0;j<=319;j++)
    {
      LCD_WriteDat(c);
    }
  }
}
/************************************************
             ��ǿ�⣨���ڴ��֧�֣�
************************************************/
void LCD_Point(u16 x,u16 y,u16 color)
{
  if ((x<320)&&(y<240))
  {
    LCD_WriteCmd(0x20);               /* GRAM Vertical/Horizontal ADDR Set(AD0~AD7) */
    LCD_WriteDat(y);
    LCD_WriteCmd(0x21);               /* GRAM Vertical/Horizontal ADDR Set(AD8~AD16) */
    LCD_WriteDat(x);  
    LCD_WriteCmd(0x22);
    LCD_WriteDat(color);
  }
}

void LCD_XLine(u16 x0,u16 y0,u16 x1,u16 color)
{
  u16 i,xx0,xx1;
  
  xx0=MIN(x0,x1);
  xx1=MAX(x0,x1);
  for (i=xx0;i<=xx1;i++)
  {
    LCD_Point(i,y0,color);
  }
}

void LCD_YLine(u16 x0,u16 y0,u16 y1,u16 color)
{
  u16 i,yy0,yy1;
  
  yy0=MIN(y0,y1);
  yy1=MAX(y0,y1);
  for (i=yy0;i<=yy1;i++)
  {
    LCD_Point(x0,yy1,color);
  }
}

void LCD_Line(u16 x0,u16 y0,u16 x1,u16 y1,u16 color)
{
  int temp;
  int dx,dy;               //������㵽�յ�ĺᡢ����������ֵ
  int s1,s2,status,i;
  int Dx,Dy,sub;

  dx=x1-x0;
  if(dx>=0)                 //X�ķ��������ӵ�
    s1=1;
  else                     //X�ķ����ǽ��͵�
    s1=-1;     
  dy=y1-y0;                 //�ж�Y�ķ��������ӻ��ǽ�����
  if(dy>=0)
    s2=1;
  else
    s2=-1;

  Dx=abs(x1-x0);             //����ᡢ�ݱ�־����ֵ�ľ���ֵ
  Dy=abs(y1-y0);
  if(Dy>Dx)                 //               
  {                     //��45�Ƚ�Ϊ�ֽ��ߣ�����Y����status=1,����X����status=0 
    temp=Dx;
    Dx=Dy;
    Dy=temp;
    status=1;
  } 
  else
    status=0;

/********�жϴ�ֱ�ߺ�ˮƽ��********/
  if(dx==0)                   //������û����������һ��ˮƽ��
    LCD_YLine(x0,y0,y1,color);
  if(dy==0)                   //������û����������һ����ֱ��
    LCD_XLine(x0,y0,x1,color);


/*********Bresenham�㷨������������ֱ��********/ 
  sub=2*Dy-Dx;                 //��1���ж��¸����λ��
  for(i=0;i<Dx;i++)
  { 
    LCD_Point(x0,y0,color);           //���� 
    if(sub>=0)                               
    { 
      if(status==1)               //�ڿ���Y������xֵ��1
        x0+=s1; 
      else                     //�ڿ���X������yֵ��1               
        y0+=s2; 
      sub-=2*Dx;                 //�ж����¸����λ�� 
    } 
    if(status==1)
      y0+=s2; 
    else       
      x0+=s1; 
    sub+=2*Dy;   
  } 
}

void LCD_Circle(u16 x0,u16 y0,u16 r,u16 color)
{
  int a,b;
  int di;
  
  a=0;
  b=r;
  di=3-2*r;             //�ж��¸���λ�õı�־
  while(a<=b)
  {
    LCD_Point(x0-b,y0-a,color);             //3           
    LCD_Point(x0+b,y0-a,color);             //0           
    LCD_Point(x0-a,y0+b,color);             //1       
    LCD_Point(x0-b,y0-a,color);             //7           
    LCD_Point(x0-a,y0-b,color);             //2             
    LCD_Point(x0+b,y0+a,color);             //4               
    LCD_Point(x0+a,y0-b,color);             //5
    LCD_Point(x0+a,y0+b,color);             //6 
    LCD_Point(x0-b,y0+a,color);             
    a++;
    /***ʹ��Bresenham�㷨��Բ**/     
    if(di<0)
      di +=4*a+6;
    else
    {
      di +=10+4*(a-b);   
      b--;
    } 
    LCD_Point(x0+a,y0+b,color);
  }
}

void LCD_Rect(u16 x1,u16 y1,u16 x2,u16 y2,u16 color)
{
  LCD_XLine(x1,y1,x2,color);
  LCD_XLine(x1,y2,x2,color);
  LCD_YLine(x1,y1,y2,color);
  LCD_YLine(x2,y1,y2,color);
}

/************************************************
       ���ֿ⣨POWERED��
************************************************/
//��ָ��λ����ʾASCII 8*16����
void LCD_Display_ASCII_8X16_Chr(u16 left,u16 top,u8 chr,u16 color)
{
  u16 x,y;
  u16 ptr;
  
  if (left<320)
  {
  ptr=(chr-0x20)*16;//��������1������
  for (y=0;y<15;y++)
  {
    for (x=0;x<8;x++)
    {
      if (((Font_Ascii_8X16E[ptr]>>x)&0x01)==0x01)
        LCD_Point(left+x,top+y,color); 
    }
    ptr++;
  }
  }
}

//��ָ��λ����ʾASCII 8*16����
void LCD_Display_ASCIIF(u16 left,u16 top,u8 chr,u16 colorF,u16 colorB)
{
  u16 x,y;
  u16 ptr;
  
  if (left<320)
  {
  ptr=(chr-0x20)*16;//��������1������
  for (y=0;y<15;y++)
  {
    for (x=0;x<8;x++)
    {
      if (((Font_Ascii_8X16E[ptr]>>x)&0x01)==0x01)
        LCD_Point(left+x,top+y,colorF);
      else
        LCD_Point(left+x,top+y,colorB);
    }
    ptr++;
  }
  }
}
/*
void LCD_Display_ASCII_24X48_Chr(u8 left,u8 top,u8 chr)
{
  u8 x,y;
  u16 ptr;
  
  if (left<40)
  {
  ptr=(chr-0x20)*144;
  for (y=0;y<48;y++)
    for (x=0;x<3;x++)
      LCD_Framebuffer[(top+y)*40+left+x]=Font_Ascii_24X48E[ptr++];
  }
}
*/

void LCD_Display_Chn_Chr(u8 left,u8 top,u8 *chr,u16 color)
{
  u16 x,y,z,ptr;
  u8 buffer[32];
  u8 h8,l8;
  u32 pos;
  
  h8=*chr;
  l8=*(chr+1);
  
  pos = ((h8-0xb0)*94+l8-0xa1)*2*16;
  SPI_FLASH_BufferRead(buffer,pos,32);
  ptr=0;
  for (y=0;y<16;y++)
  {
    for (z=0;z<2;z++)
    {
      for (x=0;x<8;x++)
      {
        if (((buffer[ptr]<<x)&0x80)==0x80)
          LCD_Point(left+x+z*8,top+y,color); 
      }
      ptr++;
    }
  }
}

void LCD_Display_ChnF(u8 left,u8 top,u8 *chr,u16 colorF,u16 colorB)
{
  u16 x,y,z,ptr;
  u8 buffer[32];
  u8 h8,l8;
  u32 pos;
  
  h8=*chr;
  l8=*(chr+1);
  
  pos = ((h8-0xb0)*94+l8-0xa1)*2*16;
  SPI_FLASH_BufferRead(buffer,pos,32);
  ptr=0;
  for (y=0;y<16;y++)
  {
    for (z=0;z<2;z++)
    {
      for (x=0;x<8;x++)
      {
        if (((buffer[ptr]<<x)&0x80)==0x80)
          LCD_Point(left+x+z*8,top+y,colorF); 
        else
          LCD_Point(left+x+z*8,top+y,colorB);
      }
      ptr++;
    }
  }
}

void LCD_String(u16 left,u16 top,u8 *s,u16 color)
{
  u16 x;
  
  x=0;
  while(*s)
  {
    if (*s<128)
    {
      LCD_Display_ASCII_8X16_Chr(left+x,top,*s++,color);
      x+=8;
    }
    else
    {
      LCD_Display_Chn_Chr(left+x,top,s,color);
      s+=2;
      x+=16;
    }
  }
}

void LCD_StringF(u16 left,u16 top,u8 *s,u16 colorF,u16 colorG)
{
  u16 x;
  
  x=0;
  while(*s)
  {
    if (*s<128)
    {
      LCD_Display_ASCIIF(left+x,top,*s++,colorF,colorG);
      x+=8;
    }
    else
    {
      LCD_Display_ChnF(left+x,top,s,colorF,colorG);
      s+=2;
      x+=16;
    }
  }
}


//m^n����
u32 mypow(u8 m,u8 n)
{
	uint32_t result=1;	 
	while(n--)result*=m;    
	return result;
}
/**************************************************************************************************************
 * ��������LCD_DrawNum()
 * ����  ��u16 x, u16 y, s32 num, u8 len   ��ʾ��λ�ã����ּ�����
 * ���  ��void
 * ����  ��LCD��ʾһ������
 * ����  ���ⲿ����        
 *****************************************************************************************************************/   
void LCD_DispNum(u16 x, u16 y, s32 num, u8 len,u16 color)
{           
  u8 t,temp;
  u8 enshow=0;
  t=0;
  if(num<0)
  {
    LCD_Display_ASCII_8X16_Chr(x+8*t,y,'-',color);
    num=-num;
    t++;
  }               
  for(;t<len;t++)
  {
    temp=(num/mypow(10,len-t-1))%10;
    if(enshow==0&&t<(len-1))
    {
      if(temp==0)
      {
        LCD_Display_ASCII_8X16_Chr(x+8*t,y,' ',color);
        continue;
      }else enshow=1;         
    }
     LCD_Display_ASCII_8X16_Chr(x+8*t,y,temp+'0',color); 
  }
} 

