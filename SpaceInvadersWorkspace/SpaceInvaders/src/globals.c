/*
 * globals.c
 *
 *  Created on: Sep 22, 2017
 *      Author: superman
 */

#include "globals.h"
#include "bitmaps.h"
#include "render.h"
#include "bullets.h"
#include "counters.h"

//////////////////////// GLOBAL VARIABLES ///////////////////////////////
static uint16_t tankPosition; // The current x-coordinate of the tank
static point_t tankBulletPosition; //The current position of the tank bullet
static bullet_type alienBulletTypes[GLOBALS_MAX_ALIEN_BULLETS]; //the types of each alien bullet
static bullet_guise_type alienBulletGuises[GLOBALS_MAX_ALIEN_BULLETS]; //the guises of each alien bullet
static point_t alienBulletPositions[GLOBALS_MAX_ALIEN_BULLETS]; //the positions of each alien bullet
static uint8_t bulletsActive[GLOBALS_MAX_ALIEN_BULLETS] = {0, 0, 0, 0}; //bools to indicate which alien bullets are active
static dead_tank_guise_type deadTankGuise = dead_tank_guise_0; //default guise for the dead tank
static int16_t saucerPosition; //The current x-coord of the saucer

//Arrays for storing the state of each block in each bunker
static uint8_t bunker0State[GLOBALS_NUM_BUNKER_BLOCKS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
static uint8_t bunker1State[GLOBALS_NUM_BUNKER_BLOCKS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
static uint8_t bunker2State[GLOBALS_NUM_BUNKER_BLOCKS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
static uint8_t bunker3State[GLOBALS_NUM_BUNKER_BLOCKS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
static uint8_t lives = 0;
//Global variable for the current score
static uint16_t currentScore = 0;


////////////////////////// FUNCTIONS //////////////////////////////////
//Returns the current guise of the dead tank
dead_tank_guise_type globals_getDeadTankGuise()
{
	return deadTankGuise;
}

//Sets the dead tank guise type to the given value
void globals_setDeadTankGuise(dead_tank_guise_type guise)
{
	deadTankGuise = guise;
}

//Returns the value of the global saucer position x-coord
int16_t globals_getSaucerPosition(){
	return saucerPosition;
}

//Sets the position of the saucer to the given value
void globals_setSaucerPosition(int16_t position){
	saucerPosition = position;
}


//Given the alien bullet number, returns whether that bullet is active
uint8_t globals_isBulletActive(uint8_t bulletNumber)
{
	return bulletsActive[bulletNumber];
}

//Sets a given alien bullet to active or inactive
void globals_setBulletStatus(uint8_t bulletNumber, uint8_t active)
{
	bulletsActive[bulletNumber] = active;
}

//Sets a given alien bullet's position
void globals_setAlienBulletPosition(uint8_t bulletNum, point_t val)
{
	alienBulletPositions[bulletNum] = val;
}

//Returns the position of the given bullet
point_t globals_getAlienBulletPosition(uint8_t bulletNum) {return alienBulletPositions[bulletNum]; }

//Sets the given bullet to the given type
void globals_setAlienBulletType(uint8_t bulletNum, bullet_type type)
{
	alienBulletTypes[bulletNum] = type;
}

//Returns the type of the given bullet
bullet_type globals_getAlienBulletType(uint8_t bulletNum) { return alienBulletTypes[bulletNum]; }

//Sets the given bullet to the given guise
void globals_setAlienBulletGuise(uint8_t bulletNum, bullet_guise_type guise)
{
	alienBulletGuises[bulletNum] = guise;
}

//Returns the guise for the given bullet
bullet_guise_type globals_getAlienBulletGuise(uint8_t bulletNum) { return alienBulletGuises[bulletNum]; }

//Sets the tank x coord to a given value
void globals_setTankPosition(uint16_t val) {
  tankPosition = val;
}

//Returns the tank x coord
uint16_t globals_getTankPosition() {
  return tankPosition;
}

//Sets the position of the tank bullet to the given value
void bullets_setTankBulletPosition(point_t val) {
  tankBulletPosition.x = val.x;
  tankBulletPosition.y = val.y;
}

//Returns the position of the tank bullet
point_t bullets_getTankBulletPosition() {
  return tankBulletPosition;
}

//Moves the tank one increment right. Handles screen edge issues.
void globals_moveTankRight()
{
	if (globals_getTankPosition() < GLOBALS_TANK_SCREEN_EDGE_RIGHT)
	{
		//erase the rectangle
		render_eraseRectangle((point_t){globals_getTankPosition(), GLOBALS_TANK_START_Y}, GLOBALS_TANK_MOVE_PIXELS, GLOBALS_TANK_HEIGHT);
		//change the start point of the tank
		uint16_t newTankPosition = globals_getTankPosition() + GLOBALS_TANK_MOVE_PIXELS;
		globals_setTankPosition(newTankPosition);
		//draw the tank
		render_drawObject(tank_15x8, GLOBALS_TANK_WIDTH, GLOBALS_TANK_HEIGHT, (point_t){newTankPosition, GLOBALS_TANK_START_Y}, GLOBALS_GREEN, GLOBALS_FORCE_BLACK_BACKGROUND);
	}

}

//Moves the tank one increment left. Handles screen edge issues.
void globals_moveTankLeft()
{
	if (globals_getTankPosition() > GLOBALS_TANK_SCREEN_EDGE_LEFT)
	{
		//erase the rectangle
		render_eraseRectangle((point_t){globals_getTankPosition() + GLOBALS_TANK_WIDTH*GLOBALS_MAGNIFY_MULT - GLOBALS_TANK_MOVE_PIXELS, GLOBALS_TANK_START_Y}, GLOBALS_TANK_MOVE_PIXELS, GLOBALS_TANK_HEIGHT);
		//change the start point of the tank
		uint16_t newTankPosition = globals_getTankPosition() - GLOBALS_TANK_MOVE_PIXELS;
		globals_setTankPosition(newTankPosition);
		//draw the tank
		render_drawObject(tank_15x8, GLOBALS_TANK_WIDTH, GLOBALS_TANK_HEIGHT, (point_t){newTankPosition, GLOBALS_TANK_START_Y}, GLOBALS_GREEN, GLOBALS_FORCE_BLACK_BACKGROUND);
	}
}


//Advances all the bullets on the screen
void globals_advanceAllBullets()
{
	bullets_advanceTankBullet();
	bullets_advanceAllAlienBullets();
}

//Returns the current score
uint16_t globals_getCurrentScore() {return currentScore;}

//Sets the score to the given value
void globals_setScore(uint16_t score) {currentScore = score;}

//increments the score to the provided value, and updates the score on the screen
void globals_incrementScore(uint16_t plus)
{
	currentScore = globals_getCurrentScore() + plus; //update global
	render_updateScoreDisplay(currentScore); //update display
}

//pass in 1 or -1 to increment or decrement the number of lives
void globals_updateLives(uint8_t incDec)
{
	lives += incDec;
}
uint8_t globals_getNumLives() {return lives;}

//end the game
void globals_gameOver()
{
	xil_printf("GAME OVER!!\n\r");
	render_drawGameOverScreen(GLOBALS_RED);
	counters_setGameOverState();
}

//the player beat the level
void globals_levelCleared()
{
	xil_printf("LEVEL CLEARED!\n\r");
}
