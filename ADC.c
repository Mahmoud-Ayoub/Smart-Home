/*
 * ADC_DRIVER.c
 *
 * Created: 23/07/2020 04:14:44 م
 *  Author: Blu-Ray
 */ 
#include "ADC_DRIVER.h"

void ADC_init (void) {
	//SET_OUTPUT_BIT(ADMUX,6) ;          // AREF = AVCC
	
	//RESET_INPUT_BIT(ADMUX,0) ;         // ADC0
	//RESET_INPUT_BIT(ADMUX,1) ;
	//RESET_INPUT_BIT(ADMUX,2) ;
	//RESET_INPUT_BIT(ADMUX,3) ;
	//RESET_INPUT_BIT(ADMUX,4) ;
	ADMUX = 0xC0 ; 
	//SET_OUTPUT_BIT(ADCSRA,7) ;           // ADC enable
	//SET_OUTPUT_BIT(ADCSRA,0) ;           // prescaler = 128
	//SET_OUTPUT_BIT(ADCSRA,1) ;
	//SET_OUTPUT_BIT(ADCSRA,2) ;
	 ADCSRA = 0x87 ; 
	
}
uint16_t ADC_read (void) {
	SET_OUTPUT_BIT(ADCSRA,6) ;        // start conversion
	while (ADCSRA & (1<<ADIF) == 0);   // check if conversion is completed
	return ADC ;
}