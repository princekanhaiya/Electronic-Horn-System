/***********************************************
Author: Prince Kanhaiya
Revision: 1.0.0
Last Updated: 28-05-2022
Files Info: ISR File
************************************************/
#include "GPIO.h"
#include "LCD.h"
extern uint8_t dutyCycle;
extern int hornCoilTemperature;
struct{
    volatile uint8_t hornSwitchStatus:1;
    volatile uint8_t ignSwitchStatus:1;
    volatile uint8_t hornSwIncStatus:1;
    volatile uint8_t hornSwDecStatus:1;
}switchStatus;

ISR(PCINT1_vect){   //ISR for ignition switch
    cli();
    if(!(PINC & (1 << PINC5))){
        switchStatus.ignSwitchStatus=1;
        SET_BIT(PORTC,PC4);   //ignition switch indicator led ON
        
        //Refreshing LCD Screen
        lcd_xy(0,0);
        lcd_str("                ");
        lcd_xy(0,0);
        lcd_str("ENGINE ON");
        lcd_xy(0,2);
        lcd_str("                ");
        lcd_xy(0,2);
        lcd_str("DUTY CYCLE ");
        lcd_int(((dutyCycle)*100)/255); //Linear mapping 0-255 to duty cycle 0-100%
        lcd_xy(0,3);
        lcd_str("COIL TEMP     ");
        lcd_xy(0,3);
        lcd_str("COIL TEMP ");
        lcd_int(hornCoilTemperature);
    }
    else{
        switchStatus.ignSwitchStatus=0;
        CLR_BIT(PORTC,PC4); //ignition switch indicator led off
        
        //Refreshing LCD Screen
        lcd_xy(0,0);
        lcd_str("                ");
        lcd_xy(0,0);
        lcd_str("ENGINE OFF");
        lcd_xy(0,2);
        lcd_str("                ");
        lcd_xy(0,2);
        lcd_str("DUTY CYCLE ");
        lcd_int(((dutyCycle)*100)/255); //Linear mapping 0-255 to duty cycle 0-100%
    }
    sei();
}

ISR(PCINT2_vect){   //ISR for horn key
    cli();
    switchStatus.hornSwitchStatus=~switchStatus.hornSwitchStatus;
    if(switchStatus.hornSwitchStatus){
        SET_BIT(PORTC,PC6);
        
        //Refreshing LCD Screen
        lcd_xy(0,1);
        lcd_str("                ");
        lcd_xy(0,1);
        lcd_str("HORN ON");
        lcd_xy(0,2);
        lcd_str("                ");
        lcd_xy(0,2);
        lcd_str("DUTY CYCLE ");
        lcd_int(((dutyCycle)*100)/255); //Linear mapping 0-255 to duty cycle 0-100%
        lcd_xy(0,3);
        lcd_str("COIL TEMP     ");
        lcd_xy(0,3);
        lcd_str("COIL TEMP ");
        lcd_int(hornCoilTemperature);
    }
    else{
        CLR_BIT(PORTC,PC6);

        //Refreshing LCD Screen
        lcd_xy(0,1);
        lcd_str("                ");
        lcd_xy(0,1);
        lcd_str("HORN OFF");
        lcd_xy(0,2);
        lcd_str("                ");
        lcd_xy(0,2);
        lcd_str("DUTY CYCLE ");
        lcd_int(((dutyCycle)*100)/255); //Linear mapping 0-255 to duty cycle 0-100%
        lcd_xy(0,3);
        lcd_str("COIL TEMP     ");
        lcd_xy(0,3);
        lcd_str("COIL TEMP ");
        lcd_int(hornCoilTemperature);
    }
    sei();
}

ISR(INT0_vect){ //ISR for increment switch
	cli();
    switchStatus.hornSwIncStatus=~switchStatus.hornSwIncStatus;
    if(switchStatus.hornSwIncStatus){
        SET_BIT(PORTD,PD1);

        lcd_xy(0,2);
        lcd_str("                ");
        lcd_xy(0,2);
        lcd_str("DUTY CYCLE ");
        uint8_t duty=((dutyCycle)*100)/255;//Linear mapping 0-255 to duty cycle 0-100%
        if(duty==1)
            lcd_str("100");
        else
        lcd_int(duty);
        lcd_xy(0,3);
        lcd_str("COIL TEMP     ");
        lcd_xy(0,3);
        lcd_str("COIL TEMP ");
        lcd_int(hornCoilTemperature);
    }
    else{
        CLR_BIT(PORTD,PD1);

        lcd_xy(0,2);
        lcd_str("                ");
        lcd_xy(0,2);
        lcd_str("DUTY CYCLE ");
        lcd_int(((dutyCycle)*100)/255); //Linear mapping 0-255 to duty cycle 0-100%
    }
    sei();
}

ISR(INT1_vect){ //ISR for decrement switch
	cli();
    switchStatus.hornSwDecStatus=~switchStatus.hornSwDecStatus;
    if(switchStatus.hornSwDecStatus){
        SET_BIT(PORTD,PD4);

        lcd_xy(0,2);
        lcd_str("                ");
        lcd_xy(0,2);
        lcd_str("DUTY CYCLE ");
        lcd_int(((dutyCycle)*100)/255); //Linear mapping 0-255 to duty cycle 0-100%
        lcd_xy(0,3);
        lcd_str("COIL TEMP     ");
        lcd_xy(0,3);
        lcd_str("COIL TEMP ");
        lcd_int(hornCoilTemperature);
    }
    else{
        CLR_BIT(PORTD,PD4);
        
        lcd_xy(0,2);
        lcd_str("                ");
        lcd_xy(0,2);
        lcd_str("DUTY CYCLE ");
        lcd_int(((dutyCycle)*100)/255); //Linear mapping 0-255 to duty cycle 0-100%
    }
    sei();
}
