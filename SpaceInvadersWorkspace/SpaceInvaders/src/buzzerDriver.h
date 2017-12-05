/*
 * buzzerDriver.h
 *
 *  Created on: Nov 27, 2017
 *      Author: superman
 */

#ifndef BUZZERDRIVER_H_
#define BUZZERDRIVER_H_

#include <stdint.h>

void buzzerInit(); //initialize the buzzer
void buzzer_setDelay(uint32_t buzzTime); //set how long the next buzz will be
void buzzer_buzz(); //start buzzing
void buzzer_disableBuzz(); //This isn't necessary unless you want to stop a buzz short


#endif /* BUZZERDRIVER_H_ */