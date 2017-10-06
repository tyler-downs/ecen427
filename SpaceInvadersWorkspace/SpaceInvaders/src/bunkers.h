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

//Note: there are 10 "bunker blocks" in a bunker

///////////////////// DEFINES ///////////////////////
#define NUM_BUNKER_BLOCK_ROWS 3 			//The number of rows in a bunker
#define NUM_BUNKER_BLOCK_COLS 4				//The number of columns in a bunker
#define BUNKER_START_Y 340					//The y coord for the top of the bunker
#define BUNKER_SPACE 90 					//space between individual bunkers, and bunkers and the edge of the screen
#define BUNKER_WIDTH 24						//Width of the bunkers
#define BUNKER_HEIGHT 18					//Height of the bunkers
#define BUNKER_FINAL_WIDTH (BUNKER_WIDTH * MAGNIFY_MULT) //The real bunker width, with the multiplier
#define NUM_BUNKERS 4						//The number of bunkers in the game
#define EROSION_ST_UNDAMAGED 0				//Index for erosion state undamaged
#define EROSION_ST1 1						//Index for erosion state 1
#define EROSION_ST2 2						//Index for erosion state 2
#define EROSION_ST3 3						//Index for erosion state 3
#define EROSION_ST_DESTROYED 4				//Index for erosion state 4 (destroyed)
#define BUNKER0 0							//Index for bunker 0
#define BUNKER1 1							//Index for bunker 1
#define BUNKER2 2							//Index for bunker 2
#define BUNKER3 3							//Index for bunker 3
#define BUNKER_BLOCK_WIDTH 6				//Width of a bunker block
#define BUNKER_BLOCK_HEIGHT 6				//Height of a bunker block


//////////////// FUNCTION PROTOTYPES /////////////////
void drawBunkersInit(); //draw the initial bunkers

//returns the erosion state of the bunker block at the specified bunker, row, and column
uint8_t getBunkerBlockState(uint8_t bunker, uint8_t row, uint8_t col);

//erodes the specified bunker block by one level
void erodeBunkerBlock(uint8_t bunker, uint8_t row, uint8_t col);

//for test purposes only, erode an entire bunker at once
void erodeEntireBunker(uint8_t bunker);

#endif /* BUNKERS_H_ */
