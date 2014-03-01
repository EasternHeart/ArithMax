#define GN 200
#include "main.h"
#include "lcd.h"
#include "key.h"
#define LEFT 62
#define RIGHT 73
#define DOWN 63
#define UP 72
#define ESC 24

int i;
uint8_t key;
int score=0;/*�÷�*/
int gamespeed=50;/*��Ϸ�ٶ��Լ�����*/

struct Food
{
   int x;/*ʳ��ĺ�����*/
   int y;/*ʳ���������*/
   int yes;/*�ж��Ƿ�Ҫ����ʳ��ı���*/
}food;/*ʳ��Ľṹ��*/

struct Snake
{
   int x[GN];
   int y[GN];
   int node;/*�ߵĽ���*/
   int direction;/*���ƶ�����*/
   int life;/* �ߵ�����,0����,1����*/
}snake;

void Init(void);/*ͼ������*/
void Close(void);/*ͼ�ν���*/
void DrawK(void);/*��ʼ����*/
void GameOver(void);/*������Ϸ*/
void GamePlay(void);/*����Ϸ�������*/
void PrScore(void);/*����ɼ�*/
/*������*/
void snake_main(void)
{
   Init();/*ͼ������*/
   DrawK();/*��ʼ����*/
   GamePlay();/*����Ϸ�������*/
   Close();/*ͼ�ν���*/
}
/*ͼ������*/
void Init(void)
{
   LCD_Fill(0,0,319,239,0x0000);
}
/*��ʼ���棬���Ͻ�����Ϊ��50��40�������½�����Ϊ��610��460����Χǽ*/
void DrawK(void)
{
/*setbkcolor(LIGHTGREEN);*/
  LCD_Fill(13,24,305,29,LCD_COLOR_WHITE); /*�ϱ�*/
  LCD_Fill(13,222,305,227,LCD_COLOR_WHITE);/*�±�*/
  LCD_Fill(13,24,18,227,LCD_COLOR_WHITE); /*���*/
  LCD_Fill(300,24,305,227,LCD_COLOR_WHITE);/*�ұ�*/
}
/*����Ϸ�������*/
void GamePlay(void)
{
   srand();/*�����������*/
   food.yes=0;/*1��ʾ��Ҫ������ʳ��,0��ʾ�Ѿ�����ʳ��*/
   snake.life=0;/*����*/
   snake.direction=1;/*��������*/
   snake.x[0]=50;snake.y[0]=50;/*��ͷ*/
   snake.x[1]=60;snake.y[1]=50;
   snake.node=2;/*����*/
   food.x=150;
   food.y=150;
   PrScore();/*����÷�*/
   key=255;
     while(1)/*��û�а����������,���Լ��ƶ�����*/
     {
        if(food.yes==1)/*��Ҫ������ʳ��*/
        {
          food.x=rand()%200+40;
          food.y=rand()%175+30;
          while(food.x%10!=0)/*ʳ��������ֺ������ʳ���ܹ���������,�����ſ������߳Ե�*/
            food.x++;
          while(food.y%10!=0)
            food.y++;
          food.yes=0;/*��������ʳ����*/
        }
        if(food.yes==0)/*��������ʳ���˾�Ҫ��ʾ*/
        {
              //setcolor(GREEN);
              LCD_Fill(food.x,food.y-9,food.x+9,food.y,LCD_COLOR_GREEN);
        }
        for(i=snake.node-1;i>0;i--)/*�ߵ�ÿ��������ǰ�ƶ�,Ҳ����̰���ߵĹؼ��㷨*/
        {
          snake.x[i]=snake.x[i-1];
          snake.y[i]=snake.y[i-1];
        }
       /*1,2,3,4��ʾ��,��,��,���ĸ�����,ͨ������ж����ƶ���ͷ*/
        switch(snake.direction)
        {
          case 1:snake.x[0]+=10;break;
          case 2:snake.x[0]-=10;break;
          case 3:snake.y[0]-=10;break;
          case 4:snake.y[0]+=10;break;
        }
        for(i=3;i<snake.node;i++)/*���ߵĵ��Ľڿ�ʼ�ж��Ƿ�ײ���Լ��ˣ���Ϊ��ͷΪ���ڣ������ڲ����ܹչ���*/
        {
          if(snake.x[i]==snake.x[0]&&snake.y[i]==snake.y[0])
          {
               GameOver();/*��ʾʧ��*/
               snake.life=1;
               break;
          }
        }
        if(snake.x[0]<20||snake.x[0]>290||snake.y[0]<40||
            snake.y[0]>227)/*���Ƿ�ײ��ǽ��*/
        {
          GameOver();/*������Ϸ����*/
          snake.life=1; /*����*/
          break;
        }
        if(snake.life==1)/*���������ж��Ժ�,���������������ѭ�������¿�ʼ*/
           break;
        if(snake.x[0]==food.x&&snake.y[0]==food.y)/*�Ե�ʳ���Ժ�*/
        {
           //setcolor(0);/*�ѻ����ϵ�ʳ�ﶫ��ȥ��*/
          LCD_Fill(food.x,food.y-9,food.x+9,food.y,0);
          snake.x[snake.node]=-5;snake.y[snake.node]=-5;
          /*�µ�һ���ȷ��ڿ�������λ��,�´�ѭ����ȡǰһ�ڵ�λ��*/
          snake.node++;/*�ߵ����峤һ��*/
          food.yes=1;/*��������Ҫ�����µ�ʳ��*/
          score+=10;
          PrScore();/*����µ÷�*/
        }
        //setcolor(4);/*������*/
        for(i=0;i<snake.node;i++)
          LCD_Fill(snake.x[i],snake.y[i]-9,snake.x[i]+9,
               snake.y[i],LCD_COLOR_RED);
        Delay(gamespeed);
        //setcolor(0);/*�ú�ɫȥ���ߵĵ����һ��*/
        LCD_Fill(snake.x[snake.node-1],snake.y[snake.node-1]-9,
          snake.x[snake.node-1]+9,snake.y[snake.node-1],0);
        key=LastKey;/*���հ���*/
        if (key!=255)
          LCD_DispNum(0,0,key,3,0xffff);
        if(key==ESC)/*��ESC���˳�*/
          break;
        else
        if((key==UP)&&(snake.direction!=4))
        /*�ж��Ƿ����෴�ķ����ƶ�*/
          snake.direction=3;
        else
        if((key==RIGHT)&&(snake.direction!=2))
          snake.direction=1;
        else
        if((key==LEFT)&&(snake.direction!=1))
          snake.direction=2;
        else
        if((key==DOWN)&&(snake.direction!=3))
          snake.direction=4;
        LastKey=255;
        key=255;
    }  /*endwhile����kbhit��*/
}
/*��Ϸ����*/
void GameOver(void)
{
    PrScore();
   //setcolor(RED);
   //settextstyle(0,0,4);
   LCD_String(100,100,"��Ϸ����,�����������",LCD_COLOR_RED);
   WaitForKey();
}
/*����ɼ�*/
void PrScore(void)
{   
   char str[10];
   LCD_Fill(25,3,110,21,LCD_COLOR_YELLOW);
   sprintf(str,"score:%d",score);
   LCD_String(27,4,str,LCD_COLOR_BLACK);
   
}
/*ͼ�ν���*/
void Close(void)
{   
}