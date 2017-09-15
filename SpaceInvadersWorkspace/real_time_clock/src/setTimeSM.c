/*
 * setTimeSM.c
 *
 *  Created on: Sep 15, 2017
 *      Author: superman
 */
#include "setTimeSM.h"
#include "sharedGlobals.h"


u8 timeBtnPressed() //return (true) if one or more of the hour, second, or minute buttons are pressed
{
	return (hour_btn != 0 || min_btn != 0 || sec_btn != 0);
}

void decSec() //decrements seconds and rolls over as necessary
{
	if (sec == 0)
		sec = MIN_SEC_MAX;
	else
		sec--;
}

void decMin() //decrements minutes and rolls over as necessary
{
	if (min == 0)
		min = MIN_SEC_MAX;
	else
		min--;
}

void decHour() //decrements hours and rolls over as necessary
{
	if (hour == 0)
		hour = HOUR_MAX;
	else
		hour--;
}

void upTime() //runs when up button is pushed to manually set time
{
	if (sec_btn != 0) //if second button is being pushed
		incSec(); //increment seconds
	if (min_btn != 0) //if minute button is being pushed
		incMin(); //increment minutes
	if (hour_btn != 0) //if hour button is being pushed
		incHour(); //increment hours

	printClock(); //update clock
	//we don't care about rollover like in normal operation
}

void downTime() //runs when down button is pushed to manually set time
{
	if (sec_btn != 0) //if second button is being pushed
		decSec(); //decrement seconds
	if (min_btn != 0) //if minute button is being pushed
		decMin(); //decrement minutes
	if (hour_btn != 0) //if hour button is being pushed
		decHour(); //decrement hours

	printClock(); //update clock
	//we don't care about rollover like in normal operation
}

enum {no_time_btns_st, wait_for_updown_st, up_pressed_st, down_pressed_st, updown_pressed_st} curState = no_time_btns_st;

void setTime_tick()
{
	//state actions
	switch(curState)
	{
	case no_time_btns_st:
		tickingEnabled = TRUE; //let the clock keep ticking
		break;
	case wait_for_updown_st:
		tickingEnabled = FALSE; //stop the automatic clock ticking
		break;
	case up_pressed_st:
		tickingEnabled = FALSE; //stop the automatic clock ticking
		break;
	case down_pressed_st:
		tickingEnabled = FALSE; //stop the automatic clock ticking
		break;
	case updown_pressed_st:
		tickingEnabled = FALSE; //stop the automatic clock ticking
		break;
	}


	//transitions, mealy actions
	switch(curState)
	{
	case no_time_btns_st:
		if (timeBtnPressed())
		{
			curState = wait_for_updown_st;
		}
		//else stay here
		break;
	case wait_for_updown_st:
		if (!timeBtnPressed()) //if no time button is being pressed
		{
			curState = no_time_btns_st;
		}
		//all following cases require that a time button is being pressed
		else if (up_btn != 0 && down_btn != 0) //if both up and down are pressed
		{
			curState = updown_pressed_st;
		}
		else if (up_btn != 0) //if up is pressed but not down
		{
			upTime();
			curState = up_pressed_st;
		}
		else if (down_btn != 0) //if down is pressed but not up
		{
			downTime();
			curState = down_pressed_st;
		}
		//else if neither up nor down is pressed stay here and continue waiting
		break;
	case up_pressed_st:
		if (!timeBtnPressed()) //if no time button is being pressed
		{
			curState = no_time_btns_st;
		}
		//all following cases require that a time button is being pressed
		else if (up_btn == 0 && down_btn == 0) //if both up and down are released
		{
			curState = wait_for_updown_st;
		}
		else if (up_btn == 0 && down_btn != 0) //if up is released and down is pressed
		{
			curState = down_pressed_st;
		}
		else if (up_btn != 0 && down_btn != 0) //if both up and down are pressed
		{
			curState = updown_pressed_st;
		}
		//else if up is pressed and down is not, stay here
		break;
	case down_pressed_st:
		if (!timeBtnPressed()) //if no time button is being pressed
		{
			curState = no_time_btns_st;
		}
		//all following cases require that a time button is being pressed
		else if (up_btn == 0 && down_btn == 0) //if both up and down are released
		{
			curState = wait_for_updown_st;
		}
		else if (down_btn == 0 && up_btn != 0) //if down is released and up is pressed
		{
			curState = up_pressed_st;
		}
		else if (up_btn != 0 && down_btn != 0) //if both up and down are pressed
		{
			curState = updown_pressed_st;
		}
		//else if down is pressed and up is not, stay here
		break;
	case updown_pressed_st:
		if (!timeBtnPressed()) //if no time button is being pressed
		{
			curState = no_time_btns_st;
		}
		//all following cases require that a time button is being pressed
		else if (up_btn == 0 && down_btn == 0) //if both up and down are released
		{
			curState = wait_for_updown_st;
		}
		else if (down_btn == 0 && up_btn != 0) //if down is released and up is still pressed
		{
			curState = up_pressed_st;
		}
		else if (up_btn == 0 && down_btn != 0) //if up is released and down is still pressed
		{
			curState = down_pressed_st;
		}
		//else if both up and down are still pressed, stay here.
		break;
	}
}

