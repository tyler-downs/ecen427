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

u8 hour_hold_btn = 0; //the value of the hour button when auto-incrementing started
u8 min_hold_btn = 0; //the value of the minute button when auto-incrementing started
u8 sec_hold_btn = 0; //the value of the second button when auto-incrementing started

void upTime_auto() //increments the hours, minutes, or seconds based on the saved button values
{
	if (sec_hold_btn != 0) //if second button is being pushed
		incSec(); //increment seconds
	if (min_hold_btn != 0) //if minute button is being pushed
		incMin(); //increment minutes
	if (hour_hold_btn != 0) //if hour button is being pushed
		incHour(); //increment hours

	printClock(); //update clock
	//we don't care about rollover like in normal operation
}

void downTime_auto() //decrements the hours, minutes, or seconds based on the saved button values
{
	if (sec_hold_btn != 0) //if second button is being pushed
		decSec(); //decrement seconds
	if (min_hold_btn != 0) //if minute button is being pushed
		decMin(); //decrement minutes
	if (hour_hold_btn != 0) //if hour button is being pushed
		decHour(); //decrement hours

	printClock(); //update clock
	//we don't care about rollover like in normal operation
}

#define MAX_WAIT 100 //wait 1 second to start auto-incrementing
#define INCREMENT_DELAY 50 //wait 1/2 second to auto-increment
u16 holdTimer = 0; //timer for waiting to start auto-incrementing
u16 incTimer = 0; //timer to control speed of auto-incrementing

void saveButtons() //save the values of the buttons when auto-incrementing starts
{
	hour_hold_btn = hour_btn; //save the value of the hour button
	min_hold_btn = min_btn; //save the value of the minute button
	sec_hold_btn = sec_btn; //save the value of the second button
}

enum {no_time_btns_st, wait_for_updown_st, up_pressed_st, down_pressed_st, updown_pressed_st, auto_up_st, auto_down_st} curState = no_time_btns_st;

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
		holdTimer++; //increment the hold timer (to measure when to start auto-incrementing)
		break;
	case down_pressed_st:
		tickingEnabled = FALSE; //stop the automatic clock ticking
		holdTimer++; //increment the hold timer (to measure when to start auto-decrementing)
		break;
	case updown_pressed_st:
		tickingEnabled = FALSE; //stop the automatic clock ticking
		break;
	case auto_up_st:
		tickingEnabled = FALSE; //stop the automatic clock ticking
		incTimer++; //increment the increment timer (to measure when to increment again in auto-incrementing)
		break;
	case auto_down_st:
		tickingEnabled = FALSE; //stop the automatic clock ticking
		incTimer++; //increment the increment timer (to measure when to decrement again in auto-decrementing)
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
			holdTimer = 0; //reset the hold timer
		}
		else if (down_btn != 0) //if down is pressed but not up
		{
			downTime();
			curState = down_pressed_st;
			holdTimer = 0; //reset the hold timer
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
			holdTimer = 0; //reset the hold timer
		}
		else if (up_btn != 0 && down_btn != 0) //if both up and down are pressed
		{
			curState = updown_pressed_st;
		}
		else if (holdTimer >= MAX_WAIT) //if up and a time button have been held for a second
		{
			saveButtons(); //save the values of the time buttons
			incTimer = 0; //reset increment timer
			upTime(); //increment time for whatever time buttons are being pushed
			curState = auto_up_st;
		}
		//else if up is pressed and down is not, and the holdTimer hasn't reached 1 second, stay here
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
			holdTimer = 0; //reset the hold timer
		}
		else if (up_btn != 0 && down_btn != 0) //if both up and down are pressed
		{
			curState = updown_pressed_st;
		}
		else if (holdTimer >= MAX_WAIT) //if down and a time button have been held for a second
		{
			saveButtons(); //save the values of the time buttons
			incTimer = 0; //reset increment timer
			downTime(); //decrement time for whatever time buttons are being pushed
			curState = auto_down_st;
		}
		//else if down is pressed and up is not, and the holdTimer hasn't reached 1 second, stay here
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
			holdTimer = 0; //reset the hold timer
		}
		else if (up_btn == 0 && down_btn != 0) //if up is released and down is still pressed
		{
			curState = down_pressed_st;
			holdTimer = 0; //reset the hold timer
		}
		//else if both up and down are still pressed, stay here.
		break;
	case auto_up_st:
		if (up_btn == 0) //if the up button is released
		{
			if(timeBtnPressed()) //if a time button is being pressed
				curState = wait_for_updown_st;
			else //no time button is being pressed
				curState = no_time_btns_st;
		}
		else //if the up button is still pressed
		{
			if (incTimer >= INCREMENT_DELAY) //if 1/2 a second has passed since the last increment
			{
				upTime_auto(); //increment the time based on the saved time button values
				incTimer = 0; //reset the increment timer
			}
			//stay in this state
		}

		break;
	case auto_down_st:
		if (down_btn == 0) // if the down button is released
		{
			if (timeBtnPressed()) //if a time button is being pressed
				curState = wait_for_updown_st;
			else //no time button is being pressed
				curState = no_time_btns_st;
		}
		else //if the down button is still pressed
		{
			if (incTimer >= INCREMENT_DELAY) //if 1/2 a second has passed since the last decrement
			{
				downTime_auto(); //decrement the time based on the saved time button values
				incTimer = 0; //reset the increment timer
			}
			//stay in this state
		}
		break;
	}
}

