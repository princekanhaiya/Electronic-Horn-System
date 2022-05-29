/***********************************************
Author: Prince Kanhaiya
Revision: 1.0.0
Last Updated: 28-05-2022
Files Info: LCD functions File
************************************************/
#include "GPIO.h"
#include "LCD.h"

extern uint8_t dutyCycle;

//LCD initialization
void lcd_init(void){
    _delay_ms(100);
    lcd_RS_port &= ~(1<<lcd_RS_bit);
    lcd_E_port &= ~(1<<lcd_E_bit);
    lcd_write(lcd_FunctionReset);
    _delay_ms(10);
    lcd_write(lcd_FunctionReset);
    _delay_us(200);
    lcd_write(lcd_FunctionReset);
    _delay_us(200);
    lcd_write(lcd_FunctionSet4bit);
    _delay_us(80);
    lcd_cmd(lcd_FunctionSet4bit);
    _delay_us(80);
    lcd_cmd(lcd_DisplayOff);
    _delay_us(80);
    lcd_cmd(lcd_Clear);
    _delay_ms(4);
    lcd_cmd(lcd_EntryMode);
    _delay_us(80);
    lcd_cmd(lcd_DisplayOn);
    _delay_us(80);
}

//LCD string write
void lcd_str(char Str[]){
    volatile int i = 0;
    while (Str[i] != 0){
        lcd_char(Str[i]);
        i++;
        _delay_us(80);
    }
}

//LCD char write
void lcd_char(uint8_t data){
    lcd_RS_port |= (1<<lcd_RS_bit);
    lcd_E_port &= ~(1<<lcd_E_bit);
    lcd_write(data);
    lcd_write(data << 4);
}

//LCD cmd write
void lcd_cmd(uint8_t theInstruction){
    lcd_RS_port &= ~(1<<lcd_RS_bit);
    lcd_E_port &= ~(1<<lcd_E_bit);
    lcd_write(theInstruction);
    lcd_write(theInstruction << 4);
}

void lcd_write(uint8_t theByte){
    lcd_D7_port &= ~(1<<lcd_D7_bit);
    if (theByte & 1<<7) lcd_D7_port |= (1<<lcd_D7_bit);
    lcd_D6_port &= ~(1<<lcd_D6_bit);
    if (theByte & 1<<6) lcd_D6_port |= (1<<lcd_D6_bit);
    lcd_D5_port &= ~(1<<lcd_D5_bit);
    if (theByte & 1<<5) lcd_D5_port |= (1<<lcd_D5_bit);
    lcd_D4_port &= ~(1<<lcd_D4_bit);
    if (theByte & 1<<4) lcd_D4_port |= (1<<lcd_D4_bit);
    lcd_E_port |= (1<<lcd_E_bit);
    _delay_us(1);
    lcd_E_port &= ~(1<<lcd_E_bit);
    _delay_us(1);
}

void lcd_int(uint8_t value){
	char string[10];
	itoa(value, string, 10);
	lcd_str(string);
}

void lcd_xy(uint8_t x, uint8_t y){
	if(y==0)
        lcd_cmd( lcd_SetCursor | (lcd_LineOne + x));
    if(y==1)
        lcd_cmd( lcd_SetCursor | (lcd_LineTwo + x));
    if(y==2)
        lcd_cmd( lcd_SetCursor | (lcd_LineThree + x));
    if(y==3)
        lcd_cmd( lcd_SetCursor | (lcd_lineFour + x));
}

void lcd_clear(void){
    lcd_cmd(lcd_Clear);
}

void lcd_animation(void){
    lcd_clear();
    lcd_xy(0,0);
    lcd_str(" HORN SYSTEM FOR");
    lcd_xy(0,1);
    lcd_str("     VEHICLE");
    lcd_xy(0,3);
    lcd_str(" CALIBRATING");
    lcd_str(".");
    _delay_ms(100);
    lcd_str(".");
    _delay_ms(150);
    lcd_str(".");
    _delay_ms(200);
    lcd_str(".");
    _delay_ms(250);
    lcd_str(".");
    _delay_ms(300);
    lcd_xy(0,3);
    lcd_str(" CALIBRATING    ");
    lcd_xy(0,3);
    lcd_str(" CALIBRATING");
    lcd_str(".");
    _delay_ms(350);
    lcd_str(".");
    _delay_ms(400);
    lcd_str(".");
    _delay_ms(450);
    lcd_str(".");
    _delay_ms(500);
    lcd_str(".");
    _delay_ms(550);

    lcd_xy(0,3);
    lcd_str(" CALIBRATING    ");
    lcd_xy(0,3);
    lcd_str(" CALIBRATING");
    lcd_str(".");
    _delay_ms(500);
    lcd_str(".");
    _delay_ms(400);
    lcd_str(".");
    _delay_ms(300);
    lcd_str(".");
    _delay_ms(200);
    lcd_str(".");
    _delay_ms(100);

    lcd_clear();
    lcd_xy(0,0);
    lcd_str("   PRESS KEYS   ");
    _delay_ms(1000);
}
