#include "aliens.h"
/*
 * aliens.c
 *
 *  Created on: Oct 3, 2017
 *      Author: superman
 */

#define ALIEN_MOVE_PIXELS TANK_MOVE_PIXELS

static point_t alienBlockPosition;
static point_t oldAlienBlockPosition;

uint8_t isAlienAlive(uint8_t row, uint8_t col)
{
	return aliensAlive[row][col];
}

//TEST
void printAliens()
{
	xil_printf("\n\raliens alive:\n\r");
	int r , c;
	for (r = 0; r < 5; r++)
	{
		for (c = 0; c < 11; c++)
		{
			xil_printf("%d ", aliensAlive[r][c]);
		}
		xil_printf("\n\r");
	}


}

void switchAlienGuises()
{
	if (currentAlienGuise == alien_guise_out)
	{
		currentAlienGuise = alien_guise_in;
	}
	else //if currnet alien guise is in
	{
		currentAlienGuise = alien_guise_out;
	}
}

point_t getOneAlienLocation(uint8_t row, uint8_t col)
{
	int16_t x = getAlienBlockPosition().x + (ALIEN_WIDTH * MAGNIFY_MULT * col) + (ALIEN_SPACE_HORIZ * col); //set this alien's start x
	int16_t y = getAlienBlockPosition().y + (ALIEN_HEIGHT * MAGNIFY_MULT * row) + (ALIEN_SPACE_VERT * row); //set this alien's start y
	point_t alienLocation = {x, y}; //create the point_t variable to use in draw Object for this alien
	return alienLocation;
}

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

//Draws the alien at a given row and column. Finds its location and draws in white
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

static uint8_t movedDownRow = 0;

//facilitates moving the aliens down one row
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
	while (col <= MAX_ALIEN_COL_INDEX)
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
		col++;
	}
	return ERROR_INDEX;
}



//returns the x coordinate of the right edge of the alien block
uint16_t getRightEdgeOfAlienBlock()
{
	//check to see what the rightmost column of aliens is
	uint8_t rightmostLivingAlienColumn = getRightmostLivingAlienColumn();
	uint16_t r = getAlienBlockPosition().x \
			+ (ALIEN_WIDTH * MAGNIFY_MULT * (rightmostLivingAlienColumn+1)) \
			+ (ALIEN_SPACE_HORIZ * (rightmostLivingAlienColumn));
	return r;
}



int16_t getLeftmostLivingAlienColumnAdjustment()
{
	return (getLeftmostLivingAlienColumn() * (ALIEN_WIDTH  + ALIEN_SPACE_HORIZ + NUM_ALIEN_COLUMNS));
}

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
			point_t newAlienBlockPosition = {(getAlienBlockPosition().x + 3*MAGNIFY_MULT), getAlienBlockPosition().y}; //TODO: magic number
			setAlienBlockPosition(newAlienBlockPosition);
			xil_printf("New alien block position: %d, %d\n\r", newAlienBlockPosition.x, newAlienBlockPosition.y);
		}
	}
	else //if aliens are moving left
	{
		//if the left end of the alien block is too close to the left edge of the screen
		printf("Adjustment value: %d\n\r", getLeftmostLivingAlienColumnAdjustment());
		if ( (getAlienBlockPosition().x + getLeftmostLivingAlienColumnAdjustment()) <= SCREEN_EDGE_BUMPER_PIXELS)
		{
			moveDownOneRow();
		}
		else
		{
			//update the alien's position
			oldAlienBlockPosition = getAlienBlockPosition();
			point_t newAlienBlockPosition = {(getAlienBlockPosition().x - 3*MAGNIFY_MULT), getAlienBlockPosition().y};
			setAlienBlockPosition(newAlienBlockPosition);
			xil_printf("New alien block position: %d, %d\n\r", newAlienBlockPosition.x, newAlienBlockPosition.y);
		}
	}
}

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
	movedDownRow = 0;
}

//Given the alien index passed in (0-54), returns the row in which this alien is located
uint8_t getRowFromAlienNumber(uint8_t num)
{
	int c = 0;
	while (num > MAX_ALIEN_COL_INDEX)
	{
		num -= NUM_ALIEN_COLUMNS;
		c++;
	}
	return c;
}

//Given the alien index passed in, returns the column in which this alien is located
uint8_t getColumnFromAlienNumber(uint8_t num)
{
	while (num > MAX_ALIEN_COL_INDEX)
		num -= NUM_ALIEN_COLUMNS;
	return num;
}

void killAlien(uint8_t alien)
{
	//map this number alien to a row/column
	uint8_t row = getRowFromAlienNumber(alien);
	uint8_t col = getColumnFromAlienNumber(alien);

	//erase this alien
	eraseOneAlien(row, col);

	//kill this alien
	aliensAlive[row][col] = 0;

	xil_printf("%d,%d = %d\n\r", row, col, aliensAlive[row][col]);
	printAliens();
}

void setAlienBlockPosition(point_t val)
{
	alienBlockPosition = val;
}

point_t getAlienBlockPosition()
{
	return alienBlockPosition;
}

void fireRandomAlienMissile()
{

}

