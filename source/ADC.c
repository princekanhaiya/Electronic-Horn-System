/***********************************************
Author: Prince Kanhaiya
Revision: 1.0.0
Last Updated: 28-05-2022
Files Info: ADC functions File
************************************************/
#include "ADC.h"
#include "GPIO.h"

void ADC_init(void){
     ADMUX=(1<<REFS0);                         // For Aref=AVcc;
     ADCSRA=(1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0); //Prescalar div factor =128
}

int readADC(uint8_t pin){
    if (pin >= PC3) 
       pin -= PC3; // allow for channel or pin numbers

    ADMUX = (REFS0<< 6) | (pin & 0x07);
    SET_BIT(ADCSRA, ADSC);
    while (bit_is_set(ADCSRA, ADSC));  //wait till ADC conversion complete
    return (ADCH << 8) | ADCL;  
}
