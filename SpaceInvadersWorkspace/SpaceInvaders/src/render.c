/*
 * render.c
 *
 *  Created on: Sep 22, 2017
 *      Author: superman
 */

#include "render.h"

//////////////////////// DEFINES ////////////////////////////////
#define UPDATE_SCORE_MAX_INDEX 5	//used in updating the score
#define UPDATE_SCORE_DIVISOR 10  	//used in finding the digits for the score
#define LIVES_PER_ROW 6				//Number of lives per row
#define GAME_OVER_WIDTH 33			//Width of the game over message
#define GAME_OVER_HEIGHT 5			//Height of the game over message
#define GAME_OVER_START_X 275		//x-coord of the game over message
#define GAME_OVER_START_Y 70		//y-coord of the game over message
#define SPACE_BETWEEN_LIFE_ROWS (GLOBALS_TANK_HEIGHT * 1.5 * GLOBALS_MAGNIFY_MULT) //the space between the life rows


////////////////// GLOBAL VARIABLES ///////////////////////////
// The variables framePointer and framePointer1 are just pointers to the base address
// of frame 0 and frame 1.
unsigned int * framePointer0 = (unsigned int *) RENDER_FRAME_BUFFER_0_ADDR;
unsigned int * framePointer1 = ((unsigned int *) RENDER_FRAME_BUFFER_0_ADDR) + 640*480;
char score[RENDER_MAX_SCORE_DIGITS] = {0, 0, 0, 0, 0, 0}; //The global score digits

//////////////////////// FUNCTIONS //////////////////////////////////

//Returns the frame pointer
unsigned int * render_getFramePointer0() {return framePointer0;}

//Updates the score display given an integer score value
void render_updateScoreDisplay(uint16_t newScore)
{
	char updatedScore[RENDER_MAX_SCORE_DIGITS] = {'0', '0', '0', '0', '0', '0'}; //initialize the score char array

	//convert the integer score into a char array
	int16_t i = 0;
	for (i = UPDATE_SCORE_MAX_INDEX; i >= 0; i--)
	{
		updatedScore[i] = (char) ((newScore % UPDATE_SCORE_DIVISOR) + '0');
		newScore /= UPDATE_SCORE_DIVISOR;
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
		x = RENDER_SCORE_SPACE + RENDER_SCORE_X + RENDER_SCORE_WIDTH*GLOBALS_MAGNIFY_MULT + (k-firstNonzero)*(RENDER_DIGIT_WIDTH*GLOBALS_MAGNIFY_MULT);
		switch(updatedScore[k])
		{
		case '0':
			render_drawObject(zero_5x5, RENDER_DIGIT_WIDTH, RENDER_DIGIT_HEIGHT, (point_t) {x, RENDER_SCORE_Y}, GLOBALS_GREEN, GLOBALS_FORCE_BLACK_BACKGROUND);
			break;
		case '1':
			render_drawObject(one_5x5, RENDER_ONE_WIDTH, RENDER_DIGIT_HEIGHT, (point_t) {x, RENDER_SCORE_Y}, GLOBALS_GREEN, GLOBALS_FORCE_BLACK_BACKGROUND);
			break;
		case '2':
			render_drawObject(two_5x5, RENDER_ONE_WIDTH, RENDER_DIGIT_HEIGHT, (point_t) {x, RENDER_SCORE_Y}, GLOBALS_GREEN, GLOBALS_FORCE_BLACK_BACKGROUND);
			break;
		case '3':
			render_drawObject(three_5x5, RENDER_ONE_WIDTH, RENDER_DIGIT_HEIGHT, (point_t) {x, RENDER_SCORE_Y}, GLOBALS_GREEN, GLOBALS_FORCE_BLACK_BACKGROUND);
			break;
		case '4':
			render_drawObject(four_5x5, RENDER_ONE_WIDTH, RENDER_DIGIT_HEIGHT, (point_t) {x, RENDER_SCORE_Y}, GLOBALS_GREEN, GLOBALS_FORCE_BLACK_BACKGROUND);
			break;
		case '5':
			render_drawObject(five_5x5, RENDER_ONE_WIDTH, RENDER_DIGIT_HEIGHT, (point_t) {x, RENDER_SCORE_Y}, GLOBALS_GREEN, GLOBALS_FORCE_BLACK_BACKGROUND);
			break;
		case '6':
			render_drawObject(six_5x5, RENDER_ONE_WIDTH, RENDER_DIGIT_HEIGHT, (point_t) {x, RENDER_SCORE_Y}, GLOBALS_GREEN, GLOBALS_FORCE_BLACK_BACKGROUND);
			break;
		case '7':
			render_drawObject(seven_5x5, RENDER_ONE_WIDTH, RENDER_DIGIT_HEIGHT, (point_t) {x, RENDER_SCORE_Y}, GLOBALS_GREEN, GLOBALS_FORCE_BLACK_BACKGROUND);
			break;
		case '8':
			render_drawObject(eight_5x5, RENDER_ONE_WIDTH, RENDER_DIGIT_HEIGHT, (point_t) {x, RENDER_SCORE_Y}, GLOBALS_GREEN, GLOBALS_FORCE_BLACK_BACKGROUND);
			break;
		case '9':
			render_drawObject(nine_5x5, RENDER_ONE_WIDTH, RENDER_DIGIT_HEIGHT, (point_t) {x, RENDER_SCORE_Y}, GLOBALS_GREEN, GLOBALS_FORCE_BLACK_BACKGROUND);
			break;
		}
	}
}

