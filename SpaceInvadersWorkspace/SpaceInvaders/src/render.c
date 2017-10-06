/*
 * render.c
 *
 *  Created on: Sep 22, 2017
 *      Author: superman
 */

#include "render.h"

////////////////// GLOBAL VARIABLES ///////////////////////////
// The variables framePointer and framePointer1 are just pointers to the base address
// of frame 0 and frame 1.
unsigned int * framePointer0 = (unsigned int *) FRAME_BUFFER_0_ADDR;
unsigned int * framePointer1 = ((unsigned int *) FRAME_BUFFER_0_ADDR) + 640*480;

char score[MAX_SCORE_DIGITS] = {0, 0, 0, 0, 0, 0}; //The global score digits


/** NOTE: This function is not finished, it will be used in the next lab. Ignore this for this lab. **/
/*
//Updates the score display given an integer score value
void updateScoreDisplay(uint16_t newScore)
{
	char updatedScore[MAX_SCORE_DIGITS] = {0, 0, 0, 0, 0, 0};
	//xil_sprintf(updatedScore, "%d", newScore); //store the score as a char array

	//test
	uint16_t n = 0;
	for (n = 0; n < MAX_SCORE_DIGITS; n++)
	{
		xil_printf("Score is : %c\n", updatedScore[n]);
	}

	uint16_t m, firstNonzero;
	for (m = 0; m < MAX_SCORE_DIGITS; m++)
	{
		if (updatedScore[m] != 0)
		{
			firstNonzero = m;
			break;
		}
	}
	uint16_t k;
	uint8_t x;
	for (k = firstNonzero; k < MAX_SCORE_DIGITS; k++)
	{
		switch(updatedScore[k])
		{
		case '0':
			x = SCORE_X + SCORE_WIDTH*MAGNIFY_MULT + (k-firstNonzero)*(DIGIT_WIDTH*MAGNIFY_MULT);
			drawObject(zero_5x5, DIGIT_WIDTH, DIGIT_HEIGHT, (point_t) {x, SCORE_Y}, GREEN, FORCE_BLACK_BACKGROUND);
			break;
		case '1':
			x = SCORE_X + SCORE_WIDTH*MAGNIFY_MULT + (k-firstNonzero)*(DIGIT_WIDTH*MAGNIFY_MULT);
			drawObject(one_3x5, ONE_WIDTH, DIGIT_HEIGHT, (point_t) {x, SCORE_Y}, GREEN, FORCE_BLACK_BACKGROUND);
			break;
		case '2':
			x = SCORE_X + SCORE_WIDTH*MAGNIFY_MULT + (k-firstNonzero)*(DIGIT_WIDTH*MAGNIFY_MULT);
			drawObject(two_5x5, ONE_WIDTH, DIGIT_HEIGHT, (point_t) {x, SCORE_Y}, GREEN, FORCE_BLACK_BACKGROUND);
			break;
		case '3':
			x = SCORE_X + SCORE_WIDTH*MAGNIFY_MULT + (k-firstNonzero)*(DIGIT_WIDTH*MAGNIFY_MULT);
			drawObject(three_5x5, ONE_WIDTH, DIGIT_HEIGHT, (point_t) {x, SCORE_Y}, GREEN, FORCE_BLACK_BACKGROUND);
			break;
		case '4':
			x = SCORE_X + SCORE_WIDTH*MAGNIFY_MULT + (k-firstNonzero)*(DIGIT_WIDTH*MAGNIFY_MULT);
			drawObject(four_5x5, ONE_WIDTH, DIGIT_HEIGHT, (point_t) {x, SCORE_Y}, GREEN, FORCE_BLACK_BACKGROUND);
			break;
		case '5':
			x = SCORE_X + SCORE_WIDTH*MAGNIFY_MULT + (k-firstNonzero)*(DIGIT_WIDTH*MAGNIFY_MULT);
			drawObject(five_5x5, ONE_WIDTH, DIGIT_HEIGHT, (point_t) {x, SCORE_Y}, GREEN, FORCE_BLACK_BACKGROUND);
			break;
		case '6':
			x = SCORE_X + SCORE_WIDTH*MAGNIFY_MULT + (k-firstNonzero)*(DIGIT_WIDTH*MAGNIFY_MULT);
			drawObject(six_5x5, ONE_WIDTH, DIGIT_HEIGHT, (point_t) {x, SCORE_Y}, GREEN, FORCE_BLACK_BACKGROUND);
			break;
		case '7':
			x = SCORE_X + SCORE_WIDTH*MAGNIFY_MULT + (k-firstNonzero)*(DIGIT_WIDTH*MAGNIFY_MULT);
			drawObject(seven_5x5, ONE_WIDTH, DIGIT_HEIGHT, (point_t) {x, SCORE_Y}, GREEN, FORCE_BLACK_BACKGROUND);
			break;
		case '8':
			x = SCORE_X + SCORE_WIDTH*MAGNIFY_MULT + (k-firstNonzero)*(DIGIT_WIDTH*MAGNIFY_MULT);
			drawObject(eight_5x5, ONE_WIDTH, DIGIT_HEIGHT, (point_t) {x, SCORE_Y}, GREEN, FORCE_BLACK_BACKGROUND);
			break;
		case '9':
			x = SCORE_X + SCORE_WIDTH*MAGNIFY_MULT + (k-firstNonzero)*(DIGIT_WIDTH*MAGNIFY_MULT);
			drawObject(nine_5x5, ONE_WIDTH, DIGIT_HEIGHT, (point_t) {x, SCORE_Y}, GREEN, FORCE_BLACK_BACKGROUND);
			break;
		}
	}
}*/


