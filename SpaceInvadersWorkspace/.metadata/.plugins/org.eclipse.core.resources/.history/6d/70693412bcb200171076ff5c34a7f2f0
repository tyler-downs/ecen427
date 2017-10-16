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
#define SCREEN_EDGE_BUMPER_PIXELS 10 //The number of pixels that acts as a buffer when the aliens reach the screen edge
#define ALIEN_MOVE_PIXELS TANK_MOVE_PIXELS //The amount the aliens move with each step


//////////// FUNCTION PROTOTYPES /////////////////

//Sets the globally accessible alien block origin position given a point_t
void setAlienBlockPosition(point_t val);

//Returns the value of the globally accessible alien block position
point_t getAlienBlockPosition();

//Moves all living aliens one step. Handles moving down rows, switching directions, etc.
void moveAliens();

//Given a number between 0-54, kills the corresponding alien
void killAlien(uint8_t alien);

//Returns the index of the leftmost living column of aliens
int8_t getLeftmostLivingAlienColumn();

//Returns the index of the leftmost living column of aliens
int8_t getRightmostLivingAlienColumn();

//Given a row and column, accesses aliensAlive array and returns whether
//corresponding alien is alive or not
uint8_t isAlienAlive(uint8_t row, uint8_t col);

//Prints the aliensAlive array to the console. Used in debugging.
void printAliens();


#endif /* ALIENS_H_ */
