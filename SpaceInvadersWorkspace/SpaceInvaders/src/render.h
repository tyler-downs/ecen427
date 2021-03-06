/*
 * render.h
 *
 *  Created on: Sep 22, 2017
 *      Author: superman
 */

#ifndef RENDER_H_
#define RENDER_H_

#include "platform.h"
#include "xparameters.h"
#include "xaxivdma.h"
#include "xio.h"
#include "time.h"
#include "unistd.h"
#include "bitmaps.h"
#include "globals.h"
#include "bunkers.h"
#include <time.h>
#include <stdlib.h>


///////////////////////// DEFINES /////////////////////////////
#define RENDER_LIVES_X 320 						//X position of the Lives display
#define RENDER_LIVES_Y 10							//Y position of the Lives display
#define RENDER_LIVES_WIDTH 18						//Width of the Lives display
#define RENDER_LIVES_HEIGHT 5						//Height of the Lives display

#define RENDER_SCORE_X 10							//X position of the Score display
#define RENDER_SCORE_Y RENDER_LIVES_Y						//Y position of the Score display
#define RENDER_SCORE_WIDTH 20						//Width of the Score display
#define RENDER_SCORE_HEIGHT RENDER_LIVES_HEIGHT			//Height of the Score display

#define RENDER_NUM_LIVES_INIT 3					//Initial number of lives
#define RENDER_LIVES_TANK_SPACE 20 				//space between "Lives" and the first tank life icon
#define RENDER_TANK_SPACE 10						//Space between the tank icons

#define RENDER_DIGIT_WIDTH 5						//Width of each digit
#define RENDER_DIGIT_HEIGHT 5						//Height of each digit
#define RENDER_ONE_WIDTH 5							//Width of the number 1
#define RENDER_SCORE_GAP 20 						//space between "score" and first digit
#define RENDER_MAX_SCORE_DIGITS 6					//Max number of digits a score can be

#define RENDER_FRAME_BUFFER_0_ADDR 0xC1000000  	//Starting location in DDR where we will store the images that we display.

#define RENDER_INC 1								//Used for incrementing the score/lives
#define RENDER_DEC -1								//Used for decrementing the score/lives

#define RENDER_SCORE_SPACE 15						//Space between score and the score


////////////////////// FUNCTION PROTOTYPES ///////////////////////
//return framePointer0
unsigned int * render_getFramePointer0();

//Initializes the display
void render_disp_init();

//Draws the black game screen with the green line
void render_drawScreenInit();

//Draws an object given details about the bitmap, location, size, and color
void render_drawObject(uint32_t bitmap[], uint16_t width, uint16_t height, point_t startPoint, uint32_t color, uint8_t force);

//Draws one pixel given position and color
void render_drawPixel(int16_t y, int16_t x, uint32_t color);

//Erases a rectangle at the given position of the given size
void render_eraseRectangle(point_t startPoint, uint16_t width, uint16_t height);

//update the score displayed on the screen by passing in the score to be displayed
void render_updateScoreDisplay(uint16_t newScore);

//update the lives displayed on the screen by passing in 1 to add a life or -1 to lose a life
void render_updateLivesDisplay(int8_t incDec);

//Draws the game over screen at the end of the game
void render_drawGameOverScreen();

//Initially draws the tank
void render_drawTankInit();

//Initially draws the aliens
void render_drawAliensInit();

#endif /* RENDER_H_ */
