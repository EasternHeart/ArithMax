#include "keyboard.h"
#include "ui_keyboard.h"

#include <QKeyEvent>

#include <iostream>

#include <cstdlib>

Keyboard::Keyboard(QArithMaxScreen *s,QWidget *parent) :
    QWidget(parent),screen(s),
    ui(new Ui::Keyboard)
{
    ui->setupUi(this);
    grabKeyboard();
}

Keyboard::~Keyboard()
{
    delete ui;
}


#define KEY_CTRL_LEFT           4
#define KEY_CTRL_RIGHT          1
#define KEY_CTRL_UP             2
#define KEY_CTRL_DOWN           3
#define KEY_CTRL_DEL            36
#define KEY_CTRL_AC             35
#define KEY_CTRL_MODE           0
#define KEY_CTRL_SETUP          0+128
#define KEY_CTRL_EXE            48
#define KEY_CTRL_FD             29
#define KEY_CHAR_PLUS           40
#define KEY_CHAR_MINUS          47
#define KEY_CHAR_MULT           43
#define KEY_CHAR_DIV            42
#define KEY_CHAR_POW            16
#define KEY_CHAR_SQUARE         17
#define KEY_CHAR_ROOT           18
#define KEY_CHAR_CUBEROOT       18+128
#define KEY_CHAR_POWROOT        16+128
#define KEY_CHAR_LN             14
#define KEY_CHAR_EXPN           14+128
#define KEY_CHAR_SIN            23
#define KEY_CHAR_ASIN           23+128
#define KEY_CHAR_COS            22
#define KEY_CHAR_ACOS           22+128
#define KEY_CHAR_TAN            21
#define KEY_CHAR_ATAN           21+128
#define KEY_CHAR_FRAC           19
#define KEY_CHAR_FACT           8+128
#define KEY_CHAR_IMGNRY         32+64
#define KEY_CHAR_PI             34+128
#define KEY_CHAR_EXP            34
#define KEY_CHAR_PMINUS         26
#define KEY_CHAR_ANS            41
#define KEY_CHAR_ENG            32

#define KEY_CHAR_LB             31
#define KEY_CHAR_RB             30
#define KEY_CHAR_CO             27
#define KEY_CHAR_e              34+64

#define KEY_CHAR_0              20
#define KEY_CHAR_1              13
#define KEY_CHAR_2              12
#define KEY_CHAR_3              11
#define KEY_CHAR_4              46
#define KEY_CHAR_5              45
#define KEY_CHAR_6              44
#define KEY_CHAR_7              39
#define KEY_CHAR_8              38
#define KEY_CHAR_9              37
#define KEY_CHAR_A              26+64
#define KEY_CHAR_B              25+64
#define KEY_CHAR_C              24+64
#define KEY_CHAR_D              23+64
#define KEY_CHAR_E              22+64
#define KEY_CHAR_F              21+64
#define KEY_CHAR_G              33+64
#define KEY_CHAR_H              32+64
#define KEY_CHAR_I              31+64
#define KEY_CHAR_J              30+64
#define KEY_CHAR_K              29+64
#define KEY_CHAR_L              28+64
#define KEY_CHAR_M              39+64
#define KEY_CHAR_N              38+64
#define KEY_CHAR_O              37+64
#define KEY_CHAR_P              36+64
#define KEY_CHAR_Q              35+64
#define KEY_CHAR_R              46+64
#define KEY_CHAR_S              45+64
#define KEY_CHAR_T              44+64
#define KEY_CHAR_U              43+64
#define KEY_CHAR_V              42+64
#define KEY_CHAR_W              13+64
#define KEY_CHAR_X              12+64
#define KEY_CHAR_Y              11+64
#define KEY_CHAR_Z              40+64
#define KEY_CHAR_EQUAL          10+64
#define KEY_CHAR_COMMA          30+128

