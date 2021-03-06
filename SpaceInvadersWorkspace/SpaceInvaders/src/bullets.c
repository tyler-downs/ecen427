/*
 * bullets.c
 *
 *  Created on: Oct 3, 2017
 *      Author: superman
 */

#include "bullets.h"
#include "sounds.h"
#include "buzzerDriver.h"
#include <time.h>
#include <stdlib.h>

//////////////////////// DEFINES ////////////////////////////////
#define BULLET_CEILING 60 //the highest the bullet can go on the screen before being erased
#define GLOBALS_TANK_BULLET_WIDTH 3 //width of the tank bullet
#define NO_PIXEL -10 //indicates an error/default case in functions that find pixels

#define SHOOT_BUZZ_DURATION 5000000 //half of a second

//////////////////// GLOBAL VARIABLES ///////////////////////////
uint8_t bullets_tankBulletExists = FALSE; 			//global variable that indicates if the tank bullet is active

//reset tankBulletExists global
void bullets_disableTankBullet()
{
	bullets_tankBulletExists = FALSE;
}

//returns true if the tank bullet is on the screen
uint8_t bullets_tankBulletOnScreen()
{
	return bullets_tankBulletExists;
}

//Returns the spawn position of the tank when it fires its bullet
point_t getTankBulletSpawnPosition()
{
	return ((point_t) {globals_getTankPosition() + GLOBALS_TANK_BULLET_OFFSET_X, GLOBALS_TANK_START_Y - GLOBALS_TANK_BULLET_OFFSET_Y});
}

//Draws the tank bullet to the display
void drawTankBullet(point_t location)
{
	render_drawObject(tankBullet_3x6, GLOBALS_TANK_BULLET_WIDTH, GLOBALS_TANK_BULLET_HEIGHT, location, GLOBALS_BULLET_WHITE, GLOBALS_LEAVE_BACKGROUND);
}

//Fires the tank bullet. Will only work if the bullet isn't on the screen already.
void bullets_fireTankBullet()
{
	if (!bullets_tankBulletExists)
	{
		//Set the tank bullet exits flag to true
		bullets_tankBulletExists = TRUE;
		//draw the tank bullet just above the location of the tank
		drawTankBullet(getTankBulletSpawnPosition());
		//set the globally accessible tank bullet position
		bullets_setTankBulletPosition(getTankBulletSpawnPosition());
		sounds_playShootSound(); //play the shoot sound

		buzzer_setDelay(SHOOT_BUZZ_DURATION); //set buzz length
		buzzer_buzz(); //buzz
	}
}


//Erases entire tank bullet.
void bullets_eraseEntireTankBullet()
{
	render_drawObject(tankBullet_3x6, GLOBALS_TANK_BULLET_WIDTH, GLOBALS_TANK_BULLET_HEIGHT, bullets_getTankBulletPosition(), GLOBALS_BLACK, GLOBALS_FORCE_BLACK_BACKGROUND);
}

//Advances the tank bullet on the display. Updates its location. Handles off-screen behavior.
void bullets_advanceTankBullet()
{
	//only do anything if there is a tank bullet on the screen
	if (bullets_tankBulletExists)
	{
		//if the tank bullet is off the screen, remove it
		if (bullets_getTankBulletPosition().y <= 0)
		{
			bullets_eraseEntireTankBullet();
			return;
		}
		else
		{
			//move the tank bullet up (decrement y value)
			point_t newTankBulletPosition = {bullets_getTankBulletPosition().x, bullets_getTankBulletPosition().y - GLOBALS_TANK_BULLET_TRAVEL_DISTANCE};
			if (newTankBulletPosition.y < BULLET_CEILING) //if the bullet's going off the top of the screen
			{
				bullets_eraseEntireTankBullet(); //remove it from the screen
				bullets_tankBulletExists = FALSE; //reset global
				return;
			}
			//erase the bottom of the tank bullet
			//eraseRectangle((point_t){newTankBulletPosition.x, newTankBulletPosition.y + TANK_BULLET_HEIGHT*MAGNIFY_MULT}, TANK_BULLET_WIDTH, TANK_BULLET_TRAVEL_DISTANCE);
			bullets_eraseEntireTankBullet();
			//draw the new tank bullet
			drawTankBullet(newTankBulletPosition);
			//update the globally accessible tank bullet location
			bullets_setTankBulletPosition(newTankBulletPosition);
		}
	}
}

