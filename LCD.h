/*
 * LCD.h
 *
 * Created: 17/07/2020 04:13:14 م
 *  Author: Mahmoud-Ayoub
 */ 


#ifndef LCD_H_
#define LCD_H_

#include <avr/io.h>
#include <util/delay.h>

#define DATA_PORT  DDRA                  // all lcd pins (data + command) are connected to same PORT (A)
#define DATA_OUT  PORTA                 // from PC4 to PC7
#define Rs 0
#define E  2
#define mode 4                      // default mode is 4bits mode

#define  SET_OUTPUT_BIT(reg,bit)  ((reg)|=(1)<<(bit))
#define  RESET_INPUT_BIT(reg,bit)  ((reg)&=~((1)<<(bit)))
#define  TOGGLE_BIT(reg,bit)  ((reg)^=(1)<<(bit))


void lcd_init (void) ;
void lcd_cmd_mode (char command) ;
void lcd_discmd (char cmd) ;
void lcd_data_mode (char data) ;
void lcd_outchar (char value) ;
void lcd_outstr (char* str) ;
void lcd_clear (void) ;
void lcd_newline (void) ; 
void lcd_shift_left (void) ; 
void lcd_shift_right (void) ; 



#endif /* LCD_H_ */