void Keyboard::keyPressEvent(QKeyEvent *event)
{
    //while(keysLocked);
    //keysLocked = true;
    screen->keysLocked.lock();
    switch(event->key())
    {
#define RESOLVE(a,b) case Qt::Key_##a: \
    screen->keys.push(KEY_##b); /*std::cerr << "\nAddKey: " << KEY_##b << std::endl;*/ \
    break
#define RESOLVE_ASCII(a,b) case a: \
    screen->keys.push(KEY_##b); /*std::cerr << "\nAddKey: " << KEY_##b << std::endl;*/ \
    break
        RESOLVE(0,CHAR_0);
        RESOLVE(1,CHAR_1);
        RESOLVE(2,CHAR_2);
        RESOLVE(3,CHAR_3);
        RESOLVE(4,CHAR_4);
        RESOLVE(5,CHAR_5);
        RESOLVE(6,CHAR_6);
        RESOLVE(7,CHAR_7);
        RESOLVE(8,CHAR_8);
        RESOLVE(9,CHAR_9);
        RESOLVE(Return,CTRL_EXE);
        RESOLVE(Enter,CTRL_EXE);
        RESOLVE(Left,CTRL_LEFT);
        RESOLVE(Right,CTRL_RIGHT);
        RESOLVE(Down,CTRL_DOWN);
        RESOLVE(Up,CTRL_UP);
        RESOLVE(Backspace,CTRL_DEL);
        RESOLVE(Escape,CTRL_AC);
        RESOLVE(Plus,CHAR_PLUS);
        RESOLVE(Minus,CHAR_MINUS);
        RESOLVE(F1,CTRL_MODE);
        RESOLVE(F2,CTRL_SETUP);
        RESOLVE(F3,CTRL_FD);
        RESOLVE_ASCII('^',CHAR_POW);
        RESOLVE_ASCII('*',CHAR_MULT);
        RESOLVE_ASCII('/',CHAR_DIV);
        RESOLVE_ASCII('@',CHAR_SQUARE);
        RESOLVE_ASCII('|',CHAR_ROOT);
        RESOLVE_ASCII('(',CHAR_LB);
        RESOLVE_ASCII(')',CHAR_RB);
        RESOLVE_ASCII('X',CHAR_X);
        RESOLVE_ASCII('Y',CHAR_Y);
        RESOLVE_ASCII('A',CHAR_A);
        RESOLVE_ASCII('B',CHAR_B);
        RESOLVE_ASCII('C',CHAR_C);
        RESOLVE_ASCII('D',CHAR_D);
        RESOLVE_ASCII('E',CHAR_E);
        RESOLVE_ASCII('F',CHAR_F);
        RESOLVE_ASCII('M',CHAR_M);
        RESOLVE_ASCII('G',CHAR_G);
        RESOLVE_ASCII('H',CHAR_H);
        RESOLVE_ASCII('I',CHAR_I);
        RESOLVE_ASCII('J',CHAR_J);
        RESOLVE_ASCII('K',CHAR_K);
        RESOLVE_ASCII('L',CHAR_L);
        RESOLVE_ASCII('N',CHAR_N);
        RESOLVE_ASCII('O',CHAR_O);
        RESOLVE_ASCII('P',CHAR_P);
        RESOLVE_ASCII('Q',CHAR_Q);
        RESOLVE_ASCII('R',CHAR_R);
        RESOLVE_ASCII('S',CHAR_S);
        RESOLVE_ASCII('T',CHAR_T);
        RESOLVE_ASCII('U',CHAR_U);
        RESOLVE_ASCII('V',CHAR_V);
        RESOLVE_ASCII('W',CHAR_W);
        RESOLVE_ASCII('Z',CHAR_Z);
        RESOLVE_ASCII('=',CHAR_EQUAL);
        RESOLVE_ASCII(',',CHAR_COMMA);
#undef RESOLVE
    }
    //keysLocked = false;
    screen->keysLocked.unlock();
    //std::cerr << "\nKeyPress: " << event->key() << std::endl;
}

void Keyboard::keyReleaseEvent(QKeyEvent *)
{
    /*aKeyPressed--;
    if(!aKeyPressed) AMTlastkey = 0xFF;*/
}

#define KEY(a) do {screen->keysLocked.lock(); \
screen->keys.push(KEY_##a); \
    screen->keysLocked.unlock(); if(!ui->pushButton_32->isChecked()) {ui->pushButton->setChecked(false); \
ui->pushButton_2->setChecked(false);}}while(0) \

void Keyboard::on_pushButton_3_clicked()
{
    KEY(CTRL_UP);
}

void Keyboard::on_pushButton_4_clicked()
{
    KEY(CTRL_DOWN);
}

void Keyboard::on_pushButton_6_clicked()
{
    KEY(CTRL_RIGHT);
}

void Keyboard::on_pushButton_5_clicked()
{
    KEY(CTRL_LEFT);
}

#define KEY3(a,b,c) if(ui->pushButton->isChecked()) KEY(b); \
    else if(ui->pushButton_2->isChecked()) KEY(c); \
    else KEY(a);

#define KEY2(a,b) if(ui->pushButton->isChecked()) KEY(b); \
    else KEY(a);

void Keyboard::on_pushButton_7_clicked()
{
    KEY3(CHAR_EQUAL,CHAR_EQUAL,CHAR_A);
}

void Keyboard::on_pushButton_8_clicked()
{
    KEY3(CHAR_FACT,CHAR_FACT,CHAR_B);
}

void Keyboard::on_pushButton_12_clicked()
{
    KEY3(CHAR_LN,CHAR_EXPN,CHAR_C);
}

void Keyboard::on_pushButton_11_clicked()
{
    KEY3(CHAR_POW,CHAR_POWROOT,CHAR_G);
}

void Keyboard::on_pushButton_10_clicked()
{
    KEY3(CHAR_SIN,CHAR_ASIN,CHAR_D);
}

void Keyboard::on_pushButton_9_clicked()
{
    KEY3(CHAR_COS,CHAR_ACOS,CHAR_E);
}

void Keyboard::on_pushButton_13_clicked()
{
    KEY3(CHAR_TAN,CHAR_ATAN,CHAR_F);
}

void Keyboard::on_pushButton_14_clicked()
{
    KEY3(CHAR_SQUARE,CHAR_ROOT,CHAR_H);
}

void Keyboard::on_pushButton_15_clicked()
{
    KEY3(CHAR_1,CHAR_1,CHAR_O);
}

void Keyboard::on_pushButton_16_clicked()
{
    KEY3(CHAR_2,CHAR_2,CHAR_P);
}

void Keyboard::on_pushButton_17_clicked()
{
    KEY3(CHAR_3,CHAR_3,CHAR_Q);
}

void Keyboard::on_pushButton_18_clicked()
{
    KEY3(CHAR_4,CHAR_4,CHAR_R);
}

void Keyboard::on_pushButton_19_clicked()
{
    KEY3(CHAR_5,CHAR_5,CHAR_S);
}

void Keyboard::on_pushButton_20_clicked()
{
    KEY3(CHAR_6,CHAR_6,CHAR_T);
}

void Keyboard::on_pushButton_22_clicked()
{
    KEY3(CHAR_7,CHAR_7,CHAR_U);
}

void Keyboard::on_pushButton_21_clicked()
{
    KEY3(CHAR_8,CHAR_8,CHAR_V);
}

void Keyboard::on_pushButton_24_clicked()
{
    KEY3(CHAR_9,CHAR_9,CHAR_W);
}

void Keyboard::on_pushButton_23_clicked()
{
    KEY3(CHAR_0,CHAR_0,CHAR_X);
}

void Keyboard::on_pushButton_25_clicked()
{
    KEY(CTRL_EXE);
}

void Keyboard::on_pushButton_26_clicked()
{
    KEY3(CHAR_PLUS,CHAR_PLUS,CHAR_Y);
}

void Keyboard::on_pushButton_28_clicked()
{
    KEY3(CHAR_MINUS,CHAR_MINUS,CHAR_Z);
}

void Keyboard::on_pushButton_27_clicked()
{
    KEY(CHAR_MULT);
}

void Keyboard::on_pushButton_29_clicked()
{
    KEY(CHAR_DIV);
}

void Keyboard::on_pushButton_30_clicked()
{
    KEY(CTRL_DEL);
}

void Keyboard::on_pushButton_31_clicked()
{
    if(ui->pushButton->isChecked())
    {
        std::exit(0);
    }
    KEY(CTRL_AC);
}

void Keyboard::on_pushButton_33_clicked()
{
    KEY3(CHAR_PI,CHAR_e,CHAR_IMGNRY);
}

void Keyboard::on_pushButton_35_clicked()
{
    KEY(CTRL_MODE);
}

void Keyboard::on_pushButton_36_clicked()
{
    KEY(CTRL_SETUP);
}

void Keyboard::on_pushButton_37_clicked()
{
    KEY(CTRL_FD);
}

void Keyboard::on_pushButton_34_clicked()
{
    KEY3(CHAR_ANS,CHAR_ANS,CHAR_I);
}

void Keyboard::on_pushButton_38_clicked()
{
    KEY3(CHAR_ENG,CHAR_ENG,CHAR_J);
}

void Keyboard::on_pushButton_39_clicked()
{
    KEY3(CHAR_LB,CHAR_LB,CHAR_K);
}

void Keyboard::on_pushButton_40_clicked()
{
    KEY3(CHAR_RB,CHAR_RB,CHAR_L);
}

void Keyboard::on_pushButton_42_clicked()
{
    KEY3(CHAR_CO,CHAR_CO,CHAR_M);
}

void Keyboard::on_pushButton_41_clicked()
{
    KEY3(CHAR_COMMA,CHAR_COMMA,CHAR_N);
}
