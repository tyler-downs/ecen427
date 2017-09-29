/*
 * globals.c
 *
 *  Created on: Sep 22, 2017
 *      Author: superman
 */

#include "globals.h"
#include "bitmaps.h"

// Here are the globals.
static uint16_t tankPosition;
static point_t tankBulletPosition;
static point_t alienBlockPosition;
static point_t oldAlienBlockPosition;

#define NUM_BUNKER_BLOCKS 10
static uint8_t bunker0State[NUM_BUNKER_BLOCKS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
static uint8_t bunker1State[NUM_BUNKER_BLOCKS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
static uint8_t bunker2State[NUM_BUNKER_BLOCKS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
static uint8_t bunker3State[NUM_BUNKER_BLOCKS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

static uint16_t currentScore = 0;

//array for aliens alive (row, column)
static uint8_t aliensAlive[NUM_ALIEN_ROWS][NUM_ALIEN_COLUMNS] = \
		{{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};


// Here are the accessors.
void setTankPosition(uint16_t val) {
  tankPosition = val;
}

uint16_t getTankPosition() {
  return tankPosition;
}

void setTankBulletPosition(point_t val) {
  tankBulletPosition.x = val.x;
  tankBulletPosition.y = val.y;
}

point_t getTankBulletPosition() {
  return tankBulletPosition;
}

void setAlienBlockPosition(point_t val)
{
	alienBlockPosition = val;
}

point_t getAlienBlockPosition()
{
	return alienBlockPosition;
}

void setAlienBulletPosition0(point_t val, bullet_type bul)
{

}

point_t getAlienBulletPosition0()
{

}

void setAlienBulletPosition1(point_t val, bullet_type bul)
{

}

point_t getAlienBulletPosition1()
{

}

void setAlienBulletPosition2(point_t val, bullet_type bul)
{

}

point_t getAlienBulletPosition2()
{

}

void setAlienBulletPosition3(point_t val, bullet_type bul)
{

}

point_t getAlienBulletPosition3()
{

}

void erodeBunker(uint8_t bunkerIndex, uint8_t blockIndex)
{

}

uint8_t getBunkerErosionState(uint8_t bunkerIndex, uint8_t blockIndex)
{

}

void fireTankBullet()
{

}

#define TANK_MOVE_PIXELS (3 * MAGNIFY_MULT)
#define TANK_SCREEN_EDGE_RIGHT (WIDTH_DISPLAY-(TANK_WIDTH+TANK_MOVE_PIXELS)*MAGNIFY_MULT)
void moveTankRight()
{
	if (getTankPosition() < TANK_SCREEN_EDGE_RIGHT)
	{
		//erase the rectangle
		eraseRectangle((point_t){getTankPosition(), TANK_START_Y}, TANK_MOVE_PIXELS, TANK_HEIGHT);
		//change the start point of the tank
		uint16_t newTankPosition = getTankPosition() + TANK_MOVE_PIXELS;
		setTankPosition(newTankPosition);
		//draw the tank
		drawObject(tank_15x8, TANK_WIDTH, TANK_HEIGHT, (point_t){newTankPosition, TANK_START_Y}, GREEN);

	}

}


#define TANK_SCREEN_EDGE_LEFT TANK_MOVE_PIXELS
void moveTankLeft()
{
	if (getTankPosition() > TANK_SCREEN_EDGE_LEFT)
	{
		//erase the rectangle
		eraseRectangle((point_t){getTankPosition() + TANK_WIDTH + TANK_MOVE_PIXELS, TANK_START_Y}, TANK_MOVE_PIXELS, TANK_HEIGHT);
		//change the start point of the tank
		uint16_t newTankPosition = getTankPosition() - TANK_MOVE_PIXELS;
		setTankPosition(newTankPosition);
		//draw the tank
		drawObject(tank_15x8, TANK_WIDTH, TANK_HEIGHT, (point_t){newTankPosition, TANK_START_Y}, GREEN);
	}
}


#define ALIEN_MOVE_PIXELS TANK_MOVE_PIXELS

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
	uint16_t x = getAlienBlockPosition().x + (ALIEN_WIDTH * MAGNIFY_MULT * col) + (ALIEN_SPACE_HORIZ * col); //set this alien's start x
	uint16_t y = getAlienBlockPosition().y + (ALIEN_HEIGHT * MAGNIFY_MULT * row) + (ALIEN_SPACE_VERT * row); //set this alien's start y
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
			drawObject(alien_top_out_12x8, ALIEN_WIDTH, ALIEN_HEIGHT, alienLocation, BLACK); //draw top alien
		else if(row < NUM_TOP_ALIEN_ROWS + NUM_MIDDLE_ALIEN_ROWS) //if we're drawing a middle alien
			drawObject(alien_middle_out_12x8, ALIEN_WIDTH, ALIEN_HEIGHT, alienLocation, BLACK); //draw middle alien
		else // we must be drawing a bottom alien
			drawObject(alien_bottom_out_12x8, ALIEN_WIDTH, ALIEN_HEIGHT, alienLocation, BLACK); //draw bottom alien
	}
	else //current alien guise is alien guise in
	{
		if (row < NUM_TOP_ALIEN_ROWS) //if we're drawing a top alien
			drawObject(alien_top_in_12x8, ALIEN_WIDTH, ALIEN_HEIGHT, alienLocation, BLACK); //draw top alien
		else if(row < NUM_TOP_ALIEN_ROWS + NUM_MIDDLE_ALIEN_ROWS) //if we're drawing a middle alien
			drawObject(alien_middle_in_12x8, ALIEN_WIDTH, ALIEN_HEIGHT, alienLocation, BLACK); //draw middle alien
		else // we must be drawing a bottom alien
			drawObject(alien_bottom_in_12x8, ALIEN_WIDTH, ALIEN_HEIGHT, alienLocation, BLACK); //draw bottom alien
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
			drawObject(alien_top_out_12x8, ALIEN_WIDTH, ALIEN_HEIGHT, alienLocation, WHITE); //draw top alien
		else if(row < NUM_TOP_ALIEN_ROWS + NUM_MIDDLE_ALIEN_ROWS) //if we're drawing a middle alien
			drawObject(alien_middle_out_12x8, ALIEN_WIDTH, ALIEN_HEIGHT, alienLocation, WHITE); //draw middle alien
		else // we must be drawing a bottom alien
			drawObject(alien_bottom_out_12x8, ALIEN_WIDTH, ALIEN_HEIGHT, alienLocation, WHITE); //draw bottom alien
	}
	else //current alien guise is alien guise in
	{
		if (row < NUM_TOP_ALIEN_ROWS) //if we're drawing a top alien
			drawObject(alien_top_in_12x8, ALIEN_WIDTH, ALIEN_HEIGHT, alienLocation, WHITE); //draw top alien
		else if(row < NUM_TOP_ALIEN_ROWS + NUM_MIDDLE_ALIEN_ROWS) //if we're drawing a middle alien
			drawObject(alien_middle_in_12x8, ALIEN_WIDTH, ALIEN_HEIGHT, alienLocation, WHITE); //draw middle alien
		else // we must be drawing a bottom alien
			drawObject(alien_bottom_in_12x8, ALIEN_WIDTH, ALIEN_HEIGHT, alienLocation, WHITE); //draw bottom alien
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
	movedDownRow = 1;
}



//TODO: this is full of magic numbers!
//Returns the index of the rightmost column that has aliens still in it.
//Columns are indexed 0-10. There are 11 columns in total
uint8_t getRightmostLivingAlienColumn()
{
	if (aliensAlive[0][10] | aliensAlive[1][10] | aliensAlive[2][10] | aliensAlive[3][10] | aliensAlive[4][10])
	{
		return 10;
	}
	else if (aliensAlive[0][9] | aliensAlive[1][9] | aliensAlive[2][9] | aliensAlive[3][9] | aliensAlive[4][9])
	{
		return 9;
	}
	else if (aliensAlive[0][8] | aliensAlive[1][8] | aliensAlive[2][8] | aliensAlive[3][8] | aliensAlive[4][8])
	{
		return 8;
	}
	else if (aliensAlive[0][7] | aliensAlive[1][7] | aliensAlive[2][7] | aliensAlive[3][7] | aliensAlive[4][7])
	{
		return 7;
	}
	else if (aliensAlive[0][6] | aliensAlive[1][6] | aliensAlive[2][6] | aliensAlive[3][6] | aliensAlive[4][6])
	{
		return 6;
	}
	else if (aliensAlive[0][5] | aliensAlive[1][5] | aliensAlive[2][5] | aliensAlive[3][5] | aliensAlive[4][5])
	{
		return 5;
	}
	else if (aliensAlive[0][4] | aliensAlive[1][4] | aliensAlive[2][4] | aliensAlive[3][4] | aliensAlive[4][4])
	{
		return 4;
	}
	else if (aliensAlive[0][3] | aliensAlive[1][3] | aliensAlive[2][3] | aliensAlive[3][3] | aliensAlive[4][3])
	{
		return 3;
	}
	else if (aliensAlive[0][2] | aliensAlive[1][2] | aliensAlive[2][2] | aliensAlive[3][2] | aliensAlive[4][2])
	{
		return 2;
	}
	else if (aliensAlive[0][1] | aliensAlive[1][1] | aliensAlive[2][1] | aliensAlive[3][1] | aliensAlive[4][1])
	{
		return 1;
	}
	else return 0;
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


#define SCREEN_EDGE_BUMPER_PIXELS 10

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
			point_t newAlienBlockPosition = {(getAlienBlockPosition().x + 3*MAGNIFY_MULT), getAlienBlockPosition().y};
			setAlienBlockPosition(newAlienBlockPosition);
			xil_printf("New alien block position: %d, %d\n\r", newAlienBlockPosition.x, newAlienBlockPosition.y);
		}
	}
	else //if aliens are moving left
	{
		//if the left end of the alien block is too close to the left edge of the screen
		if (getAlienBlockPosition().x <= SCREEN_EDGE_BUMPER_PIXELS)
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

void killAlien(uint8_t alien)
{

}

void fireRandomAlienMissile()
{

}
void updateBulletPositions()
{

}

uint16_t getCurrentScore() {return currentScore;}

void setScore(uint16_t score) {currentScore = score;}