//Given the row and column index of an alien, returns the location at which the alien bullet appears.
point_t getAlienBulletSpawnPosition(int8_t row, int8_t col)
{
	uint16_t x = aliens_getAlienBlockPosition().x + (GLOBALS_ALIEN_WIDTH * GLOBALS_MAGNIFY_MULT * col) + (GLOBALS_ALIEN_SPACE_HORIZ * col) + ALIENS_HALF_ALIEN + GLOBALS_MAGNIFY_MULT;
	uint16_t y = (aliens_getAlienBlockPosition().y + (GLOBALS_ALIEN_HEIGHT * GLOBALS_MAGNIFY_MULT * row) + GLOBALS_ALIEN_SPACE_VERT * row) + GLOBALS_ALIEN_HEIGHT*GLOBALS_MAGNIFY_MULT;
	return (point_t) {x, y};
}

//switches the bullet giuse for the given alien bullet
void switchAlienBulletGuise(int8_t bulletNumber)
{
	//if the bullet is in guise 0, set it to 1
	if (globals_getAlienBulletGuise(bulletNumber) == bullet_guise_0)
	{
		globals_setAlienBulletGuise(bulletNumber, bullet_guise_1);
	}
	else //if the bullet is in guise 1, set it to 0
	{
		globals_setAlienBulletGuise(bulletNumber, bullet_guise_0);
	}
}

//Erases an alien bullet given the type, guise, and position (draws it black).
void eraseAlienBullet(bullet_type type, bullet_guise_type guise, point_t location)
{
	if (type == cross_bullet)
	{
		if (guise == bullet_guise_0)
		{
			render_drawObject(crossBulletGuise0_5x6, GLOBALS_CROSS_BULLET_WIDTH, GLOBALS_CROSS_BULLET_HEIGHT, location, GLOBALS_BLACK, GLOBALS_LEAVE_BACKGROUND);
		}
		else // guise 1
		{
			render_drawObject(crossBulletGuise1_5x6, GLOBALS_CROSS_BULLET_WIDTH, GLOBALS_CROSS_BULLET_HEIGHT, location, GLOBALS_BLACK, GLOBALS_LEAVE_BACKGROUND);
		}
	}
	else //zigzag
	{
		if (guise == bullet_guise_0)
		{
			render_drawObject(zigzagBulletGuise0_3x7, GLOBALS_ZIGZAG_BULLET_WIDTH, GLOBALS_ZIGZAG_BULLET_HEIGHT, location, GLOBALS_BLACK, GLOBALS_LEAVE_BACKGROUND);
		}
		else // guise 1
		{
			render_drawObject(zigzagBulletGuise1_3x7, GLOBALS_ZIGZAG_BULLET_WIDTH, GLOBALS_ZIGZAG_BULLET_HEIGHT, location, GLOBALS_BLACK, GLOBALS_LEAVE_BACKGROUND);
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
			render_drawObject(crossBulletGuise0_5x6, GLOBALS_CROSS_BULLET_WIDTH, GLOBALS_CROSS_BULLET_HEIGHT, location, GLOBALS_BULLET_WHITE, GLOBALS_LEAVE_BACKGROUND);
		}
		else // guise 1
		{
			render_drawObject(crossBulletGuise1_5x6, GLOBALS_CROSS_BULLET_WIDTH, GLOBALS_CROSS_BULLET_HEIGHT, location, GLOBALS_BULLET_WHITE, GLOBALS_LEAVE_BACKGROUND);
		}
	}
	else //zigzag
	{
		if (guise == bullet_guise_0)
		{
			render_drawObject(zigzagBulletGuise0_3x7, GLOBALS_ZIGZAG_BULLET_WIDTH, GLOBALS_ZIGZAG_BULLET_HEIGHT, location, GLOBALS_BULLET_WHITE, GLOBALS_LEAVE_BACKGROUND);
		}
		else // guise 1
		{
			render_drawObject(zigzagBulletGuise1_3x7, GLOBALS_ZIGZAG_BULLET_WIDTH, GLOBALS_ZIGZAG_BULLET_HEIGHT, location, GLOBALS_BULLET_WHITE, GLOBALS_LEAVE_BACKGROUND);
		}
	}
}

//When a bullet is fired from an alien, this assigns a free index to it.
//If there are already four bullets on the screen, returns -1.
int8_t assignBulletNumber()
{
	int8_t b;
	for (b = 0; b < GLOBALS_MAX_ALIEN_BULLETS; b++) //check all the bullets
	{
		if (!globals_isBulletActive(b)) //if we find one that's not active
		{
			return b; //new bullet number
		}
	}
	return GLOBALS_ERROR_INDEX; //-1 means all bullets are currently active
}

