/*
 * saucer.c
 *
 *  Created on: Oct 13, 2017
 *      Author: superman
 */
#include "saucer.h"
#include "render.h"
////////////////////////// DEFINES //////////////////////////
#define SAUCER_SCORE_MAX_INDEX 5	//used in updating the score
#define SAUCER_SCORE_DIVISOR 10  	//used in finding the digits for the score
#define SAUCER_MOVE_PIXELS 3		//Number of pixels the saucer moves


//////////////////////// GLOBAL VARIABLES ///////////////////
static saucer_direction_type saucerDirection = saucer_moves_left; //the current direction of the saucer


////////////////////////// FUNCTIONS ////////////////////////

//Draws the saucer red
void saucer_drawSaucer()
{
	render_drawObject(saucer_16x7, SAUCER_WIDTH, SAUCER_HEIGHT, (point_t){globals_getSaucerPosition(), SAUCER_POSITION_Y}, GLOBALS_RED, GLOBALS_FORCE_BLACK_BACKGROUND);
}

//Erases the saucer black
void saucer_eraseSaucer()
{
	render_drawObject(saucer_16x7, SAUCER_WIDTH, SAUCER_HEIGHT, (point_t){globals_getSaucerPosition(), SAUCER_POSITION_Y}, GLOBALS_BLACK, GLOBALS_FORCE_BLACK_BACKGROUND);
}

//Sets the position and draws the saucer if it's going to the right
void saucer_initSaucerMovingRight()
{
	//set the position
	globals_setSaucerPosition((int16_t)(SAUCER_WIDTH * -1));
	//draw the saucer there
	saucer_drawSaucer();
}

//Sets the position and draws the saucer if it's going to the left
void saucer_initSaucerMovingLeft()
{
	//set the position
	globals_setSaucerPosition((int16_t) GLOBALS_WIDTH_DISPLAY);
	//draw the saucer there
	saucer_drawSaucer();
}

//Moves the saucer right
void saucer_moveSaucerRight()
{
	//erase the rectangle
	render_eraseRectangle((point_t) {globals_getSaucerPosition(), SAUCER_POSITION_Y}, SAUCER_MOVE_PIXELS, SAUCER_HEIGHT);
	//change the start point of the saucer
	int16_t newSaucerPosition = globals_getSaucerPosition() + SAUCER_MOVE_PIXELS;
	globals_setSaucerPosition(newSaucerPosition);
	//draw the saucer
	render_drawObject(saucer_16x7, SAUCER_WIDTH, SAUCER_HEIGHT, (point_t){newSaucerPosition, SAUCER_POSITION_Y}, GLOBALS_RED, GLOBALS_FORCE_BLACK_BACKGROUND);
}

//Moves the saucer left
void saucer_moveSaucerLeft()
{
	//erase the rectangle
	render_eraseRectangle((point_t) {globals_getSaucerPosition() + SAUCER_WIDTH*2 - SAUCER_MOVE_PIXELS, SAUCER_POSITION_Y}, SAUCER_MOVE_PIXELS*2, SAUCER_HEIGHT);
	//change the start point of the saucer
	int16_t newSaucerPosition = globals_getSaucerPosition() - SAUCER_MOVE_PIXELS;
	globals_setSaucerPosition(newSaucerPosition);
	//draw the saucer
	render_drawObject(saucer_16x7, SAUCER_WIDTH, SAUCER_HEIGHT, (point_t){newSaucerPosition, SAUCER_POSITION_Y}, GLOBALS_RED, GLOBALS_FORCE_BLACK_BACKGROUND);
}

//Switches the direction the saucer is moving
void saucer_switchSaucerMoveDirection()
{
	//if they're going left, move them right
	if (saucerDirection == saucer_moves_left)
	{
		saucerDirection = saucer_moves_right;
	}
	else //if theyre going right, move them left
	{
		saucerDirection = saucer_moves_left;
	}
}

//returns the current move direction of the saucer
saucer_direction_type saucer_getSaucerDirection()
{
	return saucerDirection;
}