//Returns the position the life tank should be placed given the life number
point_t calculateLifePosition(uint8_t lifeNum)
{
	uint8_t col = lifeNum % LIVES_PER_ROW; //determine col
	uint8_t row = lifeNum / LIVES_PER_ROW; //determine row
	//Determine the x and y positions using some tricky geometry
	uint16_t x = RENDER_LIVES_X + RENDER_LIVES_WIDTH*GLOBALS_MAGNIFY_MULT + RENDER_LIVES_TANK_SPACE + col*(GLOBALS_TANK_WIDTH*GLOBALS_MAGNIFY_MULT + RENDER_TANK_SPACE);
	uint16_t y = RENDER_LIVES_Y - (GLOBALS_TANK_HEIGHT - RENDER_LIVES_HEIGHT)*GLOBALS_MAGNIFY_MULT + row*(SPACE_BETWEEN_LIFE_ROWS);
	return (point_t) {x, y};
}

//Updates the lives display on the screen, higher level
void render_updateLivesDisplay(int8_t incDec)
{
	uint8_t lifeNum = (incDec > 0) ? globals_getNumLives() : (globals_getNumLives());
	point_t lifePosition = calculateLifePosition(lifeNum);
	uint32_t color = (incDec > 0) ? GLOBALS_GREEN : GLOBALS_BLACK;
	render_drawObject(tank_15x8, GLOBALS_TANK_WIDTH, GLOBALS_TANK_HEIGHT, lifePosition, color, GLOBALS_FORCE_BLACK_BACKGROUND);
}

//Returns whether the point given is on the screen or not
uint8_t isOnScreen(point_t point)
{
	return (point.x >= 0 && point.x < GLOBALS_WIDTH_DISPLAY && point.y >=0 && point.y < GLOBALS_HEIGHT_DISPLAY);
}

//Draws one pixel to the frame buffer. Checks if it is already that color before drawing.
void render_drawPixel(int16_t y, int16_t x, uint32_t color)
{
	if (isOnScreen((point_t){x,y}) && framePointer0[y*GLOBALS_WIDTH_DISPLAY + x] != color)
		framePointer0[y*GLOBALS_WIDTH_DISPLAY + x] = color;
}

//erases a rectangle with upper left point startpoint, given width, and given height in pixels
void render_eraseRectangle(point_t startPoint, uint16_t width, uint16_t height)
{
	uint8_t i, j;
	for (i = 0; i < width*GLOBALS_MAGNIFY_MULT; i++) //iterate through the width of the rectangle
	{
		for (j = 0; j < height*GLOBALS_MAGNIFY_MULT; j++) //iterate through the height
		{
			render_drawPixel((startPoint.y + j), (startPoint.x + i), GLOBALS_BLACK); //draw each pixel black as night
		}
	}
}

