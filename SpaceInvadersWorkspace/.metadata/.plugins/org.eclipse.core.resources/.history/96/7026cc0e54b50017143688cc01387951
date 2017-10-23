/*
 * saucer.c
 *
 *  Created on: Oct 13, 2017
 *      Author: superman
 */
#include "saucer.h"
#include "render.h"

//////////////////////// GLOBAL VARIABLES ///////////////////
static saucer_direction_type saucerDirection = saucer_moves_left;


////////////////////////// FUNCTIONS ////////////////////////
void drawSaucer()
{
	drawObject(saucer_16x7, SAUCER_WIDTH, SAUCER_HEIGHT, (point_t){getSaucerPosition(), SAUCER_POSITION_Y}, RED, FORCE_BLACK_BACKGROUND);
}

void eraseSaucer()
{
	drawObject(saucer_16x7, SAUCER_WIDTH, SAUCER_HEIGHT, (point_t){getSaucerPosition(), SAUCER_POSITION_Y}, BLACK, FORCE_BLACK_BACKGROUND);
}

//Sets the position and draws the saucer if it's going to the right
void initSaucerMovingRight()
{
	//set the position
	setSaucerPosition((int16_t)(SAUCER_WIDTH * -1));
	//draw the saucer there
	drawSaucer();
}

//Sets the position and draws the saucer if it's going to the left
void initSaucerMovingLeft()
{
	//set the position
	setSaucerPosition((int16_t) WIDTH_DISPLAY);
	//draw the saucer there
	drawSaucer();
}

#define SAUCER_MOVE_PIXELS 3
//Moves the saucer right
void moveSaucerRight()
{
	//erase the rectangle
	eraseRectangle((point_t) {getSaucerPosition(), SAUCER_POSITION_Y}, SAUCER_MOVE_PIXELS, SAUCER_HEIGHT);
	//change the start point of the saucer
	int16_t newSaucerPosition = getSaucerPosition() + SAUCER_MOVE_PIXELS;
	//xil_printf("In moveSaucerRight, position = %d\n\r", newSaucerPosition);
	setSaucerPosition(newSaucerPosition);
	//draw the saucer
	//xil_printf("New saucer position: %d\n\r", newSaucerPosition);
	drawObject(saucer_16x7, SAUCER_WIDTH, SAUCER_HEIGHT, (point_t){newSaucerPosition, SAUCER_POSITION_Y}, RED, FORCE_BLACK_BACKGROUND);
}

//Moves the saucer left
void moveSaucerLeft()
{
	//erase the rectangle
	eraseRectangle((point_t) {getSaucerPosition() + SAUCER_WIDTH*2 - SAUCER_MOVE_PIXELS, SAUCER_POSITION_Y}, SAUCER_MOVE_PIXELS*2, SAUCER_HEIGHT);
	//change the start point of the saucer
	int16_t newSaucerPosition = getSaucerPosition() - SAUCER_MOVE_PIXELS;
	//xil_printf("In moveSaucerLeft, position = %d\n\r", newSaucerPosition);
	setSaucerPosition(newSaucerPosition);
	//draw the saucer
	//xil_printf("New saucer position: %d\n\r", newSaucerPosition);
	drawObject(saucer_16x7, SAUCER_WIDTH, SAUCER_HEIGHT, (point_t){newSaucerPosition, SAUCER_POSITION_Y}, RED, FORCE_BLACK_BACKGROUND);
}

//Switches the direction the saucer is moving
void switchSaucerMoveDirection()
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
saucer_direction_type getSaucerDirection()
{
	return saucerDirection;
}

//Prints the random score when the saucer is killed
void printScoreOnSaucerDeath(uint16_t newScore, uint32_t color)
{
	char updatedScore[MAX_SCORE_DIGITS] = {'0', '0', '0', '0', '0', '0'}; //initialize the score char array

	//convert the integer score into a char array
	int16_t i = 0;
	for (i = 5; i >= 0; i--)
	{
		updatedScore[i] = (char) ((newScore % 10) + '0');
		//xil_printf("i = %d, newScore = %d, updatedScore[i] = %c\n\r", i, newScore, updatedScore[i]); //TEST
		newScore /= 10;
	}
	//determine the first digit to display (we don't want leading zeros)
	uint16_t m, firstNonzero = MAX_SCORE_DIGITS-1;
	for (m = 0 ; m < MAX_SCORE_DIGITS; m++)
	{
		if (updatedScore[m] != '0')
		{
			firstNonzero = m;
			break;
		}
	}
	//xil_printf("firstNonzero = %d\n\r", firstNonzero); //TEST
	uint16_t k;
	uint16_t x;
	//write each digit to the screen
	for (k = firstNonzero; k < MAX_SCORE_DIGITS; k++)
	{
		//xil_printf("saucerPosition: %d + k-firstNonzero*DW*MM: %d\n\r", getSaucerPosition(), (k-firstNonzero)*(DIGIT_WIDTH*MAGNIFY_MULT));
		x = getSaucerPosition() + (k-firstNonzero)*(DIGIT_WIDTH*MAGNIFY_MULT);
		//xil_printf("x = %d\n\r", x);
		switch(updatedScore[k])
		{
		case '0':
			drawObject(zero_5x5, DIGIT_WIDTH, DIGIT_HEIGHT, (point_t) {x, SAUCER_POSITION_Y}, color, FORCE_BLACK_BACKGROUND);
			break;
		case '1':
			drawObject(one_5x5, ONE_WIDTH, DIGIT_HEIGHT, (point_t) {x, SAUCER_POSITION_Y}, color, FORCE_BLACK_BACKGROUND);
			break;
		case '2':
			drawObject(two_5x5, ONE_WIDTH, DIGIT_HEIGHT, (point_t) {x, SAUCER_POSITION_Y}, color, FORCE_BLACK_BACKGROUND);
			break;
		case '3':
			drawObject(three_5x5, ONE_WIDTH, DIGIT_HEIGHT, (point_t) {x, SAUCER_POSITION_Y}, color, FORCE_BLACK_BACKGROUND);
			break;
		case '4':
			drawObject(four_5x5, ONE_WIDTH, DIGIT_HEIGHT, (point_t) {x, SAUCER_POSITION_Y}, color, FORCE_BLACK_BACKGROUND);
			break;
		case '5':
			drawObject(five_5x5, ONE_WIDTH, DIGIT_HEIGHT, (point_t) {x, SAUCER_POSITION_Y}, color, FORCE_BLACK_BACKGROUND);
			break;
		case '6':
			drawObject(six_5x5, ONE_WIDTH, DIGIT_HEIGHT, (point_t) {x, SAUCER_POSITION_Y}, color, FORCE_BLACK_BACKGROUND);
			break;
		case '7':
			drawObject(seven_5x5, ONE_WIDTH, DIGIT_HEIGHT, (point_t) {x, SAUCER_POSITION_Y}, color, FORCE_BLACK_BACKGROUND);
			break;
		case '8':
			drawObject(eight_5x5, ONE_WIDTH, DIGIT_HEIGHT, (point_t) {x, SAUCER_POSITION_Y}, color, FORCE_BLACK_BACKGROUND);
			break;
		case '9':
			drawObject(nine_5x5, ONE_WIDTH, DIGIT_HEIGHT, (point_t) {x, SAUCER_POSITION_Y}, color, FORCE_BLACK_BACKGROUND);
			break;
		}
	}
}