//Randomly chooses an alien on the bottom row and fires a bullet from that alien.
void bullets_fireRandomAlienBullet()
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
		randCol = rand() % GLOBALS_NUM_ALIEN_COLUMNS;
		//check to see whether there is an alien in this column
		//start with the highest row and go backwards
		for (row = GLOBALS_NUM_ALIEN_ROWS-1; row >= 0; row--)
		{
			//if there's an alien in this row
			if (aliens_isAlienAlive(row, randCol))
			{
				//setAlieninColumn to true and exit the for loop
				alienInColumn = TRUE;
				break;
			}
		}
	}
	//now aliensAlive[row][randCol] contains the alien that will shoot
	//randomly select bullet type
	bullet_type type = rand() % GLOBALS_NUM_BULLET_TYPES;
	point_t spawnPosition = getAlienBulletSpawnPosition(row, randCol);
	drawAlienBullet(type, bullet_guise_0, spawnPosition); 		//draw the bullet just using the first guise

	//save bullet information
	globals_setAlienBulletPosition(bulletNumber, spawnPosition); 		//set position
	globals_setAlienBulletType(bulletNumber, type); 					//set bullet type
	globals_setAlienBulletGuise(bulletNumber, bullet_guise_0); 			//first guise
	globals_setBulletStatus(bulletNumber, TRUE); 						//activate bullet

}

//Given a bullet index, advances the alien bullet on the display.
void advanceOneAlienBullet(int8_t bulletNumber)
{

	//erase bullet
	eraseAlienBullet(globals_getAlienBulletType(bulletNumber), globals_getAlienBulletGuise(bulletNumber), globals_getAlienBulletPosition(bulletNumber));
	//check to see whether the bullet has left the screen
	if (globals_getAlienBulletPosition(bulletNumber).y >= GLOBALS_BOTTOMLINE_TOP - (GLOBALS_ZIGZAG_BULLET_HEIGHT+BULLETS_ALIEN_BULLET_DEACTIVATE_BUFFER)*GLOBALS_MAGNIFY_MULT)
	{
		//deactivate the bullet
		globals_setBulletStatus(bulletNumber, FALSE);
	}
	else
	{
		//switch guises
		switchAlienBulletGuise(bulletNumber);
		//change the position of the bullet
		point_t newAlienBulletPosition = {globals_getAlienBulletPosition(bulletNumber).x, globals_getAlienBulletPosition(bulletNumber).y + BULLETS_ALIEN_BULLET_TRAVEL_DISTANCE};
		//redraw the alien bullet
		drawAlienBullet(globals_getAlienBulletType(bulletNumber), globals_getAlienBulletGuise(bulletNumber), newAlienBulletPosition);
		//set new alien bullet position globally
		globals_setAlienBulletPosition(bulletNumber, newAlienBulletPosition);
	}
}

//Advances all alien bullets on the display.
void bullets_advanceAllAlienBullets()
{
	//check to see whether each bullet is active
	//advance that bullet
	uint8_t i;
	for (i = 0; i < GLOBALS_MAX_ALIEN_BULLETS; i++)
	{
		if (globals_isBulletActive(i))
		{
			//draw the bullet
			advanceOneAlienBullet(i);
		}
	}
}

//returns the pixel that is the specified color in the given area. Returns -10, -10 if none found. If findLowest is true it will return the lowest matching pixel
point_t colorExistsInArea(point_t startPoint, uint8_t width, uint8_t height, uint32_t color, uint8_t findLowest)
{
	uint16_t r, c;
	unsigned int * framePointer = render_getFramePointer0();
	point_t colorPixel; //the point where the color is found
	colorPixel = (point_t) {NO_PIXEL, NO_PIXEL}; //initialized to none found
	for (r = startPoint.y; r < (startPoint.y + height); r = r + GLOBALS_MAGNIFY_MULT)
	{
		for (c = startPoint.x; c < (startPoint.x + width); c = c + GLOBALS_MAGNIFY_MULT)
		{
			if (framePointer[r*GLOBALS_WIDTH_DISPLAY + c] == color)
			{
				colorPixel = (point_t) {c, r};
				if (!findLowest)
					return colorPixel; //return the point where the color was found
			}
		}
	}
	return colorPixel; //returns the last pixel found, or -10, -10 if none found
}


//if the tank bullet will hit an alien on its next move, this will return the alien number. Otherwise it will return -1.
int8_t bullets_tankBulletWillHitAlien()
{
	point_t newTankBulletPosition = {bullets_getTankBulletPosition().x, bullets_getTankBulletPosition().y - GLOBALS_TANK_BULLET_TRAVEL_DISTANCE}; //where the bullet will be
	point_t collisionPoint = colorExistsInArea(newTankBulletPosition, GLOBALS_TANK_BULLET_WIDTH*GLOBALS_MAGNIFY_MULT, GLOBALS_TANK_BULLET_TRAVEL_DISTANCE, GLOBALS_WHITE, FALSE); //check if we'll hit an alien
	if (collisionPoint.x > NO_PIXEL && collisionPoint.y > NO_PIXEL) //if the tank bullet is going to hit an alien
	{
		return aliens_getAlienNumberFromPoint(collisionPoint); //return the alien number that will get hit
	}
	return BULLETS_NO_HIT; //no alien will be hit
}

