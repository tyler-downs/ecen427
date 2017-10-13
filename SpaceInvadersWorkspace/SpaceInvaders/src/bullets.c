/*
 * bullets.c
 *
 *  Created on: Oct 3, 2017
 *      Author: superman
 */

#include "bullets.h"
#include <time.h>
#include <stdlib.h>



//////////////////// GLOBAL VARIABLES ///////////////////////////
uint8_t tankBulletExists = FALSE; 			//global variable that indicates if the tank bullet is active

//Returns the spawn position of the tank when it fires its bullet
point_t getTankBulletSpawnPosition()
{
	return ((point_t) {getTankPosition() + TANK_BULLET_OFFSET_X, TANK_START_Y - TANK_BULLET_OFFSET_Y});
}

//Draws the tank bullet to the display
void drawTankBullet(point_t location)
{
	drawObject(tankBullet_3x6, TANK_BULLET_WIDTH, TANK_BULLET_HEIGHT, location, WHITE, LEAVE_BACKGROUND);
}

//Fires the tank bullet. Will only work if the bullet isn't on the screen already.
void fireTankBullet()
{
	if (!tankBulletExists)
	{
		//draw the tank bullet just above the location of the tank
		drawTankBullet(getTankBulletSpawnPosition());
		//set the globally accessible tank bullet position
		setTankBulletPosition(getTankBulletSpawnPosition());
		//Set the tank bullet exits flag to true
		tankBulletExists = TRUE;
	}
}


//Erases entire tank bullet. For debugging.
void eraseEntireTankBullet()
{
	drawObject(tankBullet_3x6, TANK_BULLET_WIDTH, TANK_BULLET_HEIGHT, getTankBulletPosition(), BLACK, FORCE_BLACK_BACKGROUND);
	tankBulletExists = FALSE;
}

//Advances the tank bullet on the display. Updates its location. Handles off-screen behavior.
void advanceTankBullet()
{
	//only do anything if there is a tank bullet on the screen
	if (tankBulletExists)
	{
		//if the tank bullet is off the screen, remove it
		if (getTankBulletPosition().y <= 0)
		{
			eraseEntireTankBullet();
			return;
		}
		else
		{
			//move the tank bullet up (decrement y value)
			point_t newTankBulletPosition = {getTankBulletPosition().x, getTankBulletPosition().y - TANK_BULLET_TRAVEL_DISTANCE};
			//erase the bottom of the tank bullet
			eraseRectangle((point_t){newTankBulletPosition.x + MAGNIFY_MULT, newTankBulletPosition.y + TANK_BULLET_HEIGHT}, MAGNIFY_MULT, TANK_BULLET_TRAVEL_DISTANCE);
			//draw the new tank bullet
			drawTankBullet(newTankBulletPosition);
			//update the globally accessible tank bullet location
			setTankBulletPosition(newTankBulletPosition);
		}
	}
}

//Given the row and column index of an alien, returns the location at which the alien bullet appears.
point_t getAlienBulletSpawnPosition(int8_t row, int8_t col)
{
	uint16_t x = getAlienBlockPosition().x + (ALIEN_WIDTH * MAGNIFY_MULT * col) + (ALIEN_SPACE_HORIZ * col) + HALF_ALIEN + MAGNIFY_MULT;
	uint16_t y = (getAlienBlockPosition().y + (ALIEN_HEIGHT * MAGNIFY_MULT * row) + ALIEN_SPACE_VERT * row) + ALIEN_HEIGHT*MAGNIFY_MULT;
	return (point_t) {x, y};
}

//switches the bullet giuse for the given alien bullet
void switchAlienBulletGuise(int8_t bulletNumber)
{
	//if the bullet is in guise 0, set it to 1
	if (getAlienBulletGuise(bulletNumber) == bullet_guise_0)
	{
		setAlienBulletGuise(bulletNumber, bullet_guise_1);
	}
	else //if the bullet is in guise 1, set it to 0
	{
		setAlienBulletGuise(bulletNumber, bullet_guise_0);
	}
}

//Erases an alien bullet given the type, guise, and position (draws it black).
void eraseAlienBullet(bullet_type type, bullet_guise_type guise, point_t location)
{
	if (type == cross_bullet)
	{
		if (guise == bullet_guise_0)
		{
			drawObject(crossBulletGuise0_5x6, CROSS_BULLET_WIDTH, CR0SS_BULLET_HEIGHT, location, BLACK, LEAVE_BACKGROUND);
		}
		else // guise 1
		{
			drawObject(crossBulletGuise1_5x6, CROSS_BULLET_WIDTH, CR0SS_BULLET_HEIGHT, location, BLACK, LEAVE_BACKGROUND);
		}
	}
	else //zigzag
	{
		if (guise == bullet_guise_0)
		{
			drawObject(zigzagBulletGuise0_3x7, ZIGZAG_BULLET_WIDTH, ZIGZAG_BULLET_HEIGHT, location, BLACK, LEAVE_BACKGROUND);
		}
		else // guise 1
		{
			drawObject(zigzagBulletGuise1_3x7, ZIGZAG_BULLET_WIDTH, ZIGZAG_BULLET_HEIGHT, location, BLACK, LEAVE_BACKGROUND);
		}
	}
}