//Draws one pixel to the frame buffer. Checks if it is already that color before drawing.
void drawPixel(uint16_t y, uint16_t x, uint32_t color)
{
	if (framePointer0[y*WIDTH_DISPLAY + x] != color)
		framePointer0[y*WIDTH_DISPLAY + x] = color;
}

//erases a rectangle with upper left point startpoint, given width, and given height in pixels
void eraseRectangle(point_t startPoint, uint16_t width, uint16_t height)
{
	uint8_t i, j;
	for (i = 0; i < width*MAGNIFY_MULT; i++) //iterate through the width of the rectangle
	{
		for (j = 0; j < height*MAGNIFY_MULT; j++) //iterate through the height
		{
			drawPixel((startPoint.y + j), (startPoint.x + i), BLACK); //draw each pixel black as night
		}
	}
}

//if force is true, it will draw black where the bitmap is 0. If it is false, it will leave it alone.
void drawObject(uint32_t bitmap[], uint16_t width, uint16_t height, point_t startPoint, uint32_t color, uint8_t force)
{
	uint16_t row=0, col=0;
	for (row=0; row<(height*MAGNIFY_MULT); row++) { //iterate through the height of the object
		for (col=0; col<(width*MAGNIFY_MULT); col++) {	//iterate through the width of the object
			//if the bitmap tells you to draw and the force is strong
			if ((bitmap[row/MAGNIFY_MULT] & (1<<(width-1-col/MAGNIFY_MULT))))
			{
				drawPixel((row+startPoint.y), (col+startPoint.x), color); //draw the pixel in the color
			}
			else
			{
				if (force) //if the force option is enabled, draw the background black
					drawPixel((row+startPoint.y), (col+startPoint.x), BLACK);
				else //otherwise, skip the pixels that you don't need to color in
					continue;
			}
		}
	}
}

//Draws the initial game screen (just the green line and the black background).
void drawScreenInit()
{
	uint16_t row=0, col=0;
	for( row=0; row<HEIGHT_DISPLAY; row++) { //iterate through the display height
		for(col=0; col<WIDTH_DISPLAY; col++) { //iterate through the width too
			//if we're in the spot where green should be drawn
			if (row > BOTTOMLINE_TOP && row < BOTTOMLINE_TOP + BOTTOMLINE_WIDTH)
			{
				//framePointer0[row*WIDTH_DISPLAY + col] = GREEN; //draw green pixels
				drawPixel(row, col, GREEN);
			}
			else
			{
				//framePointer0[row*WIDTH_DISPLAY + col] = BLACK; //draw black pixels
				drawPixel(row, col, BLACK);
			}
		}
	}
}

