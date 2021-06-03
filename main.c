/*
 * smart home.c
 *
 * Created: 25/07/2020 08:22:14 م
 * Author : Mahmoud Ayoub
 */ 

#include <avr/io.h>
#include "LCD.h"
#include "KEYPAD_DRIVER.h"
#include "INTERNAL_EEPROM_DRIVER.h"

void set_admin_pass (void) ; 
void set_guest_pass (void) ; 

void enter_admin_pass (void) ; 
void enter_guest_pass (void) ;

unsigned int  check_admin (void) ; 
unsigned int  check_guest (void) ; 

void room1_on (void) ; 
void room2_on (void) ; 
void room3_on (void) ;
void room4_on (void) ;

void room1_off (void) ;
void room2_off (void) ;
void room3_off (void) ;
void room4_off (void) ;

void Room1 (void) ; 
void Room2 (void) ; 
void Room3 (void) ; 
void Room4 (void) ; 

void tv_on (void) ;
void tv_off (void) ; 
void TV (void) ; 

static char admin_stored [4] ;
static char admin_entered[4] ;
 
static char guest_stored [4] ;
static char guest_entered[4] ;

int main(void)
{
   lcd_init() ;               // lcd initialization  
   KEYPAD_init() ;           // keypad initialization 
   
   unsigned char m ;              // mode of house 
   unsigned char room_num ;       // light action 
   unsigned char i ; 
   int x , y ; 
   
    
   lcd_outstr("WELCOME...") ; 
   _delay_ms(1000) ; 
   lcd_clear() ; 
   
   if (EEPROM_read(0x00) == 0xff ) {
	  set_admin_pass() ;
	  set_guest_pass() ;                           // now passwords are set
   }  
                                      
   
   while (1) {
	          SET_OUTPUT_BIT(DDRD,0) ;
	          RESET_INPUT_BIT(PORTD,0) ;             // light of admin mode is OFF
			  SET_OUTPUT_BIT(DDRD,1) ;
			  RESET_INPUT_BIT(PORTD,1) ;             // light of guest mode is OFF
			  
	          lcd_clear() ; 
			  lcd_outstr("0 : Admin mode");       // choosing between (admin) mode or (guest) mode
			  lcd_newline() ;
			  
			  lcd_outstr("1 : Guest mode") ;
			  _delay_ms(2000) ;
			  lcd_clear() ;
			 
	// --------------------------------------------------------------------------------------------------------		
			 
			  m = KEYPAD_check_func();           // user selection between 2 modes
			  KEYPAD_wait() ;
			  
			  
			  switch (m) {
				   case '0' :                            // ADMIN mode
						     enter_admin_pass() ;        // enter admin pass 
							x= check_admin() ; 		   // check 
				             break;
				   case '1' :                        // GUEST mode
				            enter_guest_pass() ; 
						    y= check_guest() ; 
				            break;
			             }
	// --------------------------------------------------------------------------------------------------------	
	if (x==1 || y==1) {

            lcd_outstr("1-light control") ;       // light control in both admin or guest mode 
			_delay_ms(2000) ;
			lcd_clear() ; 
	for (i=0 ; i<4 ; i++) {
	        lcd_clear() ; 

			lcd_outstr("1:Room1 2: Room2") ; 
			lcd_newline() ; 
			lcd_outstr("3:Room3 4: Room4") ; 
			
			_delay_ms(2000) ; 
			lcd_clear() ; 
			 						 
			room_num = KEYPAD_check_func() ; 
			KEYPAD_wait() ; 
			switch (room_num) {
				  case '1' : 
				           Room1() ;
						   break;
						   
				  case '2' : 
				           Room2() ;
						   break;
						  	    			               	
				  case '3' :
				           Room3() ; 
						   break;
				
				  case '4' :
				           Room4() ; 
						   break;	
						   }	   	   			 
						 	
}
   // --------------------------------------------------------------------------------------------------------
           switch (m) {
	             case '0' :                           // ADMIN mode 
							lcd_clear() ; 
							lcd_outstr("2-TV control") ;       // TV control in admin mode only
							_delay_ms(2000) ;
							lcd_clear() ;
							TV() ; 
	                        break;
	             case '1' :                        // GUEST mode
	
	                        break;
   }
}
}						  
}

