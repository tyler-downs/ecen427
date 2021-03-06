/*
 * globals.h
 *
 *  Created on: Sep 22, 2017
 *      Author: superman
 */

#ifndef GLOBALS_H_
#define GLOBALS_H_

#include <stdint.h>

/////////////////// DEFINES //////////////////////////
//General defines
#define GLOBALS_ERROR_INDEX -1 		//used for indicating error exit status of various functions

//Colors
#define GLOBALS_BLACK 0x00000000
#define GLOBALS_GREEN 0x0000FF00
#define GLOBALS_WHITE 0x00FFFFFF
#define GLOBALS_RED	  0x00FF0000
#define GLOBALS_BULLET_WHITE 0x00FFFFFE //slightly off-white so bullets will pass through each other and not think they're colliding

//Boolean values - True and False
#define TRUE 1
#define FALSE 0

//defines for line at bottom of screen
#define GLOBALS_BOTTOMLINE_TOP 438
#define GLOBALS_BOTTOMLINE_WIDTH 3

//#defines for aliens
#define GLOBALS_ALIENS_START_X 145 			//Initial x-coord for alien block
#define GLOBALS_ALIENS_START_Y 125 			//Initial y-coord for alien block
#define GLOBALS_ALIEN_WIDTH 12 				//Width of one alien in pixels
#define GLOBALS_ALIEN_HEIGHT 8 				//Height of one alien in pixels
#define GLOBALS_NUM_ALIEN_COLUMNS 11		//Number of columns of aliens
#define GLOBALS_NUM_TOP_ALIEN_ROWS 1		//Number of top-style alien rows
#define GLOBALS_NUM_MIDDLE_ALIEN_ROWS 2		//Number of middle-style alien rows
#define GLOBALS_NUM_BOTTOM_ALIEN_ROWS 2		//Number of bottom-style alien rows
#define GLOBALS_NUM_ALIEN_ROWS (GLOBALS_NUM_TOP_ALIEN_ROWS + GLOBALS_NUM_MIDDLE_ALIEN_ROWS + GLOBALS_NUM_BOTTOM_ALIEN_ROWS)
#define GLOBALS_ALIEN_SPACE_HORIZ 8			//Vertical spacing between alien rows
#define GLOBALS_ALIEN_SPACE_VERT 10			//Horizontal spacing between alien columns
#define GLOBALS_MAX_ALIEN_COL_INDEX 10		//Largest index for alien col
#define GLOBALS_MAX_ALIEN_ROW_INDEX 4		//Largest index for alien row

//Alien bullet defines
#define GLOBALS_NUM_BULLET_TYPES 2			//The number of bullet types
#define GLOBALS_MAX_ALIEN_BULLETS 4			//The max number of alien bullets that can be on the screen
#define GLOBALS_CROSS_BULLET_WIDTH 5		//The width of the cross bullet
#define GLOBALS_CROSS_BULLET_HEIGHT 6		//The height of the cross bullet
#define GLOBALS_ZIGZAG_BULLET_WIDTH 3		//Width of the zigzag bullet
#define GLOBALS_ZIGZAG_BULLET_HEIGHT 7		//Height of the zigzag bullet

//Tank defines
#define GLOBALS_TANK_START_X 99 				//Start x coord for the tank
#define GLOBALS_TANK_START_Y 400				//Start y coord for the tank
#define GLOBALS_TANK_WIDTH 15					//Width of tank
#define GLOBALS_TANK_HEIGHT 8 					//Height of tank
#define GLOBALS_TANK_MOVE_PIXELS 4	//Distance the tank moves on each press
#define GLOBALS_TANK_SCREEN_EDGE_RIGHT (GLOBALS_WIDTH_DISPLAY-(GLOBALS_TANK_WIDTH+GLOBALS_TANK_MOVE_PIXELS)*GLOBALS_MAGNIFY_MULT) //How far the tank can go on the right
#define GLOBALS_TANK_SCREEN_EDGE_LEFT GLOBALS_TANK_MOVE_PIXELS //Bumper for the left side of the screen

//Tank bullet defines
#define GLOBALS_TANK_BULLET_OFFSET_X 12						//The x offset for placing a tank bullet
#define GLOBALS_TANK_BULLET_OFFSET_Y (GLOBALS_TANK_HEIGHT+4)		//The y offset for placing a tank bullet
#define GLOBALS_TANK_BULLET_HEIGHT 6						//The height of a tank bullet
#define GLOBALS_TANK_BULLET_WIDTH 3							//The width of a tank bullet
#define GLOBALS_TANK_BULLET_TRAVEL_DISTANCE 12				//The distance a tank bullet travels with each step

//Bunker defines
#define GLOBALS_NUM_BUNKER_BLOCKS 10

//Display defines
#define GLOBALS_MAGNIFY_MULT 2 			//Multiplier for magnifying pixels on the display so we can see them
#define GLOBALS_WIDTH_DISPLAY 640 		//Width of the display
#define GLOBALS_HEIGHT_DISPLAY 480 		//Height of the display

//for draw function
#define GLOBALS_FORCE_BLACK_BACKGROUND 1  //Draw the background of an object explicitly black
#define GLOBALS_LEAVE_BACKGROUND 0		  //Leave the background the color it is

///////////////////// TYPEDEFS AND ENUMS ////////////////////////
typedef enum {alien_guise_out, alien_guise_in} alien_guise_type;
typedef enum {aliens_move_right, aliens_move_left} alien_direction_type;
typedef enum {cross_bullet, ziggy_bullet} bullet_type;
typedef enum {bullet_guise_0, bullet_guise_1} bullet_guise_type;
typedef enum {dead_tank_guise_0, dead_tank_guise_1} dead_tank_guise_type;
typedef enum {saucer_moves_right, saucer_moves_left} saucer_direction_type;
typedef struct {int16_t x; int16_t y;} point_t;


//////////////////// FUNCTION PROTOTYPES ////////////////////////

//Getters and setters. These are self-explanatory.
void globals_setTankPosition(uint16_t val);
uint16_t globals_getTankPosition();
void globals_setAlienBlockPosition(point_t val);
point_t globals_getAlienBlockPosition();
void globals_setAlienBulletPosition(uint8_t bulletNum, point_t val);
point_t globals_getAlienBulletPosition(uint8_t bulletNum);
void globals_setAlienBulletType(uint8_t bulletNum, bullet_type type);
bullet_type globals_getAlienBulletType(uint8_t bulletNum);
void globals_setAlienBulletGuise(uint8_t bulletNum, bullet_guise_type guise);
bullet_guise_type globals_getAlienBulletGuise(uint8_t bulletNum);
uint8_t globals_isBulletActive(uint8_t bulletNumber);
void globals_setBulletStatus(uint8_t bulletNumber, uint8_t active);
uint16_t globals_getCurrentScore();
void globals_setScore(uint16_t score);
void globals_incrementScore(uint16_t plus); //increments the score to the provided value
dead_tank_guise_type globals_getDeadTankGuise();
void globals_setDeadTankGuise(dead_tank_guise_type guise);
int16_t globals_getSaucerPosition();
void globals_setSaucerPosition(int16_t position);
void globals_updateLives(uint8_t incDec);
uint8_t globals_getNumLives();

//UI functions
void globals_moveTankLeft();				//Moves the tank right
void globals_moveTankRight();				//Moves the tank left
void globals_advanceAllBullets();			//Advances all alien bullets

void globals_gameOver(); //end the game
void globals_levelCleared(); //the player beat the level


#endif /* GLOBALS_H_ */
