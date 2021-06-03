/*
 * LCD.c
 *
 * Created: 17/07/2020 04:11:54 م
 *  Author: Mahmoud-Ayoub
 */ 
#include "LCD.h"

void lcd_init (void) {
	DATA_PORT = 0xff ;            // all pins of PORT C is output
	DATA_OUT = 0x00 ;            // all pins are reseted
	
	SET_OUTPUT_BIT(DDRB,0) ;        // RW pin (RW = 0 << write) , (RW = 1 << Read) 
	RESET_INPUT_BIT(PORTB,0) ;
	
	lcd_discmd(0x33) ;       // needed commands for 4 bits mode   (group of initial commands must be sent to LCD)
	lcd_discmd(0x32) ;
	lcd_discmd(0x28) ;
	lcd_discmd(0x0e) ;
	lcd_discmd(0x01) ;
	_delay_us(2000) ;
	lcd_discmd(0x06) ;
	
}
void lcd_cmd_mode (char command) {
	DATA_OUT = command ;               // 0bxxxx_0000
	RESET_INPUT_BIT(DATA_OUT,Rs) ;
	SET_OUTPUT_BIT(DATA_OUT,E) ;
	_delay_ms(1) ;
	RESET_INPUT_BIT(DATA_OUT,E) ;
	
	
	
}
void lcd_discmd (char cmd) {
	char x ;
	x = cmd & 0xf0 ;
	lcd_cmd_mode(x) ;          // MSB of cmd is sent to LCD
	x = ((cmd<<4)&0xf0 );     // shift LSB to be in position of MSB , then
	lcd_cmd_mode(x) ;         // send rest of command to LCD
	
}

void lcd_data_mode (char data) {
	DATA_OUT = data ;               // 0bxxxx_0000
	SET_OUTPUT_BIT(DATA_OUT,Rs) ;
	SET_OUTPUT_BIT(DATA_OUT,E) ;
	_delay_ms(1) ;
	RESET_INPUT_BIT(DATA_OUT,E) ;
	
}
void lcd_outchar (char value) {
	char y ;
	y = value & 0xf0 ;
	lcd_data_mode(y) ;          // MSB of data is sent to LCD
	y = ((value<<4)&0xf0 );     // shift LSB to be in position of MSB , then
	lcd_data_mode(y) ;         // send rest of data to LCD
}
void lcd_outstr (char* str) {
	unsigned char i = 0 ;
	while (str[i] != 0){
		lcd_outchar(str[i]) ;
		i++ ;
	}
}
void lcd_clear (void) {
	lcd_discmd(0x01) ;          // clear command
}
void lcd_newline (void) {
	lcd_discmd(0xC0) ;
}
void lcd_shift_left (void) {
	lcd_discmd(0x10) ; 
}
void lcd_shift_right (void) {
	lcd_discmd(0x14) ; 
}
