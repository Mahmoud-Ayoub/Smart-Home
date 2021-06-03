/*
 * INTERNAL_EEPROM_DRIVER.h
 *
 * Created: 23/07/2020 05:54:33 م
 *  Author: Blu-Ray
 */ 


#ifndef INTERNAL_EEPROM_DRIVER_H_
#define INTERNAL_EEPROM_DRIVER_H_

#include <avr/io.h>
#include "GPIO.h"

void EEPROM_write (unsigned int address , unsigned char data) ;
unsigned char EEPROM_read (unsigned int address)  ;



#endif /* INTERNAL_EEPROM_DRIVER_H_ */