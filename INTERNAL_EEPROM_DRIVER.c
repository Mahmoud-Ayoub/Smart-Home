/*
 * INTERNAL_EEPROM_DRIVER.c
 *
 * Created: 23/07/2020 05:55:25 م
 *  Author: Blu-Ray
 */ 
#include "INTERNAL_EEPROM_DRIVER.h"

void EEPROM_write (unsigned int address , unsigned char data) {
	EEAR = address ;
	EEDR = data ;
	SET_OUTPUT_BIT(EECR,2) ;         // Master write enable
	SET_OUTPUT_BIT(EECR,1) ;        // write enable
	
	while(EECR & (1<<EEWE)) ;      // wait until EEWE = 0 (means writing is completed)
	
}
unsigned char EEPROM_read (unsigned int address)  {
	EEAR = address ;
	SET_OUTPUT_BIT(EECR,0) ;
	return EEDR ;
	
}