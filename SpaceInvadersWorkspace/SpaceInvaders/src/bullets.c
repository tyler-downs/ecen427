/*
 * bullets.c
 *
 *  Created on: Oct 3, 2017
 *      Author: superman
 */

#include "bullets.h"
#include <time.h>
#include <stdlib.h>

#define TANK_BULLET_OFFSET_X 12
#define TANK_BULLET_OFFSET_Y (TANK_HEIGHT+4)
#define TANK_BULLET_HEIGHT 6
#define TANK_BULLET_WIDTH 3
#define TANK_BULLET_TRAVEL_DISTANCE 6

point_t getTankBulletSpawnPosition()
{
	return ((point_t) {getTankPosition() + TANK_BULLET_OFFSET_X, TANK_START_Y - TANK_BULLET_OFFSET_Y});
}


void drawTankBullet(point_t location)
{
	drawObject(tankBullet_3x6, TANK_BULLET_WIDTH, TANK_BULLET_HEIGHT, location, WHITE);
}

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


//for debugging
void eraseEnitreTankBullet()
{
	drawObject(tankBullet_3x6, TANK_BULLET_WIDTH, TANK_BULLET_HEIGHT, getTankBulletPosition(), BLACK);
	tankBulletExists = FALSE;
}


void advanceTankBullet()
{
	//only do anything if there is a tank bullet on the screen
	if (tankBulletExists)
	{
		//if the tank bullet is off the screen, remove it
		if (getTankBulletPosition().y <= 0)
		{
			eraseEnitreTankBullet();
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


point_t getAlienBulletSpawnPosition(int8_t row, int8_t col)
{

}

//TODO: this function always picks row 4 even if that row's alien in the column is dead.
//Figure out why.
void fireRandomAlienBullet()
{
	uint8_t alienInColumn = FALSE;
	int8_t row;
	int8_t randCol;
	while (!alienInColumn)
	{
		//choose a number between 0 and 10
		randCol = (uint8_t)rand() % NUM_ALIEN_COLUMNS;
		xil_printf("randCol = %d\n\r", randCol);
		//check to see whether there is an alien in this column
		//start with the highest row and go backwards
		for (row = 4; row >= 0; row--)
		{
			xil_printf("row = %d\n\r", row);
			//if there's an alien in this row
			if (aliensAlive[row][randCol])
			{
				//setAlieninColumn to true and exit the for loop
				alienInColumn = TRUE;
				break;
			}
		}
	}
	//now aliensAlive[row][randCol] contains the alien that will shoot
	xil_printf("shooting from alien %d,%d\n\r", row, randCol);
}


