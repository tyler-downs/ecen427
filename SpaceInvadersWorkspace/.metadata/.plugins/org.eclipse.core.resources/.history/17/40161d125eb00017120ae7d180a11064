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
#define LIVES_X 320 						//X position of the Lives display
#define LIVES_Y 10							//Y position of the Lives display
#define LIVES_WIDTH 18						//Width of the Lives display
#define LIVES_HEIGHT 5						//Height of the Lives display

#define SCORE_X 10							//X position of the Score display
#define SCORE_Y LIVES_Y						//Y position of the Score display
#define SCORE_WIDTH 20						//Width of the Score display
#define SCORE_HEIGHT LIVES_HEIGHT			//Height of the Score display

#define NUM_LIVES_INIT 3					//Initial number of lives
#define LIVES_TANK_SPACE 20 				//space between "Lives" and the first tank life icon
#define TANK_SPACE 10						//Space between the tank icons

#define DIGIT_WIDTH 5						//Width of each digit
#define DIGIT_HEIGHT 5						//Height of each digit
#define ONE_WIDTH 5							//Width of the number 1
#define SCORE_GAP 20 						//space between "score" and first digit
#define MAX_SCORE_DIGITS 6					//Max number of digits a score can be

#define FRAME_BUFFER_0_ADDR 0xC1000000  	//Starting location in DDR where we will store the images that we display.


////////////////////// FUNCTION PROTOTYPES ///////////////////////
//Initializes the display
void disp_init();

//Draws the black game screen with the green line
void drawScreenInit();

//Draws an object given details about the bitmap, location, size, and color
void drawObject(uint32_t bitmap[], uint16_t width, uint16_t height, point_t startPoint, uint32_t color, uint8_t force);

//Draws one pixel given position and color
void drawPixel(uint16_t y, uint16_t x, uint32_t color);

//Erases a rectangle at the given position of the given size
void eraseRectangle(point_t startPoint, uint16_t width, uint16_t height);

#endif /* RENDER_H_ */