void set_admin_pass (void) {
   
	unsigned int i = 0 ; 
	                                            // admin mode
    lcd_outstr ("Set Admin pass") ;
    lcd_newline() ;
    for (i=0 ; i<4 ; i++) {
		    admin_stored[i]  = KEYPAD_check_func() ;
		    lcd_outchar(admin_stored[i]) ;
		    KEYPAD_wait() ;
		    _delay_ms(100) ;
		    lcd_shift_left() ;
		    lcd_outchar('*') ;
		    _delay_ms(100) ;
		    EEPROM_write(i , admin_stored[i] ) ;
		                  
	        }
	                  
	        lcd_clear() ;
			lcd_outstr("Admin") ;
			lcd_newline() ;
	        lcd_outstr("pass is set") ;
			_delay_ms(2000) ; 
			lcd_clear() ; 
			
}

void set_guest_pass(void) {
	  
	  unsigned int j = 4 ;
	  lcd_outstr ("Set Guest pass") ;
	  lcd_newline() ;
	  for (j=4 ; j<8 ; j++) {
		  guest_stored[j-4]  = KEYPAD_check_func() ;
		  lcd_outchar(guest_stored[j-4]) ;
		  KEYPAD_wait() ;
		  _delay_ms(100) ;
		  lcd_shift_left() ;
		  lcd_outchar('*') ;
		  _delay_ms(100) ;
		  EEPROM_write(j , guest_stored[j-4] ) ;
		  
	  }
	  
	  lcd_clear() ;
	  lcd_outstr("Guest") ;
	  lcd_newline() ; 
	  lcd_outstr("pass is set") ;
	  _delay_ms(2000) ;
	  lcd_clear() ;
	
}
void enter_admin_pass (void) {
	    
	    unsigned int i = 0 ;
	    
	    lcd_outstr ("Enter Admin pass") ;
	    lcd_newline() ;
	    for (i=0 ; i<4 ; i++) {
		    admin_entered[i]  = KEYPAD_check_func() ;
		    lcd_outchar( admin_entered[i]) ;
		    KEYPAD_wait() ;
		    _delay_ms(100) ;
		    lcd_shift_left() ;
		    lcd_outchar('*') ;
		    _delay_ms(100) ;
		   
		    
	    }
	 	    	
}
void enter_guest_pass (void) {
	   unsigned int i = 0 ;
	   
	   lcd_outstr ("Enter Guest pass") ;
	   lcd_newline() ;
	   for (i=0 ; i<4 ; i++) {
		   guest_entered[i]  = KEYPAD_check_func() ;
		   lcd_outchar( guest_entered[i]) ;
		   KEYPAD_wait() ;
		   _delay_ms(100) ;
		   lcd_shift_left() ;
		   lcd_outchar('*') ;
		   _delay_ms(100) ;
		   
		   
	   }
	
}

unsigned int  check_admin (void) {
	unsigned int i = 0 ;
    unsigned int flag = 0 ; 
	unsigned char eeprom_data[4] ; 
	for (i=0 ; i<4 ; i++) {
		eeprom_data[i] = EEPROM_read(i) ; 
	}
	
	for (i = 0  ; i<4 ; i++) {
			if (eeprom_data[i] == admin_entered[i])
			{
				flag ++ ;
			}
			else break;
	}
	
	if (flag==4) {
		lcd_clear() ; 
		SET_OUTPUT_BIT(DDRD,0) ; 
		SET_OUTPUT_BIT(PORTD,0) ;             // light of admin mode is ON
		lcd_outstr("Valid") ; 
		_delay_ms(3000) ; 
		lcd_clear() ; 
		return 1 ; 
	}
	else {
		  lcd_clear() ;
		  lcd_outstr(" Not Valid") ;
		  _delay_ms(3000) ;
		  lcd_clear() ;
		  return 0 ;
	}
	  
	
}
unsigned int  check_guest (void) {
		unsigned int j = 4 ;
		unsigned int flag = 0 ;
		unsigned char eeprom_data[4] ;
		 for (j=4 ; j<8 ; j++) {
			eeprom_data[j-4] = EEPROM_read(j) ;
		}
		
		for (j = 0  ; j<4 ; j++) {
			if (eeprom_data[j] == guest_entered[j])
			{
				flag ++ ;
			}
			else break;
		}
		
		if (flag==4) {
			lcd_clear() ;
			lcd_outstr("Valid") ;
			SET_OUTPUT_BIT(DDRD,1) ; 
			SET_OUTPUT_BIT(PORTD,1) ;             // light of guest mode is ON
			_delay_ms(3000) ;
			lcd_clear() ;
			return 1 ; 
		}
		else {
				lcd_clear() ;
				lcd_outstr(" Not Valid") ;
				_delay_ms(3000) ;
				lcd_clear() ;
				return 0 ;
			
		}
	
}

