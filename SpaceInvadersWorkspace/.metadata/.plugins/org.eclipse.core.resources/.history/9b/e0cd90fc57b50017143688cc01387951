/*
 * saucer.h
 *
 *  Created on: Oct 13, 2017
 *      Author: superman
 */

#ifndef SAUCER_H_
#define SAUCER_H_
#include "globals.h"

/////////////////////// DEFINES /////////////////////
#define SAUCER_POSITION_Y 60 //The y coord of the saucer's upper right corner
#define SAUCER_WIDTH 16
#define SAUCER_HEIGHT 7

/////////////////////// FUNCTIONS ///////////////////
//Draws the saucer at the global position
void drawSaucer();
//Moves the saucer right
void moveSaucerRight();
//Moves the saucer left
void moveSaucerLeft();
//switches directions for the saucer
void switchSaucerMoveDirection();
//returns the current move direction of the saucer
saucer_direction_type getSaucerDirection();
//Sets the position and draws the saucer if it's going to the left
void initSaucerMovingLeft();
//Sets the position and draws the saucer if it's going to the right
void initSaucerMovingRight();
//erases the saucer
void eraseSaucer();
//print the saucer score
void printScoreOnSaucerDeath(uint16_t newScore, uint32_t color);


#endif /* SAUCER_H_ */
