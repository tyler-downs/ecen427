/*
 * saucer.c
 *
 *  Created on: Oct 13, 2017
 *      Author: superman
 */
#include "saucer.h"
#include "render.h"
#include "globals.h"

//////////////////////// GLOBAL VARIABLES ///////////////////
static saucer_direction_type saucerDirection = saucer_moves_left;

#define SAUCER_WIDTH 16
#define SAUCER_HEIGHT 7
////////////////////////// FUNCTIONS ////////////////////////
void drawSaucer()
{
	drawObject(saucer_16x7, SAUCER_WIDTH, SAUCER_HEIGHT, (point_t){getSaucerPosition(), SAUCER_POSITION_Y}, RED, FORCE_BLACK_BACKGROUND);
}



#define SAUCER_MOVE_PIXELS (3 * MAGNIFY_MULT)
//Moves the saucer right
void moveSaucerRight()
{
	//erase the rectangle
	eraseRectangle((point_t) {getSaucerPosition(), SAUCER_POSITION_Y}, SAUCER_MOVE_PIXELS, SAUCER_HEIGHT);
	//change the start point of the saucer
	uint16_t newSaucerPosition = getSaucerPosition() + SAUCER_MOVE_PIXELS;
	setSaucerPosition(newSaucerPosition);
	//draw the saucer
	drawObject(saucer_16x7, SAUCER_WIDTH, SAUCER_HEIGHT, (point_t){newSaucerPosition, SAUCER_POSITION_Y}, RED, FORCE_BLACK_BACKGROUND);
}

//Moves the saucer left
void moveSaucerLeft()
{
	//erase the rectangle
	eraseRectangle((point_t) {getSaucerPosition() + SAUCER_WIDTH + SAUCER_MOVE_PIXELS, SAUCER_POSITION_Y}, SAUCER_MOVE_PIXELS, SAUCER_HEIGHT);
	//change the start point of the saucer
	uint16_t newSaucerPosition = getSaucerPosition() - SAUCER_MOVE_PIXELS;
	setSaucerPosition(newSaucerPosition);
	//draw the saucer
	drawObject(saucer_16x7, SAUCER_WIDTH, SAUCER_HEIGHT, (point_t){newSaucerPosition, SAUCER_POSITION_Y}, RED, FORCE_BLACK_BACKGROUND);
}
