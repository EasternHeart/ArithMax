#include "stn.h"
#include "image.h"
#include "am.h"

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

uint8_t mode=1;//1=覆盖

uint8_t LCD_FB[96*32/8];
uint8_t CursorX,CursorY,CursorEn=0;
uint8_t m=1;
uint8_t LCD_FB_Touched = 0;

uint8_t *Curr_Font;

void LCD_Update_FB(void)
{
    int i,j;
    //for(i = 12;i<96*32/8;i++)
        // UpBuffer[i-12] = LCD_FB[i];
    //for(i = 1;i<32;i++)
        //for(j = 0;j<12;j++)
            //ScreenBuffer[j*31 + i-1] = LCD_FB[(i)*96+j];
}

void LCD_Init(void)
{
/*    LCD_GPIO_Config();
    printf("GPIO Initaled.\r\n");
    LCD_FSMC_Config();	
    printf("FSMC Configed.\r\n");
    LCD_Rst();
    printf("LCD Reseted.\r\n");
    
    //printf("Invalid LCD ID:%08X\r\n",LCD_ReadReg(0x00));
    
    LCD_WriteCmd(0xe2);//system reset
    Delay(5);   
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
    Delay(5);
    LCD_WriteCmd(0xaf);*/
    LCD_Clear(0);
    UpdateScreenBuffer();
}

void LCD_DispBmp1bpp(u8 x0,u8 y0,u8 w,u8 h,u8 *pic)
{
  u8 i,j,z,c;

  for(i=y0;i<=y0+h;i++)
  {
    for(j=x0;j<=x0+w;j+=8)
    {
      c=(*pic++);
      for (z=0;z<8;z++)
        if ((c<<z)&0x80)
          LCD_Point(j+z,i,1);
        else
          LCD_Point(j+z,i,0);
    }
  }
}

void LCD_Fill(u8 x0,u8 y0,u8 x1,u8 y1,u8 c)
{
  u16 i,j;

  for(i=y0;i<=y1;i++)
  {
    for(j=x0;j<=x1;j++)
    {
      LCD_Point(j,i,c);
    }
  }
}

void LCD_Clear(u8 c)
{
  u16 i;

  for(i=0;i<32*12;i++)
  {
      ScreenBuffer[i]=c;
  }
}

void LCD_Update()
{
  /*unsigned char i,j;
  for (i=0;i<4;i++)
  {
    LCD_WriteCmd(0xee);
    LCD_WriteCmd(0xb0|(3-i));
    LCD_WriteCmd(0x12);
    LCD_WriteCmd(0x04);
    LCD_WriteCmd(0xe0); 
    for (j=0;j<96;j++)
      LCD_WriteDat(LCD_FB[i*96+j]);
  }*/
  LCD_Update_FB();
  UpdateScreenBuffer();
}

void LCD_PowerSave()
{
  /*LCD_WriteCmd(0xae);
  LCD_WriteCmd(0x28);
  LCD_WriteCmd(0xa5);*/
}

void LCD_StatusClear()
{
  /*unsigned char i;
  LCD_WriteCmd(0xee);
  LCD_WriteCmd(0xb8);
  LCD_WriteCmd(0x12);
  LCD_WriteCmd(0x04);
  LCD_WriteCmd(0xe0); 
  for (i=0;i<96;i++)
    LCD_WriteDat(0x00);*/
}

void LCD_StatusSet(unsigned char id,unsigned char status)
{
  /*u8 rid = id+36;
  LCD_WriteCmd(0xee);
  LCD_WriteCmd(0xb8);
  LCD_WriteCmd(0x10|(rid>>4));
  LCD_WriteCmd(0x00|(rid&0x0f));
  LCD_WriteCmd(0xe0);
  LCD_WriteDat(status);*/
}

void LCD_SetBrightness(u8 t)
{

}