//returns true if the tank bullet will hit the spaceship on its next move
uint8_t bullets_tankBulletWillHitSaucer()
{
	point_t newTankBulletPosition = {bullets_getTankBulletPosition().x, bullets_getTankBulletPosition().y - GLOBALS_TANK_BULLET_TRAVEL_DISTANCE};
	point_t collisionPoint = colorExistsInArea(newTankBulletPosition, GLOBALS_TANK_BULLET_WIDTH, GLOBALS_TANK_BULLET_TRAVEL_DISTANCE, GLOBALS_RED, FALSE); //check if we'll hit the spaceship
	if (collisionPoint.x > NO_PIXEL && collisionPoint.y > NO_PIXEL) //if the tank bullet is going to hit the saucer
	{
		return TRUE;
	}
	else return FALSE;

}

//if the tank bullet will hit a bunker on its next move, this will return the bunker number. Otherwise it will return -1.
int8_t bullets_tankBulletWillHitBunker()
{
	point_t newTankBulletPosition = {bullets_getTankBulletPosition().x, bullets_getTankBulletPosition().y - GLOBALS_TANK_BULLET_TRAVEL_DISTANCE};
	point_t collisionPoint = colorExistsInArea(newTankBulletPosition, GLOBALS_TANK_BULLET_WIDTH*GLOBALS_MAGNIFY_MULT, GLOBALS_TANK_BULLET_TRAVEL_DISTANCE, GLOBALS_GREEN, TRUE); //check if we'll hit a bunker
	if (collisionPoint.x > NO_PIXEL && collisionPoint.y > NO_PIXEL) //if the tank bullet is going to hit a bunker
	{
		return bunkers_getBunkerBlockNumber(collisionPoint); //return the block number that is going to get hit
	}
	return BULLETS_NO_HIT;
}

//returns true if the specified alien bullet will hit the tank on its next move
uint8_t bullets_alienBulletWillHitTank(uint8_t bulletNum)
{
	uint16_t alien_bullet_width = (globals_getAlienBulletType(bulletNum) == cross_bullet) ? GLOBALS_CROSS_BULLET_WIDTH : GLOBALS_ZIGZAG_BULLET_WIDTH;
	point_t newAlienBulletPosition = {globals_getAlienBulletPosition(bulletNum).x, globals_getAlienBulletPosition(bulletNum).y + BULLETS_ALIEN_BULLET_TRAVEL_DISTANCE};
	point_t collisionPoint = colorExistsInArea(newAlienBulletPosition, alien_bullet_width, BULLETS_ALIEN_BULLET_TRAVEL_DISTANCE, GLOBALS_GREEN, FALSE); //check if we'll hit the tank or a bunker

	//if the green point is below the top of the tank and above the green line on the bottom of the screen
	if (collisionPoint.y >= GLOBALS_TANK_START_Y && collisionPoint.y < GLOBALS_BOTTOMLINE_TOP)
	{
		return TRUE; //it must be the tank
	}
	else return FALSE;
}


//if the specified alien bullet will hit a bunker on its next move, this will return the bunker block number. Otherwise it will return -1.
int8_t bullets_alienBulletWillHitBunkerBlock(uint8_t bulletNum)
{
	uint16_t alien_bullet_width = (globals_getAlienBulletType(bulletNum) == cross_bullet) ? GLOBALS_CROSS_BULLET_WIDTH : GLOBALS_ZIGZAG_BULLET_WIDTH;
	point_t newAlienBulletPosition = {globals_getAlienBulletPosition(bulletNum).x, globals_getAlienBulletPosition(bulletNum).y + BULLETS_ALIEN_BULLET_TRAVEL_DISTANCE};
	point_t collisionPoint = colorExistsInArea(newAlienBulletPosition, alien_bullet_width, BULLETS_ALIEN_BULLET_TRAVEL_DISTANCE, GLOBALS_GREEN, FALSE); //check if we'll hit the tank or a bunker
	if (collisionPoint.y < GLOBALS_TANK_START_Y) //if the green point is above the tank then we're hitting a bunker, not the tank
	{
		return bunkers_getBunkerBlockNumber(collisionPoint); //return the block number that is going to get hit
	}
	else return BULLETS_NO_HIT;
}



