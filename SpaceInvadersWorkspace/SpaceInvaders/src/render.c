/*
 * render.c
 *
 *  Created on: Sep 22, 2017
 *      Author: superman
 */

#include "render.h"

#define MAGNIFY_MULT 2
#define WIDTH_DISPLAY 640
#define HEIGHT_DISPLAY 480
// The variables framePointer and framePointer1 are just pointers to the base address
// of frame 0 and frame 1.
unsigned int * framePointer0 = (unsigned int *) FRAME_BUFFER_0_ADDR;
unsigned int * framePointer1 = ((unsigned int *) FRAME_BUFFER_0_ADDR) + 640*480;

void drawObject(uint32_t bitmap[], uint16_t width, uint16_t height, point_t startPoint, uint32_t color)
{
	uint16_t row=0, col=0;
	for (row=0; row<(height*MAGNIFY_MULT); row++) {
		for (col=0; col<(width*MAGNIFY_MULT); col++) {
			if ((bitmap[row/MAGNIFY_MULT] & (1<<(width-1-col/MAGNIFY_MULT))))
			{
				framePointer0[(row+startPoint.y)*WIDTH_DISPLAY + (col+startPoint.x)] = color;
			}
			else
			{
				continue;
				framePointer0[row*WIDTH_DISPLAY + col] = BLACK;
			}
		}
	}
}

#define BOTTOMLINE_TOP 438
#define BOTTOMLINE_WIDTH 3
void drawScreenInit()
{
	uint16_t row=0, col=0;
	for( row=0; row<HEIGHT_DISPLAY; row++) {
		for(col=0; col<WIDTH_DISPLAY; col++) {
			if (row > BOTTOMLINE_TOP && row < BOTTOMLINE_TOP + BOTTOMLINE_WIDTH)
			{
				framePointer0[row*WIDTH_DISPLAY + col] = GREEN;
			}
			else
			{
				framePointer0[row*WIDTH_DISPLAY + col] = BLACK;
			}
		}
	}
}

#define TANK_START_X 99
#define TANK_START_Y 400
#define TANK_WIDTH 15
#define TANK_HEIGHT 8
void drawTankInit()
{
	point_t tankStartPoint = {TANK_START_X, TANK_START_Y};
	drawObject(tank_15x8, TANK_WIDTH, TANK_HEIGHT, tankStartPoint, GREEN); //draw the tank
	setTankPosition(TANK_START_X); //set global variable
}

#define BUNKER_START_Y 340
#define BUNKER_SPACE 90 //space between individual bunkers, and bunkers and the edge of the screen
#define BUNKER_WIDTH 24
#define BUNKER_HEIGHT 18
#define BUNKER_FINAL_WIDTH (BUNKER_WIDTH * MAGNIFY_MULT)
#define NUM_BUNKERS 4
void drawBunkersInit()
{
	uint8_t n = 1;
	for (n = 1; n < NUM_BUNKERS + 1; n++)
	{
		point_t bunkerStartPoint = {(n * BUNKER_SPACE) + ((n-1) * BUNKER_FINAL_WIDTH), BUNKER_START_Y};
		drawObject(bunker_24x18, BUNKER_WIDTH, BUNKER_HEIGHT, bunkerStartPoint, GREEN); //draw bunkers
	}
}

#define ALIENS_START_X 145
#define ALIENS_START_Y 125
#define ALIEN_WIDTH 12
#define ALIEN_HEIGHT 8
#define NUM_ALIENS_PER_ROW 11
#define NUM_TOP_ALIEN_ROWS 1
#define NUM_MIDDLE_ALIEN_ROWS 2
#define NUM_BOTTOM_ALIEN_ROWS 2
#define ALIEN_SPACE_HORIZ 8
#define ALIEN_SPACE_VERT 10
void drawAliensInit()
{
	uint8_t r = 0, c = 0;
	for (r = 0; r < NUM_TOP_ALIEN_ROWS + NUM_MIDDLE_ALIEN_ROWS + NUM_BOTTOM_ALIEN_ROWS; r++) //alien rows
	{
		for (c = 0; c < NUM_ALIENS_PER_ROW; c++) //alien column
		{
			uint16_t x = ALIENS_START_X + (ALIEN_WIDTH * MAGNIFY_MULT * c) + (ALIEN_SPACE_HORIZ * c);
			uint16_t y = (ALIENS_START_Y + (ALIEN_HEIGHT * MAGNIFY_MULT * r) + ALIEN_SPACE_VERT * r);
			point_t alienStartPoint = {x, y};
			if (r < NUM_TOP_ALIEN_ROWS) //if we're drawing a top alien
				drawObject(alien_top_out_12x8, ALIEN_WIDTH, ALIEN_HEIGHT, alienStartPoint, WHITE); //draw top alien
			else if(r < NUM_TOP_ALIEN_ROWS + NUM_MIDDLE_ALIEN_ROWS) //if we're drawing a middle alien
				drawObject(alien_middle_out_12x8, ALIEN_WIDTH, ALIEN_HEIGHT, alienStartPoint, WHITE); //draw middle alien
			else // we must be drawing a bottom alien
				drawObject(alien_bottom_out_12x8, ALIEN_WIDTH, ALIEN_HEIGHT, alienStartPoint, WHITE); //draw bottom alien
		}
	}
	point_t alienBlockStartPoint = {ALIENS_START_X, ALIENS_START_Y};
	setAlienBlockPosition(alienBlockStartPoint); //set global
}




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



	//draw everything on screen in original positions //DO THIS ***********************************
	drawScreenInit(); //draw the main screen
	drawTankInit(); //draw the tank
	drawBunkersInit(); //draw the bunkers
	drawAliensInit(); //draw the block of aliens







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

void render()
{

}


