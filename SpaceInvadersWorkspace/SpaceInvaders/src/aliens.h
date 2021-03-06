/*
 * aliens.h
 *
 *  Created on: Oct 3, 2017
 *      Author: superman
 */

#ifndef ALIENS_H_
#define ALIENS_H_
#include "globals.h"
#include "render.h"

///////////// DEFINES /////////////////////////////
#define ALIENS_SCREEN_EDGE_BUMPER_PIXELS 10 //The number of pixels that acts as a buffer when the aliens reach the screen edge
#define ALIENS_MOVE_PIXELS 6 				//The amount the aliens move with each step
#define ALIENS_TOP_ALIEN_POINTS 40 			//The point worth of the top aliens
#define ALIENS_MIDDLE_ALIEN_POINTS 20		//The point worth of the middle aliens
#define ALIENS_BOTTOM_ALIEN_POINTS 10		//The point worth of the bottom aliens
#define ALIENS_HALF_ALIEN (GLOBALS_ALIEN_WIDTH / 2)		//Half the width of an alien


//////////// FUNCTION PROTOTYPES /////////////////

//Sets the globally accessible alien block origin position given a point_t
void aliens_setAlienBlockPosition(point_t val);

//Returns the value of the globally accessible alien block position
point_t aliens_getAlienBlockPosition();

//Moves all living aliens one step. Handles moving down rows, switching directions, etc.
void aliens_moveAliens();

//Given a number between 0-54, kills the corresponding alien
void aliens_killAlien(uint8_t alien);

//returns the location of the alien
point_t aliens_getAlienLocation(uint8_t alienNum);

//Returns the index of the leftmost living column of aliens
int8_t aliens_getLeftmostLivingAlienColumn();

//Returns the index of the leftmost living column of aliens
int8_t aliens_getRightmostLivingAlienColumn();

//Given a row and column, accesses aliensAlive array and returns whether
//corresponding alien is alive or not
uint8_t aliens_isAlienAlive(uint8_t row, uint8_t col);

//returns the alien number that has a pixel at the provided point
uint8_t aliens_getAlienNumberFromPoint(point_t point);

//returns how many points the alien is worth
uint8_t aliens_alienPoints(uint8_t alienNum);

//Revives all of the aliens in the array to 1
void aliens_reviveAllAliens();

//Returns the y-coord of the bottom of the living alien block
int16_t aliens_getBottomOfAliens();

//Prints the aliensAlive array to the console. Used in debugging.
void aliens_printAliens();

//Erases all aliens from the screen. Does not kill them. Used for debugging.
void aliens_eraseAllAliens();

#endif /* ALIENS_H_ */