//Initially draws the tank
void drawTankInit()
{
	point_t tankStartPoint = {TANK_START_X, TANK_START_Y}; //put the tank at its start point
	drawObject(tank_15x8, TANK_WIDTH, TANK_HEIGHT, tankStartPoint, GREEN, FORCE_BLACK_BACKGROUND); //draw the tank
	setTankPosition(TANK_START_X); //set global variable
}

//Initially draws the aliens
void drawAliensInit()
{
	uint8_t r = 0, c = 0;
	for (r = 0; r < NUM_ALIEN_ROWS; r++) //alien rows
	{
		for (c = 0; c < NUM_ALIEN_COLUMNS; c++) //alien column
		{
			uint16_t x = ALIENS_START_X + (ALIEN_WIDTH * MAGNIFY_MULT * c) + (ALIEN_SPACE_HORIZ * c);
			uint16_t y = (ALIENS_START_Y + (ALIEN_HEIGHT * MAGNIFY_MULT * r) + ALIEN_SPACE_VERT * r);
			point_t alienStartPoint = {x, y};
			if (r < NUM_TOP_ALIEN_ROWS) //if we're drawing a top alien
				drawObject(alien_top_out_12x8, ALIEN_WIDTH, ALIEN_HEIGHT, alienStartPoint, WHITE, FORCE_BLACK_BACKGROUND); //draw top alien
			else if(r < NUM_TOP_ALIEN_ROWS + NUM_MIDDLE_ALIEN_ROWS) //if we're drawing a middle alien
				drawObject(alien_middle_out_12x8, ALIEN_WIDTH, ALIEN_HEIGHT, alienStartPoint, WHITE, FORCE_BLACK_BACKGROUND); //draw middle alien
			else // we must be drawing a bottom alien
				drawObject(alien_bottom_out_12x8, ALIEN_WIDTH, ALIEN_HEIGHT, alienStartPoint, WHITE, FORCE_BLACK_BACKGROUND); //draw bottom alien
		}
	}
	point_t alienBlockStartPoint = {ALIENS_START_X, ALIENS_START_Y};
	setAlienBlockPosition(alienBlockStartPoint); //set global
	xil_printf("Alien block position initially: %d, %d\n\r", getAlienBlockPosition().x, getAlienBlockPosition().y);
}

