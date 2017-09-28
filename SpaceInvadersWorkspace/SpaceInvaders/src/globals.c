/*
 * globals.c
 *
 *  Created on: Sep 22, 2017
 *      Author: superman
 */

#include "globals.h"

// Here are the globals.
static uint16_t tankPosition;
static point_t tankBulletPosition;
static point_t alienBlockPosition;

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

void setAlienBlockPosition(point_t val)
{

}

point_t getAlienBlockPosition()
{

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

void moveTankLeft()
{

}

void moveTankRight()
{

}

void moveAliens()
{

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
