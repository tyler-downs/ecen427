#include "aliens.h"
/*
 * aliens.c
 *
 *  Created on: Oct 3, 2017
 *      Author: superman
 */


//////////// GLOBAL VARIABLES AND ENUMS //////////////////
static point_t aliens_alienBlockPosition; //globally excessible variable
static point_t aliens_oldAlienBlockPosition; //globally accessible variable used for erasing alien at old location
static uint8_t aliens_movedDownRow = FALSE; //flag which indicates when the alien block has just moved down a row
static alien_guise_type aliens_currentAlienGuise = alien_guise_out; //initialize alien guise to out
static alien_direction_type aliens_currentAlienDirection = aliens_move_right; //initialize alien crawl direction to right
static uint8_t aliens_numAliensAlive = GLOBALS_NUM_ALIEN_COLUMNS * GLOBALS_NUM_ALIEN_ROWS;	//number of aliens alive. Decrements when an alien is killed.

//Returns the number of aliens that are alive
uint8_t aliens_getNumAliensAlive()
{
	return aliens_numAliensAlive;
}

//Decrements the global numAliensAlive (use when an alien is killed)
void aliens_decrementNumAliensAlive()
{
	aliens_numAliensAlive--;
	if (aliens_numAliensAlive == 0) //if there are no more aliens alive
	{
		globals_levelCleared(); //you won the level
	}
}

//Sets the number of aliens alive to the given value
void aliens_setNumAliensAlive(uint8_t number)
{
	aliens_numAliensAlive = number;
}

