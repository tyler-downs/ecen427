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


static bullet_type alienBulletTypes[MAX_ALIEN_BULLETS];
static bullet_guise_type alienBulletGuises[MAX_ALIEN_BULLETS];
static point_t alienBulletPositions[MAX_ALIEN_BULLETS];
static uint8_t bulletsActive[MAX_ALIEN_BULLETS] = {0, 0, 0, 0};

#define NUM_BUNKER_BLOCKS 10
static uint8_t bunker0State[NUM_BUNKER_BLOCKS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
static uint8_t bunker1State[NUM_BUNKER_BLOCKS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
static uint8_t bunker2State[NUM_BUNKER_BLOCKS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
static uint8_t bunker3State[NUM_BUNKER_BLOCKS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

static uint16_t currentScore = 0;

uint8_t isBulletActive(uint8_t bulletNumber)
{
	return bulletsActive[bulletNumber];
}
void setBulletStatus(uint8_t bulletNumber, uint8_t active)
{
	bulletsActive[bulletNumber] = active;
}

void setAlienBulletPosition(uint8_t bulletNum, point_t val)
{
	alienBulletPositions[bulletNum] = val;
}
point_t getAlienBulletPosition(uint8_t bulletNum) {return alienBulletPositions[bulletNum]; }

void setAlienBulletType(uint8_t bulletNum, bullet_type type)
{
	alienBulletTypes[bulletNum] = type;
}
bullet_type getAlienBulletType(uint8_t bulletNum) { return alienBulletTypes[bulletNum]; }

void setAlienBulletGuise(uint8_t bulletNum, bullet_guise_type guise)
{
	alienBulletGuises[bulletNum] = guise;
}
bullet_guise_type getAlienBulletGuise(uint8_t bulletNum) { return alienBulletGuises[bulletNum]; }

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
		drawObject(tank_15x8, TANK_WIDTH, TANK_HEIGHT, (point_t){newTankPosition, TANK_START_Y}, GREEN, FORCE_BLACK_BACKGROUND);

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
		drawObject(tank_15x8, TANK_WIDTH, TANK_HEIGHT, (point_t){newTankPosition, TANK_START_Y}, GREEN, FORCE_BLACK_BACKGROUND);
	}
}








void advanceAllBullets()
{
	advanceTankBullet();
	advanceAllAlienBullets();
}

uint16_t getCurrentScore() {return currentScore;}

void setScore(uint16_t score) {currentScore = score;}
