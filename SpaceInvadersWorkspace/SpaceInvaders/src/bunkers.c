/*
 * bunkers.c
 *
 *  Created on: Oct 4, 2017
 *      Author: superman
 */
#include "bunkers.h"


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

//Returns the start location of a bunker given its bunker index.
point_t getBunkerStartPoint(uint8_t bunker)
{
	return (point_t) {((bunker+1) * BUNKER_SPACE) + (bunker * BUNKER_FINAL_WIDTH), BUNKER_START_Y};
}

//Initially draws the bunkers.
void drawBunkersInit()
{
	uint8_t n = 0;
	for (n = 0; n < NUM_BUNKERS; n++) //iterate through the four bunkers
	{
		point_t bunkerStartPoint = getBunkerStartPoint(n); //get the start point
		drawObject(bunker_24x18, BUNKER_WIDTH, BUNKER_HEIGHT, bunkerStartPoint, GREEN); //draw bunkers
	}
}

//Returns the erosion state of the bunker block at the specified bunker, row, and column.
uint8_t getBunkerBlockState(uint8_t bunker, uint8_t row, uint8_t col)
{
	switch (bunker)
	{
	case BUNKER0:
		return bunker0state[row][col];		//Update bunker 0
		break;
	case BUNKER1:
		return bunker1state[row][col];		//Update bunker 1
		break;
	case BUNKER2:
		return bunker2state[row][col];		//Update bunker 2
		break;
	case BUNKER3:
		return bunker3state[row][col];		//Update bunker 3
		break;
	default:
		xil_printf("Tried to erode an invalid bunker block at bunker %d, row %d, col %d\n\r", bunker, row, col);
		return ERROR_INDEX;
		break;
	}
}

//Set the erosion state of a bunker block given which bunker it's in, row, col, and state.
void setBlockErosionState(uint8_t bunker, uint8_t row, uint8_t col, uint8_t state)
{
	if ((state < 0) || (state > 4)) //valid states are 0-4
	{
		xil_printf("Tried to set erosion state to %d. Should be 0-4\n\r", state);
		return;
	}
	//update the specified bunker block
	switch (bunker)
	{
	case BUNKER0:
		bunker0state[row][col] = state; 	//Update bunker 0
		break;
	case BUNKER1:
		bunker1state[row][col] = state;		//Update bunker 1
		break;
	case BUNKER2:
		bunker2state[row][col] = state;		//Update bunker 2
		break;
	case BUNKER3:
		bunker3state[row][col] = state;		//Update bunker 3
		break;
	default:
		xil_printf("Tried to set an invalid bunker block at bunker %d, row %d, col %d\n\r", bunker, row, col);
		break;
	}
}



//Erodes the specified bunker block by one level.
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

//For test purposes only, erode an entire bunker at once
void erodeEntireBunker(uint8_t bunker)
{
	uint8_t r, c;
	for (r = 0; r < NUM_BUNKER_BLOCK_ROWS; r++)
	{
		for (c = 0; c < NUM_BUNKER_BLOCK_COLS; c++)
		{
			erodeBunkerBlock(bunker, r, c);
		}
	}
}
