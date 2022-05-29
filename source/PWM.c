/***********************************************
Author: Prince Kanhaiya
Revision: 1.0.0
Last Updated: 28-05-2022
Files Info: Fast PWM mode function definitions
************************************************/
#include "PWM.h"

//fast PWM mode 
void pwm(uint8_t dutyCycle){
    TCCR0A |=(1<<COM0A1)|(1<<WGM01)|(1<<WGM00);
    OCR0A=dutyCycle;
    TCCR0B |=(1<<CS00);
}
