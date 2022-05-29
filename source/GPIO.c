/***********************************************
Author: Prince Kanhaiya
Revision: 1.0.0
Last Updated: 28-05-2022
Files Info: GPIO File
************************************************/
#include "GPIO.h"
#include"ADC.h"

uint8_t dutyCycle= HORN_PWM_THRESHOLD;
uint16_t hornCoilTemperature= HORN_COIL_TEMP_THRESHOLD;

extern struct{
    volatile uint8_t hornSwitchStatus:1;  //horn switch flag
    volatile uint8_t ignSwitchStatus:1;   //ignition switch flag
    volatile uint8_t hornSwIncStatus:1;   //increment switch flag
    volatile uint8_t hornSwDecStatus:1;   //decrement switch flag
}switchStatus;

void gpio_init(void){
    //LCD PORTS SETTINGS
    //LCD Data Pins- (PB1,PB2,PB3,PB4), R/W- GND, RS-PC2, EN-PC0 
    SET_BIT(DDRB,PB1);
    SET_BIT(DDRB,PB2);
    SET_BIT(DDRB,PB3);
    SET_BIT(DDRB,PB4);

    SET_BIT(DDRC,PC0);
    SET_BIT(DDRC,PC2);

    SET_BIT(PORTB,PB1);
    SET_BIT(PORTB,PB2);
    SET_BIT(PORTB,PB3);
    SET_BIT(PORTB,PB4);

    SET_BIT(PORTC,PC0);
    SET_BIT(PORTC,PC2);

    //PINCHANGE INTRRUPT STTINGS FOR SWITCHES
    SET_BIT(DDRC,PC6); //OUTPUT
    SET_BIT(DDRC,PC4); //OUTPUT
    SET_BIT(DDRD,PD1); //OUTPUT
    SET_BIT(DDRD,PD4); //OUTPUT

    CLR_BIT(DDRD,PD0); //horn switch
    CLR_BIT(DDRD,PD2); //horn adjustment '+' switch 
    CLR_BIT(DDRD,PC3); //horn adjustment '-' switch 
    CLR_BIT(DDRC,PC5); //ignition switch

    SET_BIT(PORTD,PD0); //PULL UP to avoid any floating value
    SET_BIT(PORTC,PC5); //PULL UP
    SET_BIT(PORTD,PD2); //PULL UP
    SET_BIT(PORTD,PC3); //PULL UP

    //PWM PIN
    SET_BIT(DDRD,PD6); 

    //LED indicators Pins setup
    SET_BIT(PORTC,PC4);
    SET_BIT(PORTC,PC6);
    SET_BIT(PORTD,PD1);
    SET_BIT(PORTD,PD4);
    _delay_ms(500);

    //Initially all LED shall be switched off
    CLR_BIT(PORTC,PC4);
    CLR_BIT(PORTC,PC6);
    CLR_BIT(PORTD,PD1);
    CLR_BIT(PORTD,PD4);
}

//All input switches are connected to hardware intrrupt pins
void intrrupt_init(void){
    SET_BIT(PCICR,PCIE2);
    SET_BIT(PCICR,PCIE1);
	SET_BIT(PCMSK2,PCINT16);
	SET_BIT(PCMSK1,PCINT13);
	EICRA |= (1 << ISC00);    // set interrupt to trigger on ANY logic change
	EICRA |= (1 << ISC10);    // set interrupt to trigger on ANY logic change
    EIMSK |= (1 << INT0);     // Turns on INT0
    EIMSK |= (1 << INT1);     // Turns on INT1
	sei();

    //Initialize all the switch status to false
	switchStatus.hornSwitchStatus=0;
	switchStatus.ignSwitchStatus=0;
	switchStatus.hornSwIncStatus=0;
	switchStatus.hornSwIncStatus=0;
}

//Function consist of all logics of horn system
void hornFuntions(void){
    hornCoilTemperature=readADC(17); //attached to PC3

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
