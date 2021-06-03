/*
 * KEYPAD_DRIVER.c
 *
 * Created: 25/07/2020 05:14:19 م
 *  Author: Blu-Ray
 */ 
#include "KEYPAD_DRIVER.h"

void KEYPAD_init (void) {
	  DDRC = 0x0F ;             // initialization for ports (LSB is output row) and (MSB is input columns)

}



char KEYPAD_check_func (void) {
	 DDRC = 0x0F ;
	char i ;
	while (1){
		for (i=1 ; i<=8 ; i = i << 1 ){         // loop for sending ones for rows
			OUTPUT_ROW = i ;
			_delay_ms(1) ;
			if (i ==1 ){
				switch(INPUT_COL){
					case 1  : return '1' ; break;
					case 2  : return '2' ; break;
					case 4  : return '3' ; break;
				}
				
			}
			else if (i ==2 ){
				switch(INPUT_COL){
					case 1  : return '4' ; break;
					case 2  : return '5' ; break;
					case 4  : return '6' ; break;
				}
				
			}
			else if (i ==4 ){
				switch(INPUT_COL){
					case 1  : return '7' ; break;
					case 2  : return '8' ; break;
					case 4  : return '9' ; break;
				}
				
			}
			else if (i ==8 ){
				switch(INPUT_COL){
					case 1  : return '*' ; break;
					case 2  : return '0' ; break;
					case 4  : return '#' ; break;
				}
				
			}
			
		}
		
	}
	
}
void KEYPAD_wait (void) {
	while(INPUT_COL) ;
}