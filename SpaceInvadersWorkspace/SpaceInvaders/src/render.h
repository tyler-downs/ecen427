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

#define DEBUG
void print(char *str);

#define FRAME_BUFFER_0_ADDR 0xC1000000  // Starting location in DDR where we will store the images that we display.

void disp_init();
//void drawObject(uint32_t bitmap[], uint16_t width, uint16_t height, point_t startPoint, uint32_t color);
void render();
void drawScreenInit();
void drawObject(uint32_t bitmap[], uint16_t width, uint16_t height, point_t startPoint, uint32_t color);
void drawPixel(uint16_t y, uint16_t x, uint32_t color);
void eraseRectangle(point_t startPoint, uint16_t width, uint16_t height);


#endif /* RENDER_H_ */