//if force is true, it will draw black where the bitmap is 0. If it is false, it will leave it alone.
void render_drawObject(uint32_t bitmap[], uint16_t width, uint16_t height, point_t startPoint, uint32_t color, uint8_t force)
{
	uint16_t row=0, col=0;
	for (row=0; row<(height*GLOBALS_MAGNIFY_MULT); row++) { //iterate through the height of the object
		for (col=0; col<(width*GLOBALS_MAGNIFY_MULT); col++) {	//iterate through the width of the object
			//if the bitmap tells you to draw and the force is strong
			if ((bitmap[row/GLOBALS_MAGNIFY_MULT] & (1<<(width-1-col/GLOBALS_MAGNIFY_MULT))))
			{
				render_drawPixel((row+startPoint.y), (col+startPoint.x), color); //draw the pixel in the color
			}
			else
			{
				if (force) //if the force option is enabled, draw the background black
					render_drawPixel((row+startPoint.y), (col+startPoint.x), GLOBALS_BLACK);
				else //otherwise, skip the pixels that you don't need to color in
					continue;
			}
		}
	}
}

//Draws the initial game screen (just the green line and the black background).
void render_drawScreenInit()
{
	uint16_t row=0, col=0;
	for( row=0; row<GLOBALS_HEIGHT_DISPLAY; row++) { //iterate through the display height
		for(col=0; col<GLOBALS_WIDTH_DISPLAY; col++) { //iterate through the width too
			//if we're in the spot where green should be drawn
			if (row > GLOBALS_BOTTOMLINE_TOP && row < GLOBALS_BOTTOMLINE_TOP + GLOBALS_BOTTOMLINE_WIDTH)
			{
				//framePointer0[row*WIDTH_DISPLAY + col] = GREEN; //draw green pixels
				render_drawPixel(row, col, GLOBALS_GREEN);
			}
			else
			{
				//framePointer0[row*WIDTH_DISPLAY + col] = BLACK; //draw black pixels
				render_drawPixel(row, col, GLOBALS_BLACK);
			}
		}
	}
}

//Initially draws the tank
void render_drawTankInit()
{
	point_t tankStartPoint = {GLOBALS_TANK_START_X, GLOBALS_TANK_START_Y}; //put the tank at its start point
	render_drawObject(tank_15x8, GLOBALS_TANK_WIDTH, GLOBALS_TANK_HEIGHT, tankStartPoint, GLOBALS_GREEN, GLOBALS_FORCE_BLACK_BACKGROUND); //draw the tank
	globals_setTankPosition(GLOBALS_TANK_START_X); //set global variable
}

//Initially draws the aliens
void render_drawAliensInit()
{
	uint8_t r = 0, c = 0;
	for (r = 0; r < GLOBALS_NUM_ALIEN_ROWS; r++) //alien rows
	{
		for (c = 0; c < GLOBALS_NUM_ALIEN_COLUMNS; c++) //alien column
		{
			uint16_t x = GLOBALS_ALIENS_START_X + (GLOBALS_ALIEN_WIDTH * GLOBALS_MAGNIFY_MULT * c) + (GLOBALS_ALIEN_SPACE_HORIZ * c);
			uint16_t y = (GLOBALS_ALIENS_START_Y + (GLOBALS_ALIEN_HEIGHT * GLOBALS_MAGNIFY_MULT * r) + GLOBALS_ALIEN_SPACE_VERT * r);
			point_t alienStartPoint = {x, y};
			if (r < GLOBALS_NUM_TOP_ALIEN_ROWS) //if we're drawing a top alien
				render_drawObject(alien_top_out_12x8, GLOBALS_ALIEN_WIDTH, GLOBALS_ALIEN_HEIGHT, alienStartPoint, GLOBALS_WHITE, GLOBALS_FORCE_BLACK_BACKGROUND); //draw top alien
			else if(r < GLOBALS_NUM_TOP_ALIEN_ROWS + GLOBALS_NUM_MIDDLE_ALIEN_ROWS) //if we're drawing a middle alien
				render_drawObject(alien_middle_out_12x8, GLOBALS_ALIEN_WIDTH, GLOBALS_ALIEN_HEIGHT, alienStartPoint, GLOBALS_WHITE, GLOBALS_FORCE_BLACK_BACKGROUND); //draw middle alien
			else // we must be drawing a bottom alien
				render_drawObject(alien_bottom_out_12x8, GLOBALS_ALIEN_WIDTH, GLOBALS_ALIEN_HEIGHT, alienStartPoint, GLOBALS_WHITE, GLOBALS_FORCE_BLACK_BACKGROUND); //draw bottom alien
		}
	}
	point_t alienBlockStartPoint = {GLOBALS_ALIENS_START_X, GLOBALS_ALIENS_START_Y};
	aliens_setAlienBlockPosition(alienBlockStartPoint); //set global
}

