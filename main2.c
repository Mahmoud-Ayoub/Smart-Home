/*
 * smart home 2.c
 *
 * Created: 04/08/2020 03:18:33 م
 * Author : Blu-Ray
 */ 

#include <avr/io.h>
#include <stdlib.h>
#include "GPIO.h"
#include "ADC_DRIVER.h"
#include "LCD.h"


void air_on (void) ;
void air_off (void) ;
void heater_on (void) ;
void heater_off(void) ; 

int main(void)
{
    DDRD = 0xff ;               // port D is output

	int num ; 
	char temp [8] ; 
	
	  ADC_init() ;
	  lcd_init() ; 
	
    while (1) 
    {
	
		 num = ADC_read() / 4 ; 
		 itoa (num , temp , 10); 
		 lcd_outstr(temp) ;
		 lcd_outchar(0xDF) ; 
		 lcd_outstr("C");
		 _delay_ms(20) ;
	         lcd_home() ; 
		
		 if (num > 25 ) {             // too hot 
			 air_on() ;
			 heater_off() ;
		 }
		 else if (num < 15) {       // too cold
			 air_off() ;
			 heater_on() ;  
		 }
		 else {
			 air_off() ;
			 heater_off() ; 
		 }
	
		 
		
    }
	    
  
}
void air_on (void) {
	SET_OUTPUT_BIT(PORTD,0) ;
	RESET_INPUT_BIT(PORTD,1) ; 

}
void air_off (void) {
	RESET_INPUT_BIT(PORTD,0) ;
	RESET_INPUT_BIT(PORTD,1) ; 
}
void heater_on (void) {
	SET_OUTPUT_BIT(PORTD,2) ;
	RESET_INPUT_BIT(PORTD,3) ;
}
void heater_off(void) {
	RESET_INPUT_BIT(PORTD,2) ;
	RESET_INPUT_BIT(PORTD,3) ;
}
