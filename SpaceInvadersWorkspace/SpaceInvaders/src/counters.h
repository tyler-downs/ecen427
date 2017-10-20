/*
 * counters.h
 *
 *  Created on: Oct 13, 2017
 *      Author: superman
 */

#ifndef COUNTERS_H_
#define COUNTERS_H_

#include "globals.h"
#include "render.h"
#include "bullets.h"

//updates all of the gameplay counters
void counters_updateAllCounters();

//Sets the global game over state to true
void counters_setGameOverState();

#endif /* COUNTERS_H_ */
