/*
 * sharedGlobals.c
 *
 *  Created on: Sep 15, 2017
 *      Author: superman
 */

#include "sharedGlobals.h"

u8 hour_btn = 0; //left
u8 min_btn = 0; //center
u8 sec_btn = 0; //right
u8 up_btn = 0; //up
u8 down_btn = 0; //down

#define DEFAULT_SEC 45

u8 hour = HOUR_MAX; //current hour
u8 min = MIN_SEC_MAX; //current minute
u8 sec = DEFAULT_SEC; //current second

u8 tickingEnabled = TRUE; //flag that will be nonzero if the clock should automatically increment

u8 incSec() //increments seconds, returns true if rolls over
{
	if (sec >= MIN_SEC_MAX)
	{
		sec = 0;
		return TRUE;
	}
	else
	{
		sec++;
		return FALSE;
	}
}

u8 incMin() //increments minutes, returns true if rolls over
{
	if (min >= MIN_SEC_MAX)
	{
		min = 0;
		return TRUE;
	}
	else
	{
		min++;
		return FALSE;
	}
}

void incHour() //increments the hour
{
	if (hour >= HOUR_MAX)
		hour = 0;
	else
		hour++;
}

void printClock() //prints the clock to the screen
{
	xil_printf("\r%02d:%02d:%02d", hour, min, sec);
}

