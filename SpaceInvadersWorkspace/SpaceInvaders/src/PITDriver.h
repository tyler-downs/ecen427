/*
 * PITDriver.h
 *
 *  Created on: Nov 8, 2017
 *      Author: superman
 */

#ifndef PITDRIVER_H_
#define PITDRIVER_H_

#include <stdint.h>

void pit_init(); //initialize the PIT by enabling the counter and interrupts
void pit_setInterval(uint32_t clockInterval); //set the interrupt interval (number of clock ticks)
uint32_t pit_getInterval(); //returns the interval that the interrupts are being fired at
void pit_interruptEnable(uint8_t enable); //enables the PIT interrupt if enable is true; disables it if false
void pit_startTimer(); //allows the timer to count down
void pit_pauseTimer(); //pauses the timer
void pit_timerReloadEnable(uint8_t enable); //if enable is true, allows the timer to restart after reaching 0. if false, stays at 0.







#endif /* PITDRIVER_H_ */
