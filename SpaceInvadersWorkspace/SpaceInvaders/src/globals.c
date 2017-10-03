/*
 * globals.c
 *
 *  Created on: Sep 22, 2017
 *      Author: superman
 */

#include "globals.h"
#include "bitmaps.h"
#include "render.h"

// Here are the globals.
static uint16_t tankPosition;
static point_t tankBulletPosition;


#define NUM_BUNKER_BLOCKS 10
static uint8_t bunker0State[NUM_BUNKER_BLOCKS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
static uint8_t bunker1State[NUM_BUNKER_BLOCKS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
static uint8_t bunker2State[NUM_BUNKER_BLOCKS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
static uint8_t bunker3State[NUM_BUNKER_BLOCKS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

static uint16_t currentScore = 0;




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





void fireRandomAlienMissile()
{

}
void updateBulletPositions()
{

}

uint16_t getCurrentScore() {return currentScore;}

void setScore(uint16_t score) {currentScore = score;}
