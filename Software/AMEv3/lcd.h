#ifndef __LCD_H__
#define __LCD_H__

#include "main.h"

#define Bank1_LCD_D      ((u32) 0x60020000) /* RS = 1 */
#define Bank1_LCD_C      ((u32) 0x60000000) /* RS = 0 */

#define LCD_D   *(vu16*)((u32)0x60020000)  //disp Data ADDR
#define LCD_C   *(vu16*)((u32)0x60000000)	 //disp Reg  ADDR

#define RGB(r,g,b) (((r>>3) & 0x1f) << 11)|(((g>>2) & 0x3f) << 5)|((b>>3) & 0x1f)


#define LCD_COLOR_WHITE          0xFFFF
#define LCD_COLOR_BLACK          0x0000
#define LCD_COLOR_GREY           0xF7DE
#define LCD_COLOR_BLUE           0x001F
#define LCD_COLOR_BLUE2          0x051F
#define LCD_COLOR_RED            0xF800
#define LCD_COLOR_MAGENTA        0xF81F
#define LCD_COLOR_GREEN          0x07E0
#define LCD_COLOR_CYAN           0x7FFF
#define LCD_COLOR_YELLOW         0xFFE0
                                              
u32 mypow(u8 m,u8 n);

void TIM1_GPIO_Config();
void TIM1_Config();

void LCD_Init(void);
void LCD_DispBmp(u16 x0,u16 y0,u16 x1,u16 y1,u8 *pic);

void LCD_Fill(u16 x0,u16 y0,u16 x1,u16 y1,u16 c);

void LCD_Display_ASCII_8X16_Chr(u16 left,u16 top,u8 chr,u16 color);
void LCD_Display_ASCII_8X16(u16 left,u16 top,u8 *s,u16 color);
//void LCD_Display_ASCII_24X48_Chr(u8 left,u8 top,u8 chr);
//void LCD_Display_Chn_Chr(u8 left,u8 top,u8 *chr);
void LCD_String(u16 left,u16 top,u8 *s,u16 color);
void LCD_StringF(u16 left,u16 top,u8 *s,u16 colorF,u16 colorG);
void LCD_DispNum(u16 x, u16 y, s32 num, u8 len,u16 color);
//���
//������left ˮƽλ�ã�top ��ֱλ�ã�color ��ɫ��0��1��
void LCD_Point(u16 x,u16 y,u16 color);
//��һ��ˮƽ��
//������x0 ��ʼ�����꣬y0 ��ʼ�����꣬x1 ���������꣬color ��ɫ��0��1��
void LCD_XLine(u16 x0,u16 y0,u16 x1,u16 color);
//��һ����ֱ��
//������x0 ��ʼ�����꣬y0 ��ʼ�����꣬y1 ���������꣬color ��ɫ��0��1��
void LCD_YLine(u16 x0,u16 y0,u16 y1,u16 color);
//���ò���ɭ��ķ(Bresenham)�㷨����
//������x0 ��ʼ�����꣬y0 ��ʼ�����꣬x1 ���������꣬y1 ���������꣬color ��ɫ��0��1��
void LCD_Line(u16 x0,u16 y0,u16 x1,u16 y1,u16 color);
//��Բ
//������x0 ˮƽλ�ã�y0 ��ֱλ�ã�r�뾶��color ��ɫ��0��1��
void LCD_Circle(u16 x0,u16 y0,u16 r,u16 color);

void LCD_Clear(u16 c);

#endif