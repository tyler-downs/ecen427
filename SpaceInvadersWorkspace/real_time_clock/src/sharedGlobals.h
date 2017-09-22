/*
 * sharedGlobals.h
 *
 *  Created on: Sep 15, 2017
 *      Author: superman
 */

#ifndef SHAREDGLOBALS_H_
#define SHAREDGLOBALS_H_

#include "xgpio.h"          // Provides access to PB GPIO driver.
#include <stdio.h>          // xil_printf and so forth.
#include "platform.h"       // Enables caching and other system stuff.
#include "mb_interface.h"   // provides the microblaze interrupt enables, etc.
#include "xintc_l.h"        // Provides handy macros for the interrupt controller.

#define HOUR_MAX 23 //max value for hours before resetting
#define MIN_SEC_MAX 59 //max value for minutes and seconds before resetting

#define TRUE 1 //used in lieu of bool
#define FALSE 0 //used in lieu of bool

//these are the values of the debounced buttons
extern u8 hour_btn; //left
extern u8 min_btn; //center
extern u8 sec_btn; //right
extern u8 up_btn; //up
extern u8 down_btn; //down

extern u8 hour; //current hour
extern u8 min; //current minute
extern u8 sec; //current second

extern u8 tickingEnabled; //flag that will be nonzero if the clock should automatically increment

//increments seconds, returns true if rolls over
u8 incSec();

//increments minutes, returns true if rolls over
u8 incMin();

//increments the hour
void incHour();

void printClock(); //prints the clock to the screen


#endif /* SHAREDGLOBALS_H_ */
