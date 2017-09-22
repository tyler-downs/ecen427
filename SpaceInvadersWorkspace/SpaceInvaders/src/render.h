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

#define FRAME_BUFFER_0_ADDR 0xC0000000  // Starting location in DDR where we will store the images that we display.

void disp_init();
//void drawObject(uint32_t bitmap[], uint16_t width, uint16_t height, point_t startPoint, uint32_t color);
void render();

#endif /* RENDER_H_ */