//Array for aliens currently alive (row, column)
static uint8_t aliens_aliensAlive[GLOBALS_NUM_ALIEN_ROWS][GLOBALS_NUM_ALIEN_COLUMNS] = \
		{{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

//Given a row and column, accesses aliensAlive array and returns whether
//corresponding alien is alive or not
uint8_t aliens_isAlienAlive(uint8_t row, uint8_t col)
{
	return aliens_aliensAlive[row][col];
}

//Switches the current guise of the aliens
void aliens_switchAlienGuises()
{
	if (aliens_currentAlienGuise == alien_guise_out)
	{
		aliens_currentAlienGuise = alien_guise_in;
	}
	else //if current alien guise is in
	{
		aliens_currentAlienGuise = alien_guise_out;
	}
}

//Given a row and column index, returns the location of the corresponding alien on the screen
point_t aliens_getOneAlienLocation(uint8_t row, uint8_t col)
{
	int16_t x = aliens_getAlienBlockPosition().x + (GLOBALS_ALIEN_WIDTH * GLOBALS_MAGNIFY_MULT * col) + (GLOBALS_ALIEN_SPACE_HORIZ * col); //set this alien's start x
	int16_t y = aliens_getAlienBlockPosition().y + (GLOBALS_ALIEN_HEIGHT * GLOBALS_MAGNIFY_MULT * row) + (GLOBALS_ALIEN_SPACE_VERT * row); //set this alien's start y
	point_t alienLocation = {x, y}; //create the point_t variable to use in draw Object for this alien
	return alienLocation;
}

//Given a row and column index, erases the corresponding alien completely (draws it black)
void aliens_eraseOneAlien(uint8_t row, uint8_t col)
{
	//get the alien's location
	point_t alienLocation = aliens_getOneAlienLocation(row, col);
	//check to see which guise the alien is so we erase just the right stuff
	if (aliens_currentAlienGuise == alien_guise_out)
	{
		if (row < GLOBALS_NUM_TOP_ALIEN_ROWS) //if we're drawing a top alien
			render_drawObject(alien_top_out_12x8, GLOBALS_ALIEN_WIDTH, GLOBALS_ALIEN_HEIGHT, alienLocation, GLOBALS_BLACK, GLOBALS_FORCE_BLACK_BACKGROUND); //draw top alien
		else if(row < GLOBALS_NUM_TOP_ALIEN_ROWS + GLOBALS_NUM_MIDDLE_ALIEN_ROWS) //if we're drawing a middle alien
			render_drawObject(alien_middle_out_12x8, GLOBALS_ALIEN_WIDTH, GLOBALS_ALIEN_HEIGHT, alienLocation, GLOBALS_BLACK, GLOBALS_FORCE_BLACK_BACKGROUND); //draw middle alien
		else // we must be drawing a bottom alien
			render_drawObject(alien_bottom_out_12x8, GLOBALS_ALIEN_WIDTH, GLOBALS_ALIEN_HEIGHT, alienLocation, GLOBALS_BLACK, GLOBALS_FORCE_BLACK_BACKGROUND); //draw bottom alien
	}
	else //current alien guise is alien guise in
	{
		if (row < GLOBALS_NUM_TOP_ALIEN_ROWS) //if we're drawing a top alien
			render_drawObject(alien_top_in_12x8, GLOBALS_ALIEN_WIDTH, GLOBALS_ALIEN_HEIGHT, alienLocation, GLOBALS_BLACK, GLOBALS_FORCE_BLACK_BACKGROUND); //draw top alien
		else if(row < GLOBALS_NUM_TOP_ALIEN_ROWS + GLOBALS_NUM_MIDDLE_ALIEN_ROWS) //if we're drawing a middle alien
			render_drawObject(alien_middle_in_12x8, GLOBALS_ALIEN_WIDTH, GLOBALS_ALIEN_HEIGHT, alienLocation, GLOBALS_BLACK, GLOBALS_FORCE_BLACK_BACKGROUND); //draw middle alien
		else // we must be drawing a bottom alien
			render_drawObject(alien_bottom_in_12x8, GLOBALS_ALIEN_WIDTH, GLOBALS_ALIEN_HEIGHT, alienLocation, GLOBALS_BLACK, GLOBALS_FORCE_BLACK_BACKGROUND); //draw bottom alien
	}
}


//Erases all aliens from the screen. Does not kill them. Used for debugging.
void aliens_eraseAllAliens()
{
	//just draw all of the aliens I just drew but in black
	//iterate through the rows and columns
	uint8_t r = 0, c = 0;
	for (r = 0; r < GLOBALS_NUM_ALIEN_ROWS; r++) //alien rows
	{
		for (c = 0; c < GLOBALS_NUM_ALIEN_COLUMNS; c++) //alien column
		{
			if (aliens_aliensAlive[r][c]) //if the alien at this position is alive
			{
				//erase the current alien
				aliens_eraseOneAlien(r, c);
			}
		}
	}
}

//Draws the alien at a given row and column. Finds its location and draws in white.
void aliens_drawOneAlien(uint8_t row, uint8_t col)
{
	//get the alien's location
	point_t alienLocation = aliens_getOneAlienLocation(row, col);
	//check to see which guise the alien is so we erase just the right stuff
	if (aliens_currentAlienGuise == alien_guise_out)
	{
		if (row < GLOBALS_NUM_TOP_ALIEN_ROWS) //if we're drawing a top alien
			render_drawObject(alien_top_out_12x8, GLOBALS_ALIEN_WIDTH, GLOBALS_ALIEN_HEIGHT, alienLocation, GLOBALS_WHITE, GLOBALS_FORCE_BLACK_BACKGROUND); //draw top alien
		else if(row < GLOBALS_NUM_TOP_ALIEN_ROWS + GLOBALS_NUM_MIDDLE_ALIEN_ROWS) //if we're drawing a middle alien
			render_drawObject(alien_middle_out_12x8, GLOBALS_ALIEN_WIDTH, GLOBALS_ALIEN_HEIGHT, alienLocation, GLOBALS_WHITE, GLOBALS_FORCE_BLACK_BACKGROUND); //draw middle alien
		else // we must be drawing a bottom alien
			render_drawObject(alien_bottom_out_12x8, GLOBALS_ALIEN_WIDTH, GLOBALS_ALIEN_HEIGHT, alienLocation, GLOBALS_WHITE, GLOBALS_FORCE_BLACK_BACKGROUND); //draw bottom alien
	}
	else //current alien guise is alien guise in
	{
		if (row < GLOBALS_NUM_TOP_ALIEN_ROWS) //if we're drawing a top alien
			render_drawObject(alien_top_in_12x8, GLOBALS_ALIEN_WIDTH, GLOBALS_ALIEN_HEIGHT, alienLocation, GLOBALS_WHITE, GLOBALS_FORCE_BLACK_BACKGROUND); //draw top alien
		else if(row < GLOBALS_NUM_TOP_ALIEN_ROWS + GLOBALS_NUM_MIDDLE_ALIEN_ROWS) //if we're drawing a middle alien
			render_drawObject(alien_middle_in_12x8, GLOBALS_ALIEN_WIDTH, GLOBALS_ALIEN_HEIGHT, alienLocation, GLOBALS_WHITE, GLOBALS_FORCE_BLACK_BACKGROUND); //draw middle alien
		else // we must be drawing a bottom alien
			render_drawObject(alien_bottom_in_12x8, GLOBALS_ALIEN_WIDTH, GLOBALS_ALIEN_HEIGHT, alienLocation, GLOBALS_WHITE, GLOBALS_FORCE_BLACK_BACKGROUND); //draw bottom alien
	}
}

//Draws all (living) aliens to the screen.
void aliens_drawAllAliens()
{
	//iterate through the rows and columns
	uint8_t r = 0, c = 0;
	for (r = 0; r < GLOBALS_NUM_ALIEN_ROWS; r++) //alien rows
	{
		for (c = 0; c < GLOBALS_NUM_ALIEN_COLUMNS; c++) //alien column
		{
			if (aliens_aliensAlive[r][c]) //if the alien at this position is alive
			{
				//erase the current alien
				aliens_drawOneAlien(r, c);
			}
		}
	}
}

//Changes the direction variable for the aliens
void aliens_switchAlienDirection()
{
	//if the current direction is right, assign it to left
	if (aliens_currentAlienDirection == aliens_move_right)
	{
		aliens_currentAlienDirection = aliens_move_left;
	}
	//if the current direction is left, assign it to right
	else
	{
		aliens_currentAlienDirection = aliens_move_right;
	}
}

int8_t aliens_lowestLivingRow()
{
	int8_t r, c;
	for (r = GLOBALS_NUM_ALIEN_ROWS-1; r >= 0; r++) //go through each row, starting from the bottom
	{
		for (c = 0; c < GLOBALS_NUM_ALIEN_COLUMNS; c++) //go through each column
		{
			if (aliens_isAlienAlive(r, c)) //if there's a living alien, return the row number
			{
				return r;
			}
		}
	}
	xil_printf("Error: no living aliens\n\r"); //shouldn't ever happen
	return -1;
}

//Returns the y-coord of the bottom of the living alien block
int16_t aliens_getBottomOfAliens()
{
	return (aliens_getAlienBlockPosition().y + (GLOBALS_ALIEN_HEIGHT + GLOBALS_ALIEN_SPACE_VERT) * (aliens_lowestLivingRow() + 1));
}

//if an alien is drawn at this point or below (the top of the alien), they win
#define BOTTOM_Y (BUNKERS_BUNKER_START_Y + (BUNKERS_BUNKER_BLOCK_HEIGHT * GLOBALS_MAGNIFY_MULT * 2)) //this would put the alien level with the bottom block of the bunker
uint8_t aliens_reachedBottom() //returns true if the aliens have reached the bottom of the bunkers
{
	int16_t lowestAlienPos = aliens_getOneAlienLocation(aliens_lowestLivingRow(), 0).y; //get the y coordinate of the lowest living row of aliens
	return (lowestAlienPos >= BOTTOM_Y); //returns true if the aliens have reached the bottom
}

//Facilitates moving the aliens down one row
void aliens_moveDownOneRow()
{
	//erase the whole aliens
	aliens_eraseAllAliens();
	//move the start line down one row
	point_t newAlienBlockPosition = {aliens_getAlienBlockPosition().x, \
			aliens_getAlienBlockPosition().y + (GLOBALS_ALIEN_HEIGHT * GLOBALS_MAGNIFY_MULT)};
	aliens_setAlienBlockPosition(newAlienBlockPosition);
	//draw all of the aliens
	aliens_drawAllAliens();
	//switch the direction of the aliens
	aliens_switchAlienDirection();
	//set row switch flag to true
	aliens_movedDownRow = TRUE;

	if (aliens_reachedBottom())//check if we've reached the bottom. If so, GAME OVER!
		globals_gameOver();
}

//Returns the index of the rightmost column that has aliens still in it.
//Columns are indexed 0-10. There are 11 columns in total
int8_t aliens_getRightmostLivingAlienColumn()
{
	int8_t row = 0, col = GLOBALS_MAX_ALIEN_COL_INDEX;
	while (col >= 0)
	{
		row = 0;
		while (row <= GLOBALS_MAX_ALIEN_ROW_INDEX)
		{
			if (aliens_aliensAlive[row][col])
			{
				return col;
			}
			row++;
		}
		col--;
	}
	return GLOBALS_ERROR_INDEX;
}

//Returns the leftmost living column of aliens
int8_t aliens_getLeftmostLivingAlienColumn()
{
	int8_t row = 0, col = 0;
	while (col <= GLOBALS_MAX_ALIEN_COL_INDEX) //iterate through columns
	{
		row = 0;
		while (row <= GLOBALS_MAX_ALIEN_ROW_INDEX) //iterate through rows
		{
			//if any alien in this column is alive, return the column index
			if (aliens_aliensAlive[row][col])
			{
				return col;
			}
			row++; //increment the row index
		}
		col++; //increment the col index
	}
	//return -1 if there are no living alien columns (edge case)
	return GLOBALS_ERROR_INDEX;
}



//Returns the x coordinate of the right edge of the alien block
uint16_t aliens_getRightEdgeOfAlienBlock()
{
	//check to see what the rightmost column of aliens is
	uint8_t rightmostLivingAlienColumn = aliens_getRightmostLivingAlienColumn();
	uint16_t r = aliens_getAlienBlockPosition().x \
			+ (GLOBALS_ALIEN_WIDTH * GLOBALS_MAGNIFY_MULT * (rightmostLivingAlienColumn+1)) \
			+ (GLOBALS_ALIEN_SPACE_HORIZ * (rightmostLivingAlienColumn));
	return r;
}


//Returns the value that must be added to the alien block position so it can
//make it all the way to the left edge of the screen.
int16_t aliens_getLeftmostLivingAlienColumnAdjustment()
{
	return (aliens_getLeftmostLivingAlienColumn() * (GLOBALS_ALIEN_WIDTH  + GLOBALS_ALIEN_SPACE_HORIZ + GLOBALS_NUM_ALIEN_COLUMNS));
}

//Updates the block position of aliens depending on current location.
//Called in moveAliens()
void aliens_updateAlienBlockPosition()
{
	//check the bounds
	if (aliens_currentAlienDirection == aliens_move_right)
	{
		//if the right edge of the alien block is at the edge of the screen minus a bit
		if (aliens_getRightEdgeOfAlienBlock() >= (GLOBALS_WIDTH_DISPLAY - ALIENS_SCREEN_EDGE_BUMPER_PIXELS))
		{
			aliens_moveDownOneRow();
		}
		else
		{
			//update the alien's position
			aliens_oldAlienBlockPosition = aliens_getAlienBlockPosition();
			point_t newAlienBlockPosition = {(aliens_getAlienBlockPosition().x + ALIENS_MOVE_PIXELS), aliens_getAlienBlockPosition().y};
			aliens_setAlienBlockPosition(newAlienBlockPosition);
		}
	}
	else //if aliens are moving left
	{
		//if the left end of the alien block is too close to the left edge of the screen
		if ( (aliens_getAlienBlockPosition().x + aliens_getLeftmostLivingAlienColumnAdjustment()) <= ALIENS_SCREEN_EDGE_BUMPER_PIXELS)
		{
			aliens_moveDownOneRow();
		}
		else
		{
			//update the alien's position
			aliens_oldAlienBlockPosition = aliens_getAlienBlockPosition();
			point_t newAlienBlockPosition = {(aliens_getAlienBlockPosition().x - ALIENS_MOVE_PIXELS), aliens_getAlienBlockPosition().y};
			aliens_setAlienBlockPosition(newAlienBlockPosition);
		}
	}
}

//Erases the half of the alien that needs to be erased when moving the alien over.
//Takes in the row and column index of the alien and finds position based on that current alien block position.
void aliens_eraseAlienRectangle(uint8_t r, uint8_t c)
{
	uint16_t xOld = aliens_oldAlienBlockPosition.x + (GLOBALS_ALIEN_WIDTH * GLOBALS_MAGNIFY_MULT * c) + (GLOBALS_ALIEN_SPACE_HORIZ * c); //set this alien's start x
	uint16_t yOld = aliens_oldAlienBlockPosition.y + (GLOBALS_ALIEN_HEIGHT * GLOBALS_MAGNIFY_MULT * r) + (GLOBALS_ALIEN_SPACE_VERT * r); //set this alien's start y
	if (aliens_currentAlienDirection == aliens_move_right)
	{
		render_eraseRectangle((point_t){xOld, yOld}, ALIENS_MOVE_PIXELS, GLOBALS_ALIEN_HEIGHT);
	}
	else //if you're moving left
	{
		render_eraseRectangle((point_t){(xOld + GLOBALS_ALIEN_WIDTH), yOld}, ALIENS_MOVE_PIXELS, GLOBALS_ALIEN_HEIGHT);
	}
}

//Moves all living aliens one step. Handles moving down rows, switching directions, etc.
void aliens_moveAliens()
{
	//switch alien guise
	aliens_switchAlienGuises();
	//update the alien positions
	aliens_updateAlienBlockPosition();
	if (!aliens_movedDownRow)
	{
		uint8_t r = 0, c = 0;
		for (r = 0; r < GLOBALS_NUM_ALIEN_ROWS; r++) //alien rows
		{
			for (c = 0; c < GLOBALS_NUM_ALIEN_COLUMNS; c++) //alien column
			{
				if (aliens_aliensAlive[r][c]) //if the alien at this position is alive
				{
					//erase the rectangle for the aliens
					aliens_eraseAlienRectangle(r, c);
					//draw the current alien
					aliens_drawOneAlien(r, c);
				}
			}
		}
	}
	aliens_movedDownRow = FALSE; //reset this so the aliens can move later
}

//Given the alien index passed in (0-54), returns the row in which this alien is located
uint8_t aliens_getRowFromAlienNumber(uint8_t num)
{
	int c = 0; //this is our counter
	while (num > GLOBALS_MAX_ALIEN_COL_INDEX) //Exits when you get a number between 0 and 10
	{
		num -= GLOBALS_NUM_ALIEN_COLUMNS; //decrement num by 11
		c++; //increment c
	}
	return c;
}

//Given the alien index passed in, returns the column in which this alien is located
uint8_t aliens_getColumnFromAlienNumber(uint8_t num)
{
	while (num > GLOBALS_MAX_ALIEN_COL_INDEX) //exits when you get a number between 0 and 10
		num -= GLOBALS_NUM_ALIEN_COLUMNS; //decrement num by 11
	return num;
}

//returns true if all the aliens are dead
uint8_t aliens_allAliensDead()
{
	uint8_t r, c;
	for (r = 0; r < GLOBALS_NUM_ALIEN_COLUMNS; r++)
	{
		for (c = 0; c < GLOBALS_NUM_ALIEN_ROWS; c++)
		{
			if (aliens_isAlienAlive(r, c)) //if there is an alien alive
				return FALSE;
		}
	}
	return TRUE; //if all aliens are dead
}

//Given a number between 0-54, kills the corresponding alien
void aliens_killAlien(uint8_t alien)
{
	//map this number alien to a row/column
	uint8_t row = aliens_getRowFromAlienNumber(alien);
	uint8_t col = aliens_getColumnFromAlienNumber(alien);

	//erase this alien
	aliens_eraseOneAlien(row, col);

	//kill this alien
	aliens_aliensAlive[row][col] = 0;

	//decrement the global
	aliens_decrementNumAliensAlive();

	if (aliens_allAliensDead()) //if all the aliens are now dead
		globals_levelCleared(); //you won the level!
}

//returns the location of the alien
point_t aliens_getAlienLocation(uint8_t alienNum)
{
	uint8_t row, col;
	row = aliens_getRowFromAlienNumber(alienNum);
	col = aliens_getColumnFromAlienNumber(alienNum);
	return aliens_getOneAlienLocation(row, col);
}

//Sets the global for alien block position
void aliens_setAlienBlockPosition(point_t val)
{
	aliens_alienBlockPosition = val;
}

//Returns the global for alien block position
point_t aliens_getAlienBlockPosition()
{
	return aliens_alienBlockPosition;
}

//returns the alien number at the given row and column index
uint8_t aliens_getAlienNumberFromRowCol(uint8_t row, uint8_t col)
{
	return (row * GLOBALS_NUM_ALIEN_COLUMNS) + col;
}

//returns the alien number that has a pixel at the provided point
uint8_t aliens_getAlienNumberFromPoint(point_t point)
{
	uint8_t r, c;
	for (r = 0; r < GLOBALS_NUM_ALIEN_ROWS; r++)
	{
		for (c = 0; c < GLOBALS_NUM_ALIEN_COLUMNS; c++)
		{
			point_t alienPos = aliens_getOneAlienLocation(r, c); //get the position of the alien
			if (point.x >= alienPos.x && point.x <= (alienPos.x + GLOBALS_ALIEN_WIDTH*GLOBALS_MAGNIFY_MULT) &&
				point.y >= alienPos.y && point.y <= (alienPos.y + GLOBALS_ALIEN_HEIGHT*GLOBALS_MAGNIFY_MULT)	) //if the point is in this alien
			{
				return aliens_getAlienNumberFromRowCol(r, c); //return the alien number
			}

		}
	}
	xil_printf("Alien number from point error!\n\r"); //shouldn't happen
}

//returns how many points the alien is worth
uint8_t aliens_alienPoints(uint8_t alienNum)
{
	uint8_t row = aliens_getRowFromAlienNumber(alienNum);
	if (row == 0)
		return ALIENS_TOP_ALIEN_POINTS;
	else if (row < GLOBALS_NUM_TOP_ALIEN_ROWS + GLOBALS_NUM_MIDDLE_ALIEN_ROWS)
		return  ALIENS_MIDDLE_ALIEN_POINTS;
	else return  ALIENS_BOTTOM_ALIEN_POINTS;
}

//Prints all living aliens to the console. Used for debugging.
void aliens_printAliens()
{
	xil_printf("\n\raliens alive:\n\r");
	uint16_t r , c; //r = row, c = column
	for (r = 0; r < GLOBALS_NUM_ALIEN_ROWS; r++) //iterate through rows
	{
		for (c = 0; c < GLOBALS_NUM_ALIEN_COLUMNS; c++) //iterate through columns
		{
			xil_printf("%d ", aliens_aliensAlive[r][c]);
		}
		xil_printf("\n\r");
	}
}

//Revives all of the aliens in the array to 1
void aliens_reviveAllAliens()
{
	uint16_t r , c; //r = row, c = column
	for (r = 0; r < GLOBALS_NUM_ALIEN_ROWS; r++) //iterate through rows
	{
		for (c = 0; c < GLOBALS_NUM_ALIEN_COLUMNS; c++) //iterate through columns
		{
			aliens_aliensAlive[r][c] = TRUE;
		}
	}
}

