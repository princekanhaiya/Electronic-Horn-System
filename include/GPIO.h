/***********************************************
Author: Prince Kanhaiya
Revision: 1.0.0
Last Updated: 28-05-2022
Files Info: General Purpose I/O Header file and related functions prototypes
************************************************/
#ifndef GPIO_H_INCLUDED
#define GPIO_H_INCLUDED

#include <avr/io.h>           //AVR microcontroller IO header
#include <avr/interrupt.h>    //AVR microcontroller Interrupt header
#include <stdint.h>           //C standard library which allow to write more portable code
#include <util/delay.h>       //Library used to implement simple delay loops that perform a busy-waiting


//Common macro definition
#define ONE 1
#define TRUE 1
#define FALSE 0
#define ON 1
#define OFF 0

//Factory calbrated initial values
#define HORN_PWM_THRESHOLD 70        //mesurement unit is in %
#define HORN_COIL_TEMP_THRESHOLD 500 //mesurement unit is in °C
#define HORN_COIL_TEMP_MAX 1000
#define MAX_DUTY_CYCLE 255
#define MIN_DUTY_CYCLE 0
#define FIVE_PER_DUTY_CYCLE 13
#define TEN_PER_DUTY_CYCLE 26

//Macro definitions
#define SET_BIT(PORT,BIT) PORT |= (1<<BIT)
#define CLR_BIT(PORT,BIT) PORT &= ~(1<<BIT)
#define TOGGLE_BIT(PORT,BIT) PORT ^= (1<<BIT)
#define PIN_READ(PORT,PIN) (PORT&(1<<PIN))


//FUNTION PROTOTYPES
void gpio_init(void);
void intrrupt_init(void);
void hornFuntions(void);

#endif // GPIO_H_INCLUDED
