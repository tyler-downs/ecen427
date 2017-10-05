/*
 * bunkers.h
 *
 *  Created on: Oct 4, 2017
 *      Author: superman
 */

#ifndef BUNKERS_H_
#define BUNKERS_H_

#include "bitmaps.h"
#include "globals.h"

void drawBunkersInit(); //draw the initial bunkers

//returns the erosion state of the bunker block at the specified bunker, row, and column
uint8_t getBunkerBlockState(uint8_t bunker, uint8_t row, uint8_t col);

//erodes the specified bunker block by one level
void erodeBunkerBlock(uint8_t bunker, uint8_t row, uint8_t col);

//for test purposes only, erode an entire bunker at once
void erodeEntireBunker(uint8_t bunker);

#endif /* BUNKERS_H_ */
