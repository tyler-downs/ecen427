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
#define ERROR_INDEX -1
#define SCREEN_EDGE_BUMPER_PIXELS 10


//////////// VARIABLES AND ENUMS //////////////////
static alien_guise_type currentAlienGuise = alien_guise_out; //initialize alien guise to out
static alien_direction_type currentAlienDirection = aliens_move_right; //initialize alien crawl direction to right

//array for aliens alive (row, column)
static uint8_t aliensAlive[NUM_ALIEN_ROWS][NUM_ALIEN_COLUMNS] = \
		{{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};


//////////// FUNCTION PROTOTYPES /////////////////

void setAlienBlockPosition(point_t val);

point_t getAlienBlockPosition();

void moveAliens();

void killAlien(uint8_t alien);

int8_t getLeftmostLivingAlienColumn();

int8_t getRightmostLivingAlienColumn();

void fireRandomAlienMissile();





#endif /* ALIENS_H_ */