//Draws the game over screen when the game ends
void render_drawGameOverScreen(u32 color)
{
	render_drawObject(gameOver_33x5, GAME_OVER_WIDTH, GAME_OVER_HEIGHT, (point_t) {GAME_OVER_START_X, GAME_OVER_START_Y}, color, GLOBALS_FORCE_BLACK_BACKGROUND);
}

//Initializes the display
void render_disp_init()
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
	myFrameBuffer.FrameStoreStartAddr[0] = RENDER_FRAME_BUFFER_0_ADDR;
	myFrameBuffer.FrameStoreStartAddr[1] = RENDER_FRAME_BUFFER_0_ADDR + 4*640*480;

	if(XST_FAILURE == XAxiVdma_DmaSetBufferAddr(&videoDMAController, XAXIVDMA_READ,
			myFrameBuffer.FrameStoreStartAddr)) {
		xil_printf("DMA Set Address Failed Failed\r\n");
	}
	// Print a sanity message if you get this far.
	xil_printf("Woohoo! I made it through initialization.\n\r");
	// Now, let's get ready to start displaying some stuff on the screen.

	//Draw everything on screen in original positions
	render_drawScreenInit(); //draw the main screen
	render_drawTankInit(); //draw the tank
	bunkers_drawBunkersInit(); //draw the bunkers
	render_drawAliensInit(); //draw the block of aliens

	//Draw the word "Lives"
	render_drawObject(lives_18x5, RENDER_LIVES_WIDTH, RENDER_LIVES_HEIGHT, (point_t) {RENDER_LIVES_X, RENDER_LIVES_Y}, GLOBALS_BULLET_WHITE, GLOBALS_FORCE_BLACK_BACKGROUND);
	//Draw the word "Score"
	render_drawObject(score_20x5, RENDER_SCORE_WIDTH, RENDER_SCORE_HEIGHT, (point_t) {RENDER_SCORE_X, RENDER_SCORE_Y}, GLOBALS_BULLET_WHITE, GLOBALS_FORCE_BLACK_BACKGROUND);
	globals_setScore(0); //initialize the score
	render_updateScoreDisplay(0); //draw the score

	//draw tank lives
	int n;
	for(n = 0; n < RENDER_NUM_LIVES_INIT; n++) //Just draw a tank three times at the top of the screen
	{
		/*int x = LIVES_X + LIVES_WIDTH*MAGNIFY_MULT + LIVES_TANK_SPACE + n*(TANK_WIDTH*MAGNIFY_MULT + TANK_SPACE);
		int y = LIVES_Y - (TANK_HEIGHT - LIVES_HEIGHT)*MAGNIFY_MULT;
		drawObject(tank_15x8, TANK_WIDTH, TANK_HEIGHT, (point_t) {x, y}, GREEN, FORCE_BLACK_BACKGROUND);*/
		render_updateLivesDisplay(RENDER_INC);
		globals_updateLives(RENDER_INC); //update the global variable tracking number of lives
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



