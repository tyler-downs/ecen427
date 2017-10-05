/*
 * bunkers.c
 *
 *  Created on: Oct 4, 2017
 *      Author: superman
 */
#include "bunkers.h"

#define NUM_BUNKER_BLOCK_ROWS 3
#define NUM_BUNKER_BLOCK_COLS 4
//there are 3 rows and 4 columns of "bunker blocks".
//bunker 0 is leftmost, bunker 3 is rightmost
uint8_t bunker0state[NUM_BUNKER_BLOCK_ROWS][NUM_BUNKER_BLOCK_COLS] = { //initialized to 0 to indicate 0 damage
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0},
};

uint8_t bunker1state[NUM_BUNKER_BLOCK_ROWS][NUM_BUNKER_BLOCK_COLS] = { //initialized to 0 to indicate 0 damage
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0},
};

uint8_t bunker2state[NUM_BUNKER_BLOCK_ROWS][NUM_BUNKER_BLOCK_COLS] = { //initialized to 0 to indicate 0 damage
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0},
};

uint8_t bunker3state[NUM_BUNKER_BLOCK_ROWS][NUM_BUNKER_BLOCK_COLS] = { //initialized to 0 to indicate 0 damage
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0},
};

#define BUNKER_START_Y 340
#define BUNKER_SPACE 90 //space between individual bunkers, and bunkers and the edge of the screen
#define BUNKER_WIDTH 24
#define BUNKER_HEIGHT 18
#define BUNKER_FINAL_WIDTH (BUNKER_WIDTH * MAGNIFY_MULT)
#define NUM_BUNKERS 4

point_t getBunkerStartPoint(uint8_t bunker)
{
	return (point_t) {((bunker+1) * BUNKER_SPACE) + (bunker * BUNKER_FINAL_WIDTH), BUNKER_START_Y};
}


void drawBunkersInit()
{
	uint8_t n = 0;
	for (n = 0; n < NUM_BUNKERS; n++)
	{
		point_t bunkerStartPoint = getBunkerStartPoint(n);
		drawObject(bunker_24x18, BUNKER_WIDTH, BUNKER_HEIGHT, bunkerStartPoint, GREEN); //draw bunkers
	}
}

#define EROSION_ST_UNDAMAGED 0
#define EROSION_ST1 1
#define EROSION_ST2 2
#define EROSION_ST3 3
#define EROSION_ST_DESTROYED 4

#define BUNKER0 0
#define BUNKER1 1
#define BUNKER2 2
#define BUNKER3 3


//returns the erosion state of the bunker block at the specified bunker, row, and column
uint8_t getBunkerBlockState(uint8_t bunker, uint8_t row, uint8_t col)
{
	switch (bunker)
	{
	case BUNKER0:
		return bunker0state[row][col];
		break;
	case BUNKER1:
		return bunker1state[row][col];
		break;
	case BUNKER2:
		return bunker2state[row][col];
		break;
	case BUNKER3:
		return bunker3state[row][col];
		break;
	default:
		xil_printf("Tried to erode an invalid bunker block at bunker %d, row %d, col %d\n\r", bunker, row, col);
		return -1;
		break;
	}
}

void setBlockErosionState(uint8_t bunker, uint8_t row, uint8_t col, uint8_t state)
{
	if (state < 0 || state > 4) //valid states are 0-4
	{
		xil_printf("Tried to set erosion state to %d. Should be 0-4\n\r", state);
		return;
	}

	//xil_printf("  setting erosion state bunker: %d, row: %d, col: %d, state: %d\n\r", bunker, row, col, state);

	//update the specified bunker block
	switch (bunker)
	{
	case BUNKER0:
		bunker0state[row][col] = state;
		break;
	case BUNKER1:
		bunker1state[row][col] = state;
		break;
	case BUNKER2:
		bunker2state[row][col] = state;
		break;
	case BUNKER3:
		bunker3state[row][col] = state;
		break;
	default:
		xil_printf("Tried to set an invalid bunker block at bunker %d, row %d, col %d\n\r", bunker, row, col);
		break;
	}
}


#define BUNKER_BLOCK_WIDTH 6
#define BUNKER_BLOCK_HEIGHT 6
//erodes the specified bunker block by one level
void erodeBunkerBlock(uint8_t bunker, uint8_t row, uint8_t col)
{
	//xil_printf("  eroding bunker %d, row: %d, col: %d\n\r", bunker, row, col);
	point_t bunkerStartPoint = getBunkerStartPoint(bunker);
	int16_t blockX = bunkerStartPoint.x + (col*BUNKER_BLOCK_WIDTH*MAGNIFY_MULT);
	int16_t blockY = bunkerStartPoint.y + (row*BUNKER_BLOCK_HEIGHT*MAGNIFY_MULT);
	point_t blockStartPoint = {blockX, blockY};

	switch (getBunkerBlockState(bunker, row, col)) //get the current erosion state
	{
	case EROSION_ST_UNDAMAGED: //if not eroded yet
		drawObject(bunkerDamage1_6x6, BUNKER_BLOCK_WIDTH, BUNKER_BLOCK_HEIGHT, blockStartPoint, BLACK, LEAVE_BACKGROUND); //draw erosion 1 pattern
		setBlockErosionState(bunker, row, col, EROSION_ST1); //record new erosion state
		break;
	case 1: //if currently on damage level 1
		drawObject(bunkerDamage2_6x6, BUNKER_BLOCK_WIDTH, BUNKER_BLOCK_HEIGHT, blockStartPoint, BLACK, LEAVE_BACKGROUND); //draw erosion 2 pattern
		setBlockErosionState(bunker, row, col, EROSION_ST2); //record new erosion state
		break;
	case 2: //if currently on damage level 2
		drawObject(bunkerDamage3_6x6, BUNKER_BLOCK_WIDTH, BUNKER_BLOCK_HEIGHT, blockStartPoint, BLACK, LEAVE_BACKGROUND); //draw erosion 3 pattern
		setBlockErosionState(bunker, row, col, EROSION_ST3); //record new erosion state
		break;
	case 3: //if currently on damage level 3
		drawObject(bunkerDamage4_6x6, BUNKER_BLOCK_WIDTH, BUNKER_BLOCK_HEIGHT, blockStartPoint, BLACK, LEAVE_BACKGROUND); //draw erosion 4 pattern
		setBlockErosionState(bunker, row, col, EROSION_ST_DESTROYED); //record new erosion state
		break;
	default: //if invalid input
		xil_printf("Tried to erode destroyed block or invalid block number %d\n\r", bunker);
		break;
	}
}

//for test purposes only, erode an entire bunker at once
void erodeEntireBunker(uint8_t bunker)
{
	//xil_printf("  eroding bunker %d\n\r", bunker);
	uint8_t r, c;
	for (r = 0; r < NUM_BUNKER_BLOCK_ROWS; r++)
	{
		for (c = 0; c < NUM_BUNKER_BLOCK_COLS; c++)
		{
			erodeBunkerBlock(bunker, r, c);
		}
	}
}
