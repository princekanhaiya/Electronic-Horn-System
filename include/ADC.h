/***********************************************
Author: Prince Kanhaiya
Revision: 1.0.0
Last Updated: 28-05-2022
Files Info: ADC header File
************************************************/
#ifndef ADC_H_INCLUDED
#define ADC_H_INCLUDED

#include "GPIO.h"

void ADC_init(void);
int readADC(uint8_t ch);

#endif // ADC_H_INCLUDED