/************************************************
             增强库（基于打点支持）
************************************************/
void LCD_Point(u8 x,u8 y,u8 color)
{
  u16 x_bit,x_byte;               //定义行地址的字节位，及在字节中的哪1位
  if ((x<96)&&(y<32))
  {
    x_byte=x/8;
    x_bit=x%8;
  
    //if(color)
      //LCD_FB[(y_byte)*96+x]|=(0x80>>y_bit);
    //else
      //LCD_FB[(y_byte)*96+x]&=~(0x80>>y_bit);
    if(color) ScreenBuffer[(x_byte)*32 + y] |= (1 << x_bit);
    else ScreenBuffer[(x_byte)*32 + y] &= ~(1 << x_bit);
    //fprintf(stderr,"%d %d %d \n",(int)x,(int)y,(int)color);
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
  int dx,dy;               //定义起点到终点的横、纵坐标增加值
  int s1,s2,status,i;
  int Dx,Dy,sub;

  dx=x1-x0;
  if(dx>=0)                 //X的方向是增加的
    s1=1;
  else                     //X的方向是降低的
    s1=-1;     
  dy=y1-y0;                 //判断Y的方向是增加还是降到的
  if(dy>=0)
    s2=1;
  else
    s2=-1;

  Dx=abs(x1-x0);             //计算横、纵标志增加值的绝对值
  Dy=abs(y1-y0);
  if(Dy>Dx)                 //               
  {                     //以45度角为分界线，靠进Y轴是status=1,靠近X轴是status=0 
    temp=Dx;
    Dx=Dy;
    Dy=temp;
    status=1;
  } 
  else
    status=0;

/********判断垂直线和水平线********/
  if(dx==0)                   //横向上没有增量，画一条水平线
    LCD_YLine(x0,y0,y1,color);
  if(dy==0)                   //纵向上没有增量，画一条垂直线
    LCD_XLine(x0,y0,x1,color);


/*********Bresenham算法画任意两点间的直线********/ 
  sub=2*Dy-Dx;                 //第1次判断下个点的位置
  for(i=0;i<Dx;i++)
  { 
    LCD_Point(x0,y0,color);           //画点 
    if(sub>=0)                               
    { 
      if(status==1)               //在靠近Y轴区，x值加1
        x0+=s1; 
      else                     //在靠近X轴区，y值加1               
        y0+=s2; 
      sub-=2*Dx;                 //判断下下个点的位置 
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
  di=3-2*r;             //判断下个点位置的标志
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
    /***使用Bresenham算法画圆**/     
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
       文字库（POWERED）
************************************************/

void LCD_SelectFont(u8* font)
{
  Curr_Font = font;
}
//在指定位置显示ASCII 8*16文字
void LCD_Display_ASCII_8X16_Chr(u16 left,u16 top,u8 chr,u16 color)
{
  u16 x,y;
  u16 ptr;
  
  ptr=(chr-0x20)*16;//整体下移1个像素
  for (y=0;y<16;y++)
  {
    for (x=0;x<8;x++)
    {
      if (((Font_Ascii_8X16E[ptr]>>x)&0x01)==0x01)
        LCD_Point(left+x,top+y,color); 
    }
    ptr++;
  }
  LCD_FB_Touched = 0;
  /*if ((CursorEn)&&(CursorState))
  {
    rx=CursorX+36;
    LCD_WriteCmd(0xee);
    LCD_WriteCmd(0xb0|(3-CursorY));
    LCD_WriteCmd(0x10|(rx>>4));
    LCD_WriteCmd(0x00|(rx&0x0f));
    LCD_WriteCmd(0xe0);
    LCD_WriteDat(0xFF);
    LCD_WriteDat(0xFF);
  }*/
}

//在指定位置显示ASCII 8*16文字
void LCD_Display_ASCII_5X7_Chr(u16 left,u16 top,u8 chr,u16 color)
{
  u16 x,y;
  u16 ptr;


  
  ptr=(chr-0x20)*8;//整体下移1个像素
  if (mode==1){
      LCD_Fill(left,top,6,8,0);
  for (y=0;y<8;y++)
  {
    for (x=0;x<5;x++)
    {
      if (((Curr_Font[ptr]<<x)&0x80)==0x80)
        LCD_Point(left+x,top+y,color);
      else
        LCD_Point(left+x,top+y,1-color);
    }
    ptr++;
  } 
  }else{
  for (y=0;y<8;y++)
  {
    for (x=0;x<5;x++)
    {
      if (((Curr_Font[ptr]<<x)&0x80)==0x80)
        LCD_Point(left+x,top+y,color); 
    }
    ptr++;
  }
  }
}

void LCD_Display_Chn_Chr(u8 left,u8 top,u8 *chr,u16 color)
{
  u16 x,y,z,ptr;
  u8 buffer[32];
  u8 h8,l8;
  u32 pos;
  
  h8=*chr;
  l8=*(chr+1);
  
  pos = ((h8-0xb0)*94+l8-0xa1)*2*16;
  //SPI_FLASH_BufferRead(buffer,pos,32);
  //FIXME:Font
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

void LCD_String_5X7(u16 left,u16 top,u8 *s,u16 color)
{
  u16 x;
  
  x=0;
  while(*s)
  {
    if (*s<128)
    {
      //LCD_Fill(left+x,top,6,7,0);
      LCD_Display_ASCII_5X7_Chr(left+x,top,*s++,color);
      x+=6;
    }
    else
    {
      //暂时不支持小字体中文
      s+=2;
      x+=6;
    }
  }
}

//m^n函数
u32 mypow(u8 m,u8 n)
{
	uint32_t result=1;	 
	while(n--)result*=m;    
	return result;
}
/**************************************************************************************************************
 * 函数名：LCD_DrawNum()
 * 输入  ：u16 x, u16 y, s32 num, u8 len   显示的位置，数字及长度
 * 输出  ：void
 * 描述  ：LCD显示一个数字
 * 调用  ：外部调用        
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

void LCD_DispNum_5X7(u16 x, u16 y, s32 num, u8 len,u16 color)
{           
  u8 t,temp;
  u8 enshow=0;
  t=0;
  if(num<0)
  {
    LCD_Display_ASCII_5X7_Chr(x+6*t,y,'-',color);
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
        LCD_Display_ASCII_5X7_Chr(x+6*t,y,' ',color);
        continue;
      }else enshow=1;         
    }
     LCD_Display_ASCII_5X7_Chr(x+6*t,y,temp+'0',color); 
  }
} 
