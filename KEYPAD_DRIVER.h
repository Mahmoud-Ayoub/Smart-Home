/*
 * KEYPAD_DRIVER.h
 *
 * Created: 25/07/2020 05:13:10 م
 *  Author: Blu-Ray
 */ 


#ifndef KEYPAD_DRIVER_H_
#define KEYPAD_DRIVER_H_

#include <avr/io.h>
#include <util/delay.h>

#define OUTPUT_ROW  PORTC                   // LSB is rows
#define INPUT_COL PINC >> 4                // MSB is columns
void KEYPAD_init (void) ; 
char KEYPAD_check_func (void) ;
void KEYPAD_wait (void) ;




#endif /* KEYPAD_DRIVER_H_ */