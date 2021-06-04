/*
 * ADC_DRIVER.h
 *
 * Created: 23/07/2020 04:13:22 م
 *  Author: Blu-Ray
 */ 


#ifndef ADC_DRIVER_H_
#define ADC_DRIVER_H_

#include <avr/io.h>
#include "GPIO.h"
#include <util/delay.h>

void ADC_init (void)  ;
uint16_t ADC_read (void) ;




#endif /* ADC_DRIVER_H_ */