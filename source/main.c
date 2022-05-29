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


//Function consist of all logics of horn system
void hornFuntions(void){
    /*attached to PC3 and Convertion of adc value to equivalent temp not required, potentiometer use insted of temperature sensor
    which give adc output 0-1024 */
    hornCoilTemperature=readADC(PC3);
    
    //If horn coil temp less than threshold temp (HORN_COIL_TEMP_THRESHOLD=500), it shall operate normally
    if(hornCoilTemperature <= HORN_COIL_TEMP_THRESHOLD){

        //if ignition switch and horn swith is ON play/adjust the the horn tone
        if(switchStatus.ignSwitchStatus && switchStatus.hornSwIncStatus){
            pwm(dutyCycle);
            if(switchStatus.hornSwIncStatus){
                dutyCycle += (dutyCycle>=MAX_DUTY_CYCLE) ? MAX_DUTY_CYCLE : FIVE_PER_DUTY_CYCLE; //Incrementing 5% duty cycle
                _delay_ms(200); 
            }
            if(switchStatus.hornSwIncStatus){
                dutyCycle -= (dutyCycle<=0)? MIN_DUTY_CYCLE : FIVE_PER_DUTY_CYCLE; //Decrementing 5% duty cycle
                _delay_ms(200);
            }
                      
        }
        else{
            pwm(OFF);
        }
    }

    //If horn coil temp exceed threshold temp, it shall operate at 10% duty cycle only
    if(hornCoilTemperature > HORN_COIL_TEMP_THRESHOLD && hornCoilTemperature < HORN_COIL_TEMP_MAX){
        pwm(TEN_PER_DUTY_CYCLE);     // Approximate PWM value for 10% duty cycle ie (255/100)*10=26
    }

    //If horn coil temp exceed maximum temp, it shall not operate
    if(hornCoilTemperature >= HORN_COIL_TEMP_MAX){
        pwm(OFF);
    }
}

 //End of the program
