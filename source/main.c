/*
*  Files Info: Main Driver File
*  Revision: 1.0.0
*  Modified: 28 May 2022
*  Auther: Prince Kanhaiya
*
*
*  The circuit:
*  //Inputs
*  - Potentiometer used as temperature sensor connected to analog pin PC3.
*  - Ignition Switch->PC5, Horn Switch->PD0, Horn Tone Adjustment Switch-> +/- PD2/PD3
*
*  //Outputs   
*  - Horn increase LED indicator connected to digital pin PD1
*  - Horn Decrease LED indicator connected to digital pin PD4
*  - IGN switch LED indicator connected to digital pin PC4
*  - Horn switch LED indicator connected to digital pin PC6
*  - Horn PWM Output connected to digital pin PD6
*    
*  //LCD Data Pins- (PB1,PB2,PB3,PB4), R/W- GND, RS-PC2, EN-PC0  
*
*  This example code is in the public domain.
*  https://drive.google.com/file/d/1vwgjXQzhsoMb9QFSTUf1AIvTeQ1fhg4g/view?usp=sharing
*/

#include "GPIO.h"
#include "LCD.h"

// Driver Code
int main(void){
    gpio_init();                   //I/O initialization for all pins
    intrrupt_init();               //Interrupt initialization
    lcd_init();                    //LCD initialization
    ADC_init();                    //ADC  initialization
    lcd_animation();               //LCD calibration animation
    while(1){
        hornFuntions();            //Function to call all horn logic
    }
    return 0;
}
 //End of the program
