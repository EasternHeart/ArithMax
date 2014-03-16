#include "oled.h"
#include "stdlib.h"
#include "font.h"     
//SSD1306 OLED ����IC��������
//������ʽ:8080����/4�ߴ���
//�汾:V1.1
//����ԭ��@ALIENTEK
//2010-6-3

//OLED���Դ�
//��Ÿ�ʽ����.
//[0]0 1 2 3 ... 127  
//[1]0 1 2 3 ... 127  
//[2]0 1 2 3 ... 127  
//[3]0 1 2 3 ... 127  
//[4]0 1 2 3 ... 127  
//[5]0 1 2 3 ... 127  
//[6]0 1 2 3 ... 127  
//[7]0 1 2 3 ... 127        
u8 OLED_GRAM[128][8];   

//�����Դ浽LCD     
void OLED_Refresh_Gram(void)
{
  u8 i,n;        
  for(i=0;i<8;i++)  
  {  
    OLED_WR_Byte(0xb0+i,OLED_CMD);    //����ҳ��ַ��0~7��
    OLED_WR_Byte(0x02,OLED_CMD);      //������ʾλ�á��е͵�ַ,ƫ����2��
    OLED_WR_Byte(0x10,OLED_CMD);      //������ʾλ�á��иߵ�ַ   
    for(n=0;n<128;n++)OLED_WR_Byte(OLED_GRAM[n][i],OLED_DATA); 
  }   
}
//��SSD1306д��һ���ֽڡ�
//dat:Ҫд�������/����
//cmd:����/�����־ 0,��ʾ����;1,��ʾ����;
void OLED_WR_Byte(u8 dat,u8 cmd)
{  
  u8 i;    
        if (cmd)
          OLED_DC_High();
        else
          OLED_DC_Low(); 
  OLED_CS_Low(); 
  asm("nop");
  for(i=0;i<8;i++)
  {        
    OLED_SCLK_Low();
    if(dat&0x80)OLED_SDIN_High();
    else OLED_SDIN_Low();
    asm("nop");
    OLED_SCLK_High();
    dat<<=1;   
  }         
  OLED_CS_High();
  OLED_DC_High();       
} 
      
//����OLED��ʾ    
void OLED_Display_On(void)
{
  OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC����
  OLED_WR_Byte(0X14,OLED_CMD);  //DCDC ON
  OLED_WR_Byte(0XAF,OLED_CMD);  //DISPLAY ON
}
//�ر�OLED��ʾ     
void OLED_Display_Off(void)
{
  OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC����
  OLED_WR_Byte(0X10,OLED_CMD);  //DCDC OFF
  OLED_WR_Byte(0XAE,OLED_CMD);  //DISPLAY OFF
}              
//��������,������,������Ļ�Ǻ�ɫ��!��û����һ��!!!    
void OLED_Clear(void)  
{  
  u8 i,n;  
  for(i=0;i<8;i++)for(n=0;n<128;n++)OLED_GRAM[n][i]=0X00;  
  OLED_Refresh_Gram();//������ʾ
}
//���� 
//x:0~127
//y:0~63
//t:1 ��� 0,���           
void OLED_DrawPoint(u8 x,u8 y,u8 t)
{
  u8 pos,bx,temp=0;
  if(x>127||y>63)return;//������Χ��.
  pos=7-y/8;
  bx=y%8;
  temp=1<<(7-bx);
  if(t)OLED_GRAM[x][pos]|=temp;
  else OLED_GRAM[x][pos]&=~temp;      
}
//x1,y1,x2,y2 �������ĶԽ�����
//ȷ��x1<=x2;y1<=y2 0<=x1<=127 0<=y1<=63      
//dot:0,���;1,���    
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot)  
{  
  u8 x,y;  
  for(x=x1;x<=x2;x++)
  {
    for(y=y1;y<=y2;y++)OLED_DrawPoint(x,y,dot);
  }                              
  OLED_Refresh_Gram();//������ʾ
}
//��ָ��λ����ʾһ���ַ�,���������ַ�
//x:0~127
//y:0~63
//mode:0,������ʾ;1,������ʾ         
//size:ѡ������ 16/12 
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size,u8 mode)
{                
  u8 temp,t,t1;
  u8 y0=y;
  chr=chr-' ';//�õ�ƫ�ƺ��ֵ           
    for(t=0;t<size;t++)
    {   
    if(size==12)temp=asc2_1206[chr][t];  //����1206����
    else temp=asc2_1608[chr][t];     //����1608����                             
        for(t1=0;t1<8;t1++)
    {
      if(temp&0x80)OLED_DrawPoint(x,y,mode);
      else OLED_DrawPoint(x,y,!mode);
      temp<<=1;
      y++;
      if((y-y0)==size)
      {
        y=y0;
        x++;
        break;
      }
    }     
    }          
}
//m^n����
u32 mypow(u8 m,u8 n)
{
  u32 result=1;   
  while(n--)result*=m;    
  return result;
}          
//��ʾ2������
//x,y :�������   
//len :���ֵ�λ��
//size:�����С
//mode:ģʽ  0,���ģʽ;1,����ģʽ
//num:��ֵ(0~4294967295);         
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size)
{           
  u8 t,temp;
  u8 enshow=0;               
  for(t=0;t<len;t++)
  {
    temp=(num/mypow(10,len-t-1))%10;
    if(enshow==0&&t<(len-1))
    {
      if(temp==0)
      {
        OLED_ShowChar(x+(size/2)*t,y,' ',size,1);
        continue;
      }else enshow=1; 
        
    }
     OLED_ShowChar(x+(size/2)*t,y,temp+'0',size,1); 
  }
} 
//��ʾ�ַ���
//x,y:�������  
//*p:�ַ�����ʼ��ַ
//��16����
void OLED_ShowString(u8 x,u8 y,const u8 *p)
{
#define MAX_CHAR_POSX 122
#define MAX_CHAR_POSY 58          
    while(*p!='\0')
    {       
        if(x>MAX_CHAR_POSX){x=0;y+=16;}
        if(y>MAX_CHAR_POSY){y=x=0;OLED_Clear();}
        OLED_ShowChar(x,y,*p,16,1);   
        x+=8;
        p++;
    }  
}     
//��ʼ��SSD1303              
void OLED_Init(void)
{                              
  GPIO_InitTypeDef GPIO_InitStructure;
  
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_9 | GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);  
  
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
                  
  OLED_RST_Low();
  Delay(100);
  OLED_RST_High(); 
            