//Prints the random score when the saucer is killed
void saucer_printScoreOnSaucerDeath(uint16_t newScore, uint32_t color)
{
	char updatedScore[RENDER_MAX_SCORE_DIGITS] = {'0', '0', '0', '0', '0', '0'}; //initialize the score char array

	//convert the integer score into a char array
	int16_t i = 0;
	for (i = SAUCER_SCORE_MAX_INDEX; i >= 0; i--)
	{
		updatedScore[i] = (char) ((newScore % SAUCER_SCORE_DIVISOR) + '0');
		newScore /= SAUCER_SCORE_DIVISOR;
	}
	//determine the first digit to display (we don't want leading zeros)
	uint16_t m, firstNonzero = RENDER_MAX_SCORE_DIGITS-1;
	for (m = 0 ; m < RENDER_MAX_SCORE_DIGITS; m++)
	{
		if (updatedScore[m] != '0')
		{
			firstNonzero = m;
			break;
		}
	}
	uint16_t k;
	uint16_t x;
	//write each digit to the screen
	for (k = firstNonzero; k < RENDER_MAX_SCORE_DIGITS; k++)
	{
		x = globals_getSaucerPosition() + (k-firstNonzero)*(RENDER_DIGIT_WIDTH*GLOBALS_MAGNIFY_MULT);
		switch(updatedScore[k])
		{
		case '0':
			render_drawObject(zero_5x5, RENDER_DIGIT_WIDTH, RENDER_DIGIT_HEIGHT, (point_t) {x, SAUCER_POSITION_Y}, color, GLOBALS_FORCE_BLACK_BACKGROUND);
			break;
		case '1':
			render_drawObject(one_5x5, RENDER_ONE_WIDTH, RENDER_DIGIT_HEIGHT, (point_t) {x, SAUCER_POSITION_Y}, color, GLOBALS_FORCE_BLACK_BACKGROUND);
			break;
		case '2':
			render_drawObject(two_5x5, RENDER_ONE_WIDTH, RENDER_DIGIT_HEIGHT, (point_t) {x, SAUCER_POSITION_Y}, color, GLOBALS_FORCE_BLACK_BACKGROUND);
			break;
		case '3':
			render_drawObject(three_5x5, RENDER_ONE_WIDTH, RENDER_DIGIT_HEIGHT, (point_t) {x, SAUCER_POSITION_Y}, color, GLOBALS_FORCE_BLACK_BACKGROUND);
			break;
		case '4':
			render_drawObject(four_5x5, RENDER_ONE_WIDTH, RENDER_DIGIT_HEIGHT, (point_t) {x, SAUCER_POSITION_Y}, color, GLOBALS_FORCE_BLACK_BACKGROUND);
			break;
		case '5':
			render_drawObject(five_5x5, RENDER_ONE_WIDTH, RENDER_DIGIT_HEIGHT, (point_t) {x, SAUCER_POSITION_Y}, color, GLOBALS_FORCE_BLACK_BACKGROUND);
			break;
		case '6':
			render_drawObject(six_5x5, RENDER_ONE_WIDTH, RENDER_DIGIT_HEIGHT, (point_t) {x, SAUCER_POSITION_Y}, color, GLOBALS_FORCE_BLACK_BACKGROUND);
			break;
		case '7':
			render_drawObject(seven_5x5, RENDER_ONE_WIDTH, RENDER_DIGIT_HEIGHT, (point_t) {x, SAUCER_POSITION_Y}, color, GLOBALS_FORCE_BLACK_BACKGROUND);
			break;
		case '8':
			render_drawObject(eight_5x5, RENDER_ONE_WIDTH, RENDER_DIGIT_HEIGHT, (point_t) {x, SAUCER_POSITION_Y}, color, GLOBALS_FORCE_BLACK_BACKGROUND);
			break;
		case '9':
			render_drawObject(nine_5x5, RENDER_ONE_WIDTH, RENDER_DIGIT_HEIGHT, (point_t) {x, SAUCER_POSITION_Y}, color, GLOBALS_FORCE_BLACK_BACKGROUND);
			break;
		}
	}
}
