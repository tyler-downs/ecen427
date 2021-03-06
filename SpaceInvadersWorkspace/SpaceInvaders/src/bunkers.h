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
#include "render.h"

//Note: there are 10 "bunker blocks" in a bunker

///////////////////// DEFINES ///////////////////////
#define BUNKERS_NUM_BUNKER_BLOCK_ROWS 3 			//The number of rows in a bunker
#define BUNKERS_NUM_BUNKER_BLOCK_COLS 4				//The number of columns in a bunker
#define BUNKERS_BUNKER_START_Y 340					//The y coord for the top of the bunker
#define BUNKERS_BUNKER_SPACE 90 					//space between individual bunkers, and bunkers and the edge of the screen
#define BUNKERS_BUNKER_WIDTH 24						//Width of the bunkers
#define BUNKERS_BUNKER_HEIGHT 18					//Height of the bunkers
#define BUNKERS_BUNKER_FINAL_WIDTH (BUNKERS_BUNKER_WIDTH * GLOBALS_MAGNIFY_MULT) //The real bunker width, with the multiplier
#define BUNKERS_NUM_BUNKERS 4						//The number of bunkers in the game
#define BUNKERS_EROSION_ST_UNDAMAGED 0				//Index for erosion state undamaged
#define BUNKERS_EROSION_ST1 1						//Index for erosion state 1
#define BUNKERS_EROSION_ST2 2						//Index for erosion state 2
#define BUNKERS_EROSION_ST3 3						//Index for erosion state 3
#define BUNKERS_EROSION_ST_DESTROYED 4				//Index for erosion state 4 (destroyed)
#define BUNKERS_BUNKER0 0							//Index for bunker 0
#define BUNKERS_BUNKER1 1							//Index for bunker 1
#define BUNKERS_BUNKER2 2							//Index for bunker 2
#define BUNKERS_BUNKER3 3							//Index for bunker 3
#define BUNKERS_BUNKER_BLOCK_WIDTH 6				//Width of a bunker block
#define BUNKERS_BUNKER_BLOCK_HEIGHT 6				//Height of a bunker block


//////////////// FUNCTION PROTOTYPES /////////////////
void bunkers_drawBunkersInit(); //draw the initial bunkers

//returns the erosion state of the bunker block at the specified bunker, row, and column
uint8_t bunkers_getBunkerBlockState(uint8_t bunker, uint8_t row, uint8_t col);

//erodes the specified bunker block by one level
void bunkers_erodeBunkerBlock(uint8_t bunker, uint8_t row, uint8_t col);

//for test purposes only, erode an entire bunker at once
void bunkers_erodeEntireBunker(uint8_t bunker);

//returns a unique number for the bunker block that contains the pixel. -1 for error.
int8_t bunkers_getBunkerBlockNumber(point_t pixel);

//revives all the bunkers
void bunkers_reviveAllBunkers();

#endif /* BUNKERS_H_ */
