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

//////////////////////// GLOBAL VARIABLES ///////////////////////////////
static uint16_t tankPosition; // The current x-coordinate of the tank
static point_t tankBulletPosition; //The current position of the tank bullet
static bullet_type alienBulletTypes[MAX_ALIEN_BULLETS]; //the types of each alien bullet
static bullet_guise_type alienBulletGuises[MAX_ALIEN_BULLETS]; //the guises of each alien bullet
static point_t alienBulletPositions[MAX_ALIEN_BULLETS]; //the positions of each alien bullet
static uint8_t bulletsActive[MAX_ALIEN_BULLETS] = {0, 0, 0, 0}; //bools to indicate which alien bullets are active
static dead_tank_guise_type deadTankGuise = dead_tank_guise_0; //default guise for the dead tank
static int16_t saucerPosition; //The current x-coord of the saucer

//Arrays for storing the state of each block in each bunker
static uint8_t bunker0State[NUM_BUNKER_BLOCKS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
static uint8_t bunker1State[NUM_BUNKER_BLOCKS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
static uint8_t bunker2State[NUM_BUNKER_BLOCKS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
static uint8_t bunker3State[NUM_BUNKER_BLOCKS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
static uint8_t lives = 0;
//Global variable for the current score
static uint16_t currentScore = 0;


////////////////////////// FUNCTIONS //////////////////////////////////
//Returns the current guise of the dead tank
dead_tank_guise_type getDeadTankGuise()
{
	return deadTankGuise;
}

//Sets the dead tank guise type to the given value
void setDeadTankGuise(dead_tank_guise_type guise)
{
	deadTankGuise = guise;
}

//Returns the value of the global saucer position x-coord
int16_t getSaucerPosition(){
	return saucerPosition;
}

//Sets the position of the saucer to the given value
void setSaucerPosition(int16_t position){
	saucerPosition = position;
}


//Given the alien bullet number, returns whether that bullet is active
uint8_t isBulletActive(uint8_t bulletNumber)
{
	return bulletsActive[bulletNumber];
}

//Sets a given alien bullet to active or inactive
void setBulletStatus(uint8_t bulletNumber, uint8_t active)
{
	bulletsActive[bulletNumber] = active;
}

//Sets a given alien bullet's position
void setAlienBulletPosition(uint8_t bulletNum, point_t val)
{
	alienBulletPositions[bulletNum] = val;
}

//Returns the position of the given bullet
point_t getAlienBulletPosition(uint8_t bulletNum) {return alienBulletPositions[bulletNum]; }

//Sets the given bullet to the given type
void setAlienBulletType(uint8_t bulletNum, bullet_type type)
{
	alienBulletTypes[bulletNum] = type;
}

//Returns the type of the given bullet
bullet_type getAlienBulletType(uint8_t bulletNum) { return alienBulletTypes[bulletNum]; }

//Sets the given bullet to the given guise
void setAlienBulletGuise(uint8_t bulletNum, bullet_guise_type guise)
{
	alienBulletGuises[bulletNum] = guise;
}

//Returns the guise for the given bullet
bullet_guise_type getAlienBulletGuise(uint8_t bulletNum) { return alienBulletGuises[bulletNum]; }

//Sets the tank x coord to a given value
void setTankPosition(uint16_t val) {
  tankPosition = val;
}

//Returns the tank x coord
uint16_t getTankPosition() {
  return tankPosition;
}

//Sets the position of the tank bullet to the given value
void setTankBulletPosition(point_t val) {
  tankBulletPosition.x = val.x;
  tankBulletPosition.y = val.y;
}

//Returns the position of the tank bullet
point_t getTankBulletPosition() {
  return tankBulletPosition;
}

//Moves the tank one increment right. Handles screen edge issues.
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

//Moves the tank one increment left. Handles screen edge issues.
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


//Advances all the bullets on the screen
void advanceAllBullets()
{
	advanceTankBullet();
	advanceAllAlienBullets();
}

//Returns the current score
uint16_t getCurrentScore() {return currentScore;}

//Sets the score to the given value
void setScore(uint16_t score) {currentScore = score;}

//increments the score to the provided value, and updates the score on the screen
void incrementScore(uint16_t plus)
{
	currentScore = getCurrentScore() + plus; //update global
	updateScoreDisplay(currentScore); //update display
}

//pass in 1 or -1 to increment or decrement the number of lives
void updateLives(uint8_t incDec)
{
	lives += incDec;
}
uint8_t getNumLives() {return lives;}

//end the game
void gameOver()
{
	xil_printf("GAME OVER!!\n\r");
	//exit(0);
}

//the player beat the level
void levelCleared()
{
	xil_printf("LEVEL CLEARED!\n\r");
}
