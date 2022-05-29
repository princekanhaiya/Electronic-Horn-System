/***********************************************
Author: Prince Kanhaiya
Revision: 1.0.0
Last Updated: 28-05-2022
Files Info: LCD header File
************************************************/
#ifndef LCD_H_INCLUDED
#define LCD_H_INCLUDED

#include "GPIO.h"

#define LCD_D7_ddr      DDRB
#define lcd_D7_port     PORTB
#define lcd_D7_bit      PORTB1

#define lcd_D6_ddr      DDRB
#define lcd_D6_port     PORTB
#define lcd_D6_bit      PORTB2

#define lcd_D5_ddr      DDRB
#define lcd_D5_port     PORTB
#define lcd_D5_bit      PORTB3

#define lcd_D4_ddr      DDRB
#define lcd_D4_port     PORTB
#define lcd_D4_bit      PORTB4

#define lcd_E_ddr       DDRC
#define lcd_E_port      PORTC
#define lcd_E_bit       PORTC0

#define lcd_RS_ddr      DDRC
#define lcd_RS_port     PORTC
#define lcd_RS_bit      PORTC2


// LCD module information
#define lcd_LineOne     0x00                    // start of line 1
#define lcd_LineTwo     0x40                    // start of line 2
#define   lcd_LineThree   0x14                  // start of line 3 (20x4)
#define   lcd_lineFour    0x54                  // start of line 4 (20x4)

// LCD instructions
#define lcd_Clear           0x01          // replace all characters with ASCII Space
#define lcd_Home            0x02          // return cursor to first position on first line
#define lcd_EntryMode       0x06          // shift cursor from left to right on read/write
#define lcd_DisplayOff      0x08          // turn display off
#define lcd_DisplayOn       0x0C          // display on, cursor off, don't blink character
#define lcd_FunctionReset   0x30          // reset the LCD
#define lcd_FunctionSet4bit 0x28          // 4-bit data, 2-line display, 5 x 7 font
#define lcd_SetCursor       0x80          // set cursor position

// Function Prototypes
void lcd_write(uint8_t);
void lcd_cmd(uint8_t);
void lcd_char(uint8_t);
void lcd_str(char *);
void lcd_init(void);
void lcd_clear(void);
void lcd_int(uint8_t);
void lcd_xy(uint8_t, uint8_t);
void lcd_animation(void);
#endif // LCD_H_INCLUDED
