/*
 * bunkers.c
 *
 *  Created on: Oct 4, 2017
 *      Author: superman
 */
#include "bunkers.h"

#define NUM_BLOCKS_PER_BUNKER (BUNKERS_NUM_BUNKER_BLOCK_ROWS * BUNKERS_NUM_BUNKER_BLOCK_COLS) //the number of blocks in a bunker
#define NO_BUNKER -1 //indicates an error state in eroding bunkers
#define NO_BLOCK -1  //indicates an error state in eroding blocks
//there are 3 rows and 4 columns of "bunker blocks".
//bunker 0 is leftmost, bunker 3 is rightmost
uint8_t bunker0state[BUNKERS_NUM_BUNKER_BLOCK_ROWS][BUNKERS_NUM_BUNKER_BLOCK_COLS] = { //initialized to 0 to indicate 0 damage
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0},
};

uint8_t bunker1state[BUNKERS_NUM_BUNKER_BLOCK_ROWS][BUNKERS_NUM_BUNKER_BLOCK_COLS] = { //initialized to 0 to indicate 0 damage
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0},
};

uint8_t bunker2state[BUNKERS_NUM_BUNKER_BLOCK_ROWS][BUNKERS_NUM_BUNKER_BLOCK_COLS] = { //initialized to 0 to indicate 0 damage
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0},
};

uint8_t bunker3state[BUNKERS_NUM_BUNKER_BLOCK_ROWS][BUNKERS_NUM_BUNKER_BLOCK_COLS] = { //initialized to 0 to indicate 0 damage
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0},
};

//Returns the start location of a bunker given its bunker index.
point_t getBunkerStartPoint(uint8_t bunker)
{
	return (point_t) {((bunker+1) * BUNKERS_BUNKER_SPACE) + (bunker * BUNKERS_BUNKER_FINAL_WIDTH), BUNKERS_BUNKER_START_Y};
}

//Initially draws the bunkers.
void bunkers_drawBunkersInit()
{
	uint8_t n = 0;
	for (n = 0; n < BUNKERS_NUM_BUNKERS; n++) //iterate through the four bunkers
	{
		point_t bunkerStartPoint = getBunkerStartPoint(n); //get the start point
		render_drawObject(bunker_24x18, BUNKERS_BUNKER_WIDTH, BUNKERS_BUNKER_HEIGHT, bunkerStartPoint, GLOBALS_GREEN, GLOBALS_FORCE_BLACK_BACKGROUND); //draw bunkers
	}
}

//Returns the erosion state of the bunker block at the specified bunker, row, and column.
uint8_t bunkers_getBunkerBlockState(uint8_t bunker, uint8_t row, uint8_t col)
{
	switch (bunker)
	{
	case BUNKERS_BUNKER0:
		return bunker0state[row][col];		//Update bunker 0
		break;
	case BUNKERS_BUNKER1:
		return bunker1state[row][col];		//Update bunker 1
		break;
	case BUNKERS_BUNKER2:
		return bunker2state[row][col];		//Update bunker 2
		break;
	case BUNKERS_BUNKER3:
		return bunker3state[row][col];		//Update bunker 3
		break;
	default:
		xil_printf("Tried to erode an invalid bunker block at bunker %d, row %d, col %d\n\r", bunker, row, col);
		return GLOBALS_ERROR_INDEX;
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
	case BUNKERS_BUNKER0:
		bunker0state[row][col] = state; 	//Update bunker 0
		break;
	case BUNKERS_BUNKER1:
		bunker1state[row][col] = state;		//Update bunker 1
		break;
	case BUNKERS_BUNKER2:
		bunker2state[row][col] = state;		//Update bunker 2
		break;
	case BUNKERS_BUNKER3:
		bunker3state[row][col] = state;		//Update bunker 3
		break;
	default:
		xil_printf("Tried to set an invalid bunker block at bunker %d, row %d, col %d\n\r", bunker, row, col);
		break;
	}
}

//revives all the bunkers
void bunkers_reviveAllBunkers()
{
	//loop through the bunkers and each row and columns of blocks in each bunker
	uint8_t i, r, c;
	for (i = 0; i < BUNKERS_NUM_BUNKERS; i++)
	{
		for (r = 0; r < BUNKERS_NUM_BUNKER_BLOCK_ROWS; r++)
		{
			for (c = 0; c < BUNKERS_NUM_BUNKER_BLOCK_COLS; c++)
			{
				setBlockErosionState(i, r, c, BUNKERS_EROSION_ST_UNDAMAGED);
			}
		}
	}
}

//Returns the start point of a bunker block so it can be eroded
point_t getBlockStartPoint(point_t bunkerStartPoint, uint8_t row, uint8_t col)
{
	int16_t blockX = bunkerStartPoint.x + (col*BUNKERS_BUNKER_BLOCK_WIDTH*GLOBALS_MAGNIFY_MULT);
	int16_t blockY = bunkerStartPoint.y + (row*BUNKERS_BUNKER_BLOCK_HEIGHT*GLOBALS_MAGNIFY_MULT);
	return (point_t) {blockX, blockY};
}