void room1_on (void) {
	
	SET_OUTPUT_BIT(DDRB,0) ;       
	SET_OUTPUT_BIT(PORTB,0) ;     // room1 light is ON

}
void room2_on (void) {
	
	SET_OUTPUT_BIT(DDRB,1) ;
	SET_OUTPUT_BIT(PORTB,1) ;     // room1 light is ON

}
void room3_on (void) {
	
	SET_OUTPUT_BIT(DDRB,2) ;
	SET_OUTPUT_BIT(PORTB,2) ;     // room1 light is ON

}
void room4_on (void) {
	
	SET_OUTPUT_BIT(DDRB,3) ;
	SET_OUTPUT_BIT(PORTB,3) ;     // room1 light is ON

}

void room1_off (void) {
	
	SET_OUTPUT_BIT(DDRB,0) ;
	RESET_INPUT_BIT(PORTB,0) ;     // room1 light is OFF

}
void room2_off (void) {
	
	SET_OUTPUT_BIT(DDRB,1) ;
	RESET_INPUT_BIT(PORTB,1) ;     // room1 light is OFF

}
void room3_off (void) {
	
	SET_OUTPUT_BIT(DDRB,2) ;
	RESET_INPUT_BIT(PORTB,2) ;     // room1 light is OFF

}
void room4_off (void) {
	
	SET_OUTPUT_BIT(DDRB,3) ;
	RESET_INPUT_BIT(PORTB,3) ;     // room1 light is OFF

}
void Room1 (void) {
	 
	 unsigned char room_out ;
	 lcd_clear() ;
	 lcd_outstr("Room1 ") ;
	 if (PINB & 0b00000001) {
		 lcd_outstr("S: ON") ;
		 lcd_newline();
		 lcd_outstr("1:ON 2:OFF 0:ret") ;
		 room_out = KEYPAD_check_func() ;
		 KEYPAD_wait() ;
		 switch(room_out) {
			 case '1' : room1_on() ;
			            break;
			 case '2' : room1_off() ;
			            break;
			 case '0' : lcd_clear() ;
			            return ;
			           
		 }
		 
	 }
	 else   {
		 lcd_outstr("S: OFF") ;
		 lcd_newline();
		 lcd_outstr("1:ON 2:OFF 0:ret") ;
		 room_out = KEYPAD_check_func() ;
		 KEYPAD_wait() ;
		 switch(room_out) {
			 case '1' : room1_on() ;
			            break;
			 case '2' : room1_off() ;
			            break;
			 case '0' : lcd_clear() ;
			            return ;
			           
		 }
	 }
}
void Room2 (void) {
    
	unsigned char room_out ; 
	lcd_clear() ;
	lcd_outstr("Room2 ") ;
	if (PINB & 0b00000010) {
		lcd_outstr("S: ON") ;
		lcd_newline();
		lcd_outstr("1:ON 2:OFF 0:ret") ;
		room_out = KEYPAD_check_func() ;
		KEYPAD_wait() ;
		switch(room_out) {
			case '1' : room2_on() ;
			           break;
			case '2' : room2_off() ;
			           break;
			case '0' : lcd_clear() ;
			           return ;
			           
		}
		
	}
	else  {
		lcd_outstr("S: OFF") ;
		lcd_newline();
		lcd_outstr("1:ON 2:OFF 0:ret") ;
		room_out = KEYPAD_check_func() ;
		KEYPAD_wait() ;
		switch(room_out) {
			case '1' : room2_on() ;
			           break;
			case '2' : room2_off() ;
			           break;
			case '0' : lcd_clear() ;
			           return ;
			
		}
	}
	
}
void Room3(void) {
	
	  unsigned char room_out ; 
	  lcd_clear() ;
	  lcd_outstr("Room3 ") ;
	  if (PINB & 0b00000100) {
		  lcd_outstr("S: ON") ;
		  lcd_newline();
		  lcd_outstr("1:ON 2:OFF 0:ret") ;
		  room_out = KEYPAD_check_func() ;
		  KEYPAD_wait() ;
		  switch(room_out) {
			  case '1' : room3_on() ;
			             break;
			  case '2' : room3_off() ;
			             break;
			  case '0' : lcd_clear() ;
			             return ; 
			 
		  }
		  
	  }
	  else   {
		  lcd_outstr("S: OFF") ;
		  lcd_newline();
		  lcd_outstr("1:ON 2:OFF 0:ret") ;
		  room_out = KEYPAD_check_func() ;
		  KEYPAD_wait() ;
		  switch(room_out) {
			  case '1' : room3_on() ;
			             break;
			  case '2' : room3_off() ;
			             break;
			  case '0' : lcd_clear() ;
			             return ; 
			 
		  }
	  }
	  
}
void Room4(void) {
	
	 unsigned char room_out ; 
	 lcd_clear() ;
	 lcd_outstr("Room4 ") ;
	 if (PINB & 0b00001000) {
		 lcd_outstr("S: ON") ;
		 lcd_newline();
		 lcd_outstr("1:ON 2:OFF 0:ret") ;
		 room_out = KEYPAD_check_func() ;
		 KEYPAD_wait() ;
		 switch(room_out) {
			 case '1' : room4_on() ;
			            break;
			 case '2' : room4_off() ;
			            break;
			 case '0' : lcd_clear() ;
			            return ;
			
		 }
		 
	 }
	 else {
		 lcd_outstr("S: OFF") ;
		 lcd_newline();
		 lcd_outstr("1:ON 2:OFF 0:ret") ;
		 room_out = KEYPAD_check_func() ;
		 KEYPAD_wait() ;
		 switch(room_out) {
			 case '1' : room4_on() ;
			            break;
			 case '2' : room4_off() ;
			            break;
			 case '0' : lcd_clear() ;
			            return ;
			
		 }
	 }
	 
	 
}
void tv_on (void) {
	   SET_OUTPUT_BIT(DDRD,2) ;        // TV_ON
	   SET_OUTPUT_BIT(PORTD,2) ;
	   
}
void tv_off (void) {
	   SET_OUTPUT_BIT(DDRD,2) ;        // TV_OFF
	   RESET_INPUT_BIT(PORTD,2) ;
}
void TV (void) {
	unsigned char tv_out ; 
	if (PIND & 0b00000100) {           // check if tv is on 
		lcd_clear() ;
		lcd_outstr("TV  S:ON") ; 
		lcd_newline() ; 
		 lcd_outstr("1:ON 2:OFF 0:ret") ;
		tv_out = KEYPAD_check_func() ; 
		KEYPAD_wait() ; 
		switch(tv_out){
			case '1' :  tv_on() ;
			            break;
			case '2' :  tv_off() ; 
			            break;	
		    case '0' : lcd_clear() ;
			            return ;					
		}
	}
	else {
		lcd_clear() ;
		lcd_outstr("TV  S:OFF") ;
		lcd_newline() ;
		 lcd_outstr("1:ON 2:OFF 0:ret") ;
		tv_out = KEYPAD_check_func() ;
		KEYPAD_wait() ;
		switch(tv_out){
			case '1' :  tv_on() ;
			            break;
			case '2' :  tv_off() ;
				        break;
			 case '0' : lcd_clear() ;
			            return ;			
			}
	}
}