//Initializes the display
void disp_init()
{
	//initialize display stuff

	int Status;                        // Keep track of success/failure of system function calls.
	XAxiVdma videoDMAController;
	// There are 3 steps to initializing the vdma driver and IP.
	// Step 1: lookup the memory structure that is used to access the vdma driver.
	XAxiVdma_Config * VideoDMAConfig = XAxiVdma_LookupConfig(XPAR_AXI_VDMA_0_DEVICE_ID);
	// Step 2: Initialize the memory structure and the hardware.
	if(XST_FAILURE == XAxiVdma_CfgInitialize(&videoDMAController, VideoDMAConfig,	XPAR_AXI_VDMA_0_BASEADDR)) {
		xil_printf("VideoDMA Did not initialize.\r\n");
	}
	// Step 3: (optional) set the frame store number.
	if(XST_FAILURE ==  XAxiVdma_SetFrmStore(&videoDMAController, 2, XAXIVDMA_READ)) {
		xil_printf("Set Frame Store Failed.");
	}
	// Initialization is complete at this point.

	// Setup the frame counter. We want two read frames. We don't need any write frames but the
	// function generates an error if you set the write frame count to 0. We set it to 2
	// but ignore it because we don't need a write channel at all.
	XAxiVdma_FrameCounter myFrameConfig;
	myFrameConfig.ReadFrameCount = 2;
	myFrameConfig.ReadDelayTimerCount = 10;
	myFrameConfig.WriteFrameCount =2;
	myFrameConfig.WriteDelayTimerCount = 10;
	Status = XAxiVdma_SetFrameCounter(&videoDMAController, &myFrameConfig);
	if (Status != XST_SUCCESS) {
		xil_printf("Set frame counter failed %d\r\n", Status);
		if(Status == XST_VDMA_MISMATCH_ERROR)
			xil_printf("DMA Mismatch Error\r\n");
	}
	// Now we tell the driver about the geometry of our frame buffer and a few other things.
	// Our image is 480 x 640.
	XAxiVdma_DmaSetup myFrameBuffer;
	myFrameBuffer.VertSizeInput = 480;    // 480 vertical pixels.
	myFrameBuffer.HoriSizeInput = 640*4;  // 640 horizontal (32-bit pixels).
	myFrameBuffer.Stride = 640*4;         // Dont' worry about the rest of the values.
	myFrameBuffer.FrameDelay = 0;
	myFrameBuffer.EnableCircularBuf=1;
	myFrameBuffer.EnableSync = 0;
	myFrameBuffer.PointNum = 0;
	myFrameBuffer.EnableFrameCounter = 0;
	myFrameBuffer.FixedFrameStoreAddr = 0;
	if(XST_FAILURE == XAxiVdma_DmaConfig(&videoDMAController, XAXIVDMA_READ, &myFrameBuffer)) {
		xil_printf("DMA Config Failed\r\n");
	}
	// We need to give the frame buffer pointers to the memory that it will use. This memory
	// is where you will write your video data. The vdma IP/driver then streams it to the HDMI
	// IP.
	myFrameBuffer.FrameStoreStartAddr[0] = FRAME_BUFFER_0_ADDR;
	myFrameBuffer.FrameStoreStartAddr[1] = FRAME_BUFFER_0_ADDR + 4*640*480;

	if(XST_FAILURE == XAxiVdma_DmaSetBufferAddr(&videoDMAController, XAXIVDMA_READ,
			myFrameBuffer.FrameStoreStartAddr)) {
		xil_printf("DMA Set Address Failed Failed\r\n");
	}
	// Print a sanity message if you get this far.
	xil_printf("Woohoo! I made it through initialization.\n\r");
	// Now, let's get ready to start displaying some stuff on the screen.

	//Draw everything on screen in original positions
	drawScreenInit(); //draw the main screen
	drawTankInit(); //draw the tank
	drawBunkersInit(); //draw the bunkers
	drawAliensInit(); //draw the block of aliens

	//Draw the word "Lives"
	drawObject(lives_18x5, LIVES_WIDTH, LIVES_HEIGHT, (point_t) {LIVES_X, LIVES_Y}, WHITE, FORCE_BLACK_BACKGROUND);
	//Draw the word "Score
	drawObject(score_20x5, SCORE_WIDTH, SCORE_HEIGHT, (point_t) {SCORE_X, SCORE_Y}, WHITE, FORCE_BLACK_BACKGROUND);

	//draw tank lives
	int n;
	for(n = 0; n < NUM_LIVES_INIT; n++) //Just draw a tank three times at the top of the screen
	{
		int x = LIVES_X + LIVES_WIDTH*MAGNIFY_MULT + LIVES_TANK_SPACE + n*(TANK_WIDTH*MAGNIFY_MULT + TANK_SPACE);
		int y = LIVES_Y - (TANK_HEIGHT - LIVES_HEIGHT)*MAGNIFY_MULT;
		drawObject(tank_15x8, TANK_WIDTH, TANK_HEIGHT, (point_t) {x, y}, GREEN, FORCE_BLACK_BACKGROUND);
	}
	srand(time(NULL)); //set random seed
	// This tells the HDMI controller the resolution of your display (there must be a better way to do this).
	XIo_Out32(XPAR_AXI_HDMI_0_BASEADDR, 640*480);
	// Start the DMA for the read channel only.
	if(XST_FAILURE == XAxiVdma_DmaStart(&videoDMAController, XAXIVDMA_READ)){
		xil_printf("DMA START FAILED\r\n");
	}
	int frameIndex = 0;
	// We have two frames, let's park on frame 0. Use frameIndex to index them.
	// Note that you have to start the DMA process before parking on a frame.
	if (XST_FAILURE == XAxiVdma_StartParking(&videoDMAController, frameIndex,  XAXIVDMA_READ)) {
		xil_printf("vdma parking failed\n\r");
	}
}