//Draws the alien bullet given the type, guise, and location.
void drawAlienBullet(bullet_type type, bullet_guise_type guise, point_t location)
{
	if (type == cross_bullet)
	{
		if (guise == bullet_guise_0)
		{
			drawObject(crossBulletGuise0_5x6, CROSS_BULLET_WIDTH, CR0SS_BULLET_HEIGHT, location, WHITE, LEAVE_BACKGROUND);
		}
		else // guise 1
		{
			drawObject(crossBulletGuise1_5x6, CROSS_BULLET_WIDTH, CR0SS_BULLET_HEIGHT, location, WHITE, LEAVE_BACKGROUND);
		}
	}
	else //zigzag
	{
		if (guise == bullet_guise_0)
		{
			drawObject(zigzagBulletGuise0_3x7, ZIGZAG_BULLET_WIDTH, ZIGZAG_BULLET_HEIGHT, location, WHITE, LEAVE_BACKGROUND);
		}
		else // guise 1
		{
			drawObject(zigzagBulletGuise1_3x7, ZIGZAG_BULLET_WIDTH, ZIGZAG_BULLET_HEIGHT, location, WHITE, LEAVE_BACKGROUND);
		}
	}
}

//When a bullet is fired from an alien, this assigns a free index to it.
//If there are already four bullets on the screen, returns -1.
int8_t assignBulletNumber()
{
	int8_t b;
	for (b = 0; b < MAX_ALIEN_BULLETS; b++) //check all the bullets
	{
		if (!isBulletActive(b)) //if we find one that's not active
		{
			return b; //new bullet number
		}
	}
	return ERROR_INDEX; //-1 means all bullets are currently active
}

//Randomly chooses an alien on the bottom row and fires a bullet from that alien.
void fireRandomAlienBullet()
{
	int8_t bulletNumber = assignBulletNumber(); //assign bullet number
	if (bulletNumber < 0) //all bullets currently active
		return;
	uint8_t alienInColumn = FALSE; //set this flag by default to false
	int8_t row;
	int8_t randCol;
	while (!alienInColumn)
	{
		//choose a number between 0 and 10
		//I set random seed in disp_init()
		randCol = rand() % NUM_ALIEN_COLUMNS;
		//check to see whether there is an alien in this column
		//start with the highest row and go backwards
		for (row = NUM_ALIEN_ROWS-1; row >= 0; row--)
		{
			//if there's an alien in this row
			if (isAlienAlive(row, randCol))
			{
				//setAlieninColumn to true and exit the for loop
				alienInColumn = TRUE;
				break;
			}
		}
	}
	//now aliensAlive[row][randCol] contains the alien that will shoot
	//randomly select bullet type
	bullet_type type = rand() % NUM_BULLET_TYPES;
	point_t spawnPosition = getAlienBulletSpawnPosition(row, randCol);
	drawAlienBullet(type, bullet_guise_0, spawnPosition); 		//draw the bullet just using the first guise

	//save bullet information
	setAlienBulletPosition(bulletNumber, spawnPosition); 		//set position
	setAlienBulletType(bulletNumber, type); 					//set bullet type
	setAlienBulletGuise(bulletNumber, bullet_guise_0); 			//first guise
	setBulletStatus(bulletNumber, TRUE); 						//activate bullet

}

//Given a bullet index, advances the alien bullet on the display.
void advanceOneAlienBullet(int8_t bulletNumber)
{

	//erase bullet
	eraseAlienBullet(getAlienBulletType(bulletNumber), getAlienBulletGuise(bulletNumber), getAlienBulletPosition(bulletNumber));
	//check to see whether the bullet has left the screen
	if (getAlienBulletPosition(bulletNumber).y >= BOTTOMLINE_TOP - (ZIGZAG_BULLET_HEIGHT+ALIEN_BULLET_DEACTIVATE_BUFFER)*MAGNIFY_MULT)
	{
		//deactivate the bullet
		setBulletStatus(bulletNumber, FALSE);
	}
	else
	{
		//switch guises
		switchAlienBulletGuise(bulletNumber);
		//change the position of the bullet
		point_t newAlienBulletPosition = {getAlienBulletPosition(bulletNumber).x, getAlienBulletPosition(bulletNumber).y + ALIEN_BULLET_TRAVEL_DISTANCE};
		//redraw the alien bullet
		drawAlienBullet(getAlienBulletType(bulletNumber), getAlienBulletGuise(bulletNumber), newAlienBulletPosition);
		//set new alien bullet position globally
		setAlienBulletPosition(bulletNumber, newAlienBulletPosition);
	}
}

//Advances all alien bullets on the display.
void advanceAllAlienBullets()
{
	//check to see whether each bullet is active
	//advance that bullet
	uint8_t i;
	for (i = 0; i < MAX_ALIEN_BULLETS; i++)
	{
		if (isBulletActive(i))
		{
			//draw the bullet
			advanceOneAlienBullet(i);
		}
	}
}