//Erodes the specified bunker block by one level.
void bunkers_erodeBunkerBlock(uint8_t bunker, uint8_t row, uint8_t col)
{
	point_t bunkerStartPoint = getBunkerStartPoint(bunker);
	point_t blockStartPoint = getBlockStartPoint(bunkerStartPoint, row, col);

	switch (bunkers_getBunkerBlockState(bunker, row, col)) //get the current erosion state
	{
	case BUNKERS_EROSION_ST_UNDAMAGED: //if not eroded yet
		render_drawObject(bunkerDamage1_6x6, BUNKERS_BUNKER_BLOCK_WIDTH, BUNKERS_BUNKER_BLOCK_HEIGHT, blockStartPoint, GLOBALS_BLACK, GLOBALS_LEAVE_BACKGROUND); //draw erosion 1 pattern
		setBlockErosionState(bunker, row, col, BUNKERS_EROSION_ST1); //record new erosion state
		break;
	case 1: //if currently on damage level 1
		render_drawObject(bunkerDamage2_6x6, BUNKERS_BUNKER_BLOCK_WIDTH, BUNKERS_BUNKER_BLOCK_HEIGHT, blockStartPoint, GLOBALS_BLACK, GLOBALS_LEAVE_BACKGROUND); //draw erosion 2 pattern
		setBlockErosionState(bunker, row, col, BUNKERS_EROSION_ST2); //record new erosion state
		break;
	case 2: //if currently on damage level 2
		render_drawObject(bunkerDamage3_6x6, BUNKERS_BUNKER_BLOCK_WIDTH, BUNKERS_BUNKER_BLOCK_HEIGHT, blockStartPoint, GLOBALS_BLACK, GLOBALS_LEAVE_BACKGROUND); //draw erosion 3 pattern
		setBlockErosionState(bunker, row, col, BUNKERS_EROSION_ST3); //record new erosion state
		break;
	case 3: //if currently on damage level 3
		render_drawObject(bunkerDamage4_6x6, BUNKERS_BUNKER_BLOCK_WIDTH, BUNKERS_BUNKER_BLOCK_HEIGHT, blockStartPoint, GLOBALS_BLACK, GLOBALS_LEAVE_BACKGROUND); //draw erosion 4 pattern
		setBlockErosionState(bunker, row, col, BUNKERS_EROSION_ST_DESTROYED); //record new erosion state
		break;
	default: //if invalid input
		xil_printf("Tried to erode destroyed block or invalid block number %d\n\r", bunker);
		break;
	}
}

//erodes the specified bunker block by one level
void erodeBunkerBlockByNum(uint8_t blockNum)
{
	uint8_t bunker, blockWithinBunker, row, col;
	bunker = blockNum / NUM_BLOCKS_PER_BUNKER; //calculate bunker
	blockWithinBunker = blockNum % (NUM_BLOCKS_PER_BUNKER); //the block number (0-11) within the bunker
	row = (blockWithinBunker / BUNKERS_NUM_BUNKER_BLOCK_COLS); //calculate the row number
	col = blockWithinBunker % BUNKERS_NUM_BUNKER_BLOCK_COLS; //calculate the column number
	bunkers_erodeBunkerBlock(bunker, row, col); //erode the bunker block
}

//For test purposes only, erode an entire bunker at once
void bunkers_erodeEntireBunker(uint8_t bunker)
{
	uint8_t r, c;
	for (r = 0; r < BUNKERS_NUM_BUNKER_BLOCK_ROWS; r++) //loop through each row
	{
		for (c = 0; c < BUNKERS_NUM_BUNKER_BLOCK_COLS; c++) //loop through each col
		{
			bunkers_erodeBunkerBlock(bunker, r, c); //erode the block at the position
		}
	}
}

//returns the bunker number that contains this pixel. -1 if none
int8_t getBunkerNumber(point_t pixel)
{
	uint8_t b;
	for (b = 0; b < BUNKERS_NUM_BUNKERS; b++)
	{
		point_t bunkerPoint = getBunkerStartPoint(b);
		if (pixel.x >= bunkerPoint.x && pixel.x <= (bunkerPoint.x + BUNKERS_BUNKER_WIDTH*GLOBALS_MAGNIFY_MULT) &&
			pixel.y >= bunkerPoint.y && pixel.y <= (bunkerPoint.y + BUNKERS_BUNKER_HEIGHT*GLOBALS_MAGNIFY_MULT)	) //if the pixel is within this bunker
		{
			return b;
		}
	}
	//xil_printf("Bunker collision error!\n\r"); //shouldn't happen
	return NO_BUNKER; //shouldn't happen
}

//returns a unique number for the bunker block that contains the pixel
int8_t bunkers_getBunkerBlockNumber(point_t pixel)
{
	int8_t bunker = getBunkerNumber(pixel);
	uint8_t r, c;
	for (r = 0; r < BUNKERS_NUM_BUNKER_BLOCK_ROWS; r++)
	{
		for (c = 0; c < BUNKERS_NUM_BUNKER_BLOCK_COLS; c++)
		{
			point_t blockStartPoint = getBlockStartPoint(getBunkerStartPoint(bunker), r, c);
			if (pixel.x >= blockStartPoint.x && pixel.x <= (blockStartPoint.x + BUNKERS_BUNKER_BLOCK_WIDTH*GLOBALS_MAGNIFY_MULT) &&
				pixel.y >= blockStartPoint.y && pixel.y <= (blockStartPoint.y + BUNKERS_BUNKER_BLOCK_HEIGHT*GLOBALS_MAGNIFY_MULT)) //if the pixel is within this block
			{
				return (bunker * NUM_BLOCKS_PER_BUNKER) + (r * BUNKERS_NUM_BUNKER_BLOCK_COLS) + c; //returns a block ID
			}
		}
	}
	//xil_printf("Block collision error!\n\r"); //shouldn't happen
	return NO_BLOCK;//shouldn't happen
}
