#include "aliens.h"
/*
 * aliens.c
 *
 *  Created on: Oct 3, 2017
 *      Author: superman
 */


//////////// GLOBAL VARIABLES AND ENUMS //////////////////
static point_t alienBlockPosition; //globally excessible variable
static point_t oldAlienBlockPosition; //globally accessible variable used for erasing alien at old location
static uint8_t movedDownRow = FALSE; //flag which indicates when the alien block has just moved down a row
static alien_guise_type currentAlienGuise = alien_guise_out; //initialize alien guise to out
static alien_direction_type currentAlienDirection = aliens_move_right; //initialize alien crawl direction to right

//Array for aliens currently alive (row, column)
static uint8_t aliensAlive[NUM_ALIEN_ROWS][NUM_ALIEN_COLUMNS] = \
		{{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

//Given a row and column, accesses aliensAlive array and returns whether
//corresponding alien is alive or not
uint8_t isAlienAlive(uint8_t row, uint8_t col)
{
	return aliensAlive[row][col];
}

//Switches the current guise of the aliens
void switchAlienGuises()
{
	if (currentAlienGuise == alien_guise_out)
	{
		currentAlienGuise = alien_guise_in;
	}
	else //if current alien guise is in
	{
		currentAlienGuise = alien_guise_out;
	}
}

//Given a row and column index, returns the location of the corresponding alien on the screen
point_t getOneAlienLocation(uint8_t row, uint8_t col)
{
	int16_t x = getAlienBlockPosition().x + (ALIEN_WIDTH * MAGNIFY_MULT * col) + (ALIEN_SPACE_HORIZ * col); //set this alien's start x
	int16_t y = getAlienBlockPosition().y + (ALIEN_HEIGHT * MAGNIFY_MULT * row) + (ALIEN_SPACE_VERT * row); //set this alien's start y
	point_t alienLocation = {x, y}; //create the point_t variable to use in draw Object for this alien
	return alienLocation;
}

//Given a row and column index, erases the corresponding alien completely (draws it black)
void eraseOneAlien(uint8_t row, uint8_t col)
{
	//get the alien's location
	point_t alienLocation = getOneAlienLocation(row, col);
	//check to see which guise the alien is so we erase just the right stuff
	if (currentAlienGuise == alien_guise_out)
	{
		if (row < NUM_TOP_ALIEN_ROWS) //if we're drawing a top alien
			drawObject(alien_top_out_12x8, ALIEN_WIDTH, ALIEN_HEIGHT, alienLocation, BLACK, FORCE_BLACK_BACKGROUND); //draw top alien
		else if(row < NUM_TOP_ALIEN_ROWS + NUM_MIDDLE_ALIEN_ROWS) //if we're drawing a middle alien
			drawObject(alien_middle_out_12x8, ALIEN_WIDTH, ALIEN_HEIGHT, alienLocation, BLACK, FORCE_BLACK_BACKGROUND); //draw middle alien
		else // we must be drawing a bottom alien
			drawObject(alien_bottom_out_12x8, ALIEN_WIDTH, ALIEN_HEIGHT, alienLocation, BLACK, FORCE_BLACK_BACKGROUND); //draw bottom alien
	}
	else //current alien guise is alien guise in
	{
		if (row < NUM_TOP_ALIEN_ROWS) //if we're drawing a top alien
			drawObject(alien_top_in_12x8, ALIEN_WIDTH, ALIEN_HEIGHT, alienLocation, BLACK, FORCE_BLACK_BACKGROUND); //draw top alien
		else if(row < NUM_TOP_ALIEN_ROWS + NUM_MIDDLE_ALIEN_ROWS) //if we're drawing a middle alien
			drawObject(alien_middle_in_12x8, ALIEN_WIDTH, ALIEN_HEIGHT, alienLocation, BLACK, FORCE_BLACK_BACKGROUND); //draw middle alien
		else // we must be drawing a bottom alien
			drawObject(alien_bottom_in_12x8, ALIEN_WIDTH, ALIEN_HEIGHT, alienLocation, BLACK, FORCE_BLACK_BACKGROUND); //draw bottom alien
	}
}


//Erases all aliens from the screen. Does not kill them. Used for debugging.
void eraseAllAliens()
{
	//just draw all of the aliens I just drew but in black
	//iterate through the rows and columns
	uint8_t r = 0, c = 0;
	for (r = 0; r < NUM_ALIEN_ROWS; r++) //alien rows
	{
		for (c = 0; c < NUM_ALIEN_COLUMNS; c++) //alien column
		{
			if (aliensAlive[r][c]) //if the alien at this position is alive
			{
				//erase the current alien
				eraseOneAlien(r, c);
			}
		}
	}
}

//Draws the alien at a given row and column. Finds its location and draws in white.
void drawOneAlien(uint8_t row, uint8_t col)
{
	//get the alien's location
	point_t alienLocation = getOneAlienLocation(row, col);
	//check to see which guise the alien is so we erase just the right stuff
	if (currentAlienGuise == alien_guise_out)
	{
		if (row < NUM_TOP_ALIEN_ROWS) //if we're drawing a top alien
			drawObject(alien_top_out_12x8, ALIEN_WIDTH, ALIEN_HEIGHT, alienLocation, WHITE, FORCE_BLACK_BACKGROUND); //draw top alien
		else if(row < NUM_TOP_ALIEN_ROWS + NUM_MIDDLE_ALIEN_ROWS) //if we're drawing a middle alien
			drawObject(alien_middle_out_12x8, ALIEN_WIDTH, ALIEN_HEIGHT, alienLocation, WHITE, FORCE_BLACK_BACKGROUND); //draw middle alien
		else // we must be drawing a bottom alien
			drawObject(alien_bottom_out_12x8, ALIEN_WIDTH, ALIEN_HEIGHT, alienLocation, WHITE, FORCE_BLACK_BACKGROUND); //draw bottom alien
	}
	else //current alien guise is alien guise in
	{
		if (row < NUM_TOP_ALIEN_ROWS) //if we're drawing a top alien
			drawObject(alien_top_in_12x8, ALIEN_WIDTH, ALIEN_HEIGHT, alienLocation, WHITE, FORCE_BLACK_BACKGROUND); //draw top alien
		else if(row < NUM_TOP_ALIEN_ROWS + NUM_MIDDLE_ALIEN_ROWS) //if we're drawing a middle alien
			drawObject(alien_middle_in_12x8, ALIEN_WIDTH, ALIEN_HEIGHT, alienLocation, WHITE, FORCE_BLACK_BACKGROUND); //draw middle alien
		else // we must be drawing a bottom alien
			drawObject(alien_bottom_in_12x8, ALIEN_WIDTH, ALIEN_HEIGHT, alienLocation, WHITE, FORCE_BLACK_BACKGROUND); //draw bottom alien
	}
}

//Draws all (living) aliens to the screen.
void drawAllAliens()
{
	//iterate through the rows and columns
	uint8_t r = 0, c = 0;
	for (r = 0; r < NUM_ALIEN_ROWS; r++) //alien rows
	{
		for (c = 0; c < NUM_ALIEN_COLUMNS; c++) //alien column
		{
			if (aliensAlive[r][c]) //if the alien at this position is alive
			{
				//erase the current alien
				drawOneAlien(r, c);
			}
		}
	}
}

//Changes the direction variable for the aliens
void switchAlienDirection()
{
	//if the current direction is right, assign it to left
	if (currentAlienDirection == aliens_move_right)
	{
		currentAlienDirection = aliens_move_left;
	}
	//if the current direction is left, assign it to right
	else
	{
		currentAlienDirection = aliens_move_right;
	}
}

//Facilitates moving the aliens down one row
void moveDownOneRow()
{
	//erase the whole aliens
	eraseAllAliens();
	//move the start line down one row
	point_t newAlienBlockPosition = {getAlienBlockPosition().x, \
			getAlienBlockPosition().y + (ALIEN_HEIGHT * MAGNIFY_MULT)};
	setAlienBlockPosition(newAlienBlockPosition);
	//draw all of the aliens
	drawAllAliens();
	//switch the direction of the aliens
	switchAlienDirection();
	//set row switch flag to true
	movedDownRow = TRUE;
}

//Returns the index of the rightmost column that has aliens still in it.
//Columns are indexed 0-10. There are 11 columns in total
int8_t getRightmostLivingAlienColumn()
{
	int8_t row = 0, col = MAX_ALIEN_COL_INDEX;
	while (col >= 0)
	{
		row = 0;
		while (row <= MAX_ALIEN_ROW_INDEX)
		{
			if (aliensAlive[row][col])
			{
				return col;
			}
			row++;
		}
		col--;
	}
	return ERROR_INDEX;
}

//Returns the leftmost living column of aliens
int8_t getLeftmostLivingAlienColumn()
{
	int8_t row = 0, col = 0;
	while (col <= MAX_ALIEN_COL_INDEX) //iterate through columns
	{
		row = 0;
		while (row <= MAX_ALIEN_ROW_INDEX) //iterate through rows
		{
			//if any alien in this column is alive, return the column index
			if (aliensAlive[row][col])
			{
				return col;
			}
			row++; //increment the row index
		}
		col++; //increment the col index
	}
	//return -1 if there are no living alien columns (edge case)
	return ERROR_INDEX;
}



//Returns the x coordinate of the right edge of the alien block
uint16_t getRightEdgeOfAlienBlock()
{
	//check to see what the rightmost column of aliens is
	uint8_t rightmostLivingAlienColumn = getRightmostLivingAlienColumn();
	uint16_t r = getAlienBlockPosition().x \
			+ (ALIEN_WIDTH * MAGNIFY_MULT * (rightmostLivingAlienColumn+1)) \
			+ (ALIEN_SPACE_HORIZ * (rightmostLivingAlienColumn));
	return r;
}


//Returns the value that must be added to the alien block position so it can
//make it all the way to the left edge of the screen.
int16_t getLeftmostLivingAlienColumnAdjustment()
{
	return (getLeftmostLivingAlienColumn() * (ALIEN_WIDTH  + ALIEN_SPACE_HORIZ + NUM_ALIEN_COLUMNS));
}

//Updates the block position of aliens depending on current location.
//Called in moveAliens()
void updateAlienBlockPosition()
{
	//check the bounds
	if (currentAlienDirection == aliens_move_right)
	{
		//if the right edge of the alien block is at the edge of the screen minus a bit
		if (getRightEdgeOfAlienBlock() >= (WIDTH_DISPLAY - SCREEN_EDGE_BUMPER_PIXELS))
		{
			moveDownOneRow();
		}
		else
		{
			//update the alien's position
			oldAlienBlockPosition = getAlienBlockPosition();
			point_t newAlienBlockPosition = {(getAlienBlockPosition().x + ALIEN_MOVE_PIXELS), getAlienBlockPosition().y};
			setAlienBlockPosition(newAlienBlockPosition);
		}
	}
	else //if aliens are moving left
	{
		//if the left end of the alien block is too close to the left edge of the screen
		if ( (getAlienBlockPosition().x + getLeftmostLivingAlienColumnAdjustment()) <= SCREEN_EDGE_BUMPER_PIXELS)
		{
			moveDownOneRow();
		}
		else
		{
			//update the alien's position
			oldAlienBlockPosition = getAlienBlockPosition();
			point_t newAlienBlockPosition = {(getAlienBlockPosition().x - ALIEN_MOVE_PIXELS), getAlienBlockPosition().y};
			setAlienBlockPosition(newAlienBlockPosition);
		}
	}
}

//Erases the half of the alien that needs to be erased when moving the alien over.
//Takes in the row and column index of the alien and finds position based on that current alien block position.
void eraseAlienRectangle(uint8_t r, uint8_t c)
{
	uint16_t xOld = oldAlienBlockPosition.x + (ALIEN_WIDTH * MAGNIFY_MULT * c) + (ALIEN_SPACE_HORIZ * c); //set this alien's start x
	uint16_t yOld = oldAlienBlockPosition.y + (ALIEN_HEIGHT * MAGNIFY_MULT * r) + (ALIEN_SPACE_VERT * r); //set this alien's start y
	if (currentAlienDirection == aliens_move_right)
	{
		eraseRectangle((point_t){xOld, yOld}, ALIEN_MOVE_PIXELS, ALIEN_HEIGHT);
	}
	else //if you're moving left
	{
		eraseRectangle((point_t){(xOld + ALIEN_WIDTH), yOld}, ALIEN_MOVE_PIXELS, ALIEN_HEIGHT);
	}
}

//Moves all living aliens one step. Handles moving down rows, switching directions, etc.
void moveAliens()
{
	//switch alien guise
	switchAlienGuises();
	//update the alien positions
	updateAlienBlockPosition();
	if (!movedDownRow)
	{
		uint8_t r = 0, c = 0;
		for (r = 0; r < NUM_ALIEN_ROWS; r++) //alien rows
		{
			for (c = 0; c < NUM_ALIEN_COLUMNS; c++) //alien column
			{
				if (aliensAlive[r][c]) //if the alien at this position is alive
				{
					//erase the rectangle for the aliens
					eraseAlienRectangle(r, c);
					//draw the current alien
					drawOneAlien(r, c);
				}
			}
		}
	}
	movedDownRow = FALSE; //reset this so the aliens can move later
}

//Given the alien index passed in (0-54), returns the row in which this alien is located
uint8_t getRowFromAlienNumber(uint8_t num)
{
	int c = 0; //this is our counter
	while (num > MAX_ALIEN_COL_INDEX) //Exits when you get a number between 0 and 10
	{
		num -= NUM_ALIEN_COLUMNS; //decrement num by 11
		c++; //increment c
	}
	return c;
}

//Given the alien index passed in, returns the column in which this alien is located
uint8_t getColumnFromAlienNumber(uint8_t num)
{
	while (num > MAX_ALIEN_COL_INDEX) //exits when you get a number between 0 and 10
		num -= NUM_ALIEN_COLUMNS; //decrement num by 11
	return num;
}

//Given a number between 0-54, kills the corresponding alien
void killAlien(uint8_t alien)
{
	//map this number alien to a row/column
	uint8_t row = getRowFromAlienNumber(alien);
	uint8_t col = getColumnFromAlienNumber(alien);

	//erase this alien
	eraseOneAlien(row, col);

	//kill this alien
	aliensAlive[row][col] = 0;
}

//Sets the global for alien block position
void setAlienBlockPosition(point_t val)
{
	alienBlockPosition = val;
}

//Returns the global for alien block position
point_t getAlienBlockPosition()
{
	return alienBlockPosition;
}

//Prints all living aliens to the console. Used for debugging.
void printAliens()
{
	xil_printf("\n\raliens alive:\n\r");
	int r , c; //r = row, c = column
	for (r = 0; r < NUM_ALIEN_ROWS; r++) //iterate through rows
	{
		for (c = 0; c < NUM_ALIEN_COLUMNS; c++) //iterate through columns
		{
			xil_printf("%d ", aliensAlive[r][c]);
		}
		xil_printf("\n\r");
	}
}