OLED_WR_Byte(0xae,OLED_CMD);//--turn off oled panel
OLED_WR_Byte(0x00,OLED_CMD);//---set low column address
OLED_WR_Byte(0x10,OLED_CMD);//---set high column address
OLED_WR_Byte(0x40,OLED_CMD);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
OLED_WR_Byte(0x81,OLED_CMD);//--set contrast control register
OLED_WR_Byte(0xcf,OLED_CMD); // Set SEG Output Current Brightness
OLED_WR_Byte(0xa1,OLED_CMD);//--Set SEG/Column Mapping     0xa0���ҷ��� 0xa1����
OLED_WR_Byte(0xc8,OLED_CMD);//Set COM/Row Scan Direction   0xc0���·��� 0xc8����
OLED_WR_Byte(0xa6,OLED_CMD);//--set normal display
OLED_WR_Byte(0xa8,OLED_CMD);//--set multiplex ratio(1 to 64)
OLED_WR_Byte(0x3f,OLED_CMD);//--1/64 duty
OLED_WR_Byte(0xd3,OLED_CMD);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
OLED_WR_Byte(0x00,OLED_CMD);//-not offset
OLED_WR_Byte(0xd5,OLED_CMD);//--set display clock divide ratio/oscillator frequency
OLED_WR_Byte(0x80,OLED_CMD);//--set divide ratio, Set Clock as 100 Frames/Sec
OLED_WR_Byte(0xd9,OLED_CMD);//--set pre-charge period
OLED_WR_Byte(0xf1,OLED_CMD);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
OLED_WR_Byte(0xda,OLED_CMD);//--set com pins hardware configuration
OLED_WR_Byte(0x12,OLED_CMD);
OLED_WR_Byte(0xdb,OLED_CMD);//--set vcomh
OLED_WR_Byte(0x40,OLED_CMD);//Set VCOM Deselect Level
OLED_WR_Byte(0x20,OLED_CMD);//-Set Page Addressing Mode (0x00/0x01/0x02)
OLED_WR_Byte(0x02,OLED_CMD);//
OLED_WR_Byte(0x8d,OLED_CMD);//--set Charge Pump enable/disable
OLED_WR_Byte(0x14,OLED_CMD);//--set(0x10) disable
OLED_WR_Byte(0xa4,OLED_CMD);// Disable Entire Display On (0xa4/0xa5)
OLED_WR_Byte(0xa6,OLED_CMD);// Disable Inverse Display On (0xa6/a7) 
OLED_WR_Byte(0xaf,OLED_CMD);//--turn on oled panel
  OLED_Clear();
}  





























