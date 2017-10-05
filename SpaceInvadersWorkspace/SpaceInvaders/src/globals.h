/*
 * globals.h
 *
 *  Created on: Sep 22, 2017
 *      Author: superman
 */

#ifndef GLOBALS_H_
#define GLOBALS_H_

#include <stdint.h>

//Colors
#define BLACK 0x00000000
#define GREEN 0x0000FF00
#define WHITE 0x00FFFFFF
#define RED	  0x00FF0000

//Boolean values - True and False
#define TRUE 1
#define FALSE 0

//defines for line at bottom of screen
#define BOTTOMLINE_TOP 438
#define BOTTOMLINE_WIDTH 3

//#defines for aliens
#define ALIENS_START_X 145 			//Initial x-coord for alien block
#define ALIENS_START_Y 125 			//Initial y-coord for alien block
#define ALIEN_WIDTH 12 				//Width of one alien in pixels
#define ALIEN_HEIGHT 8 				//Height of one alien in pixels
#define NUM_ALIEN_COLUMNS 11		//Number of columns of aliens
#define NUM_TOP_ALIEN_ROWS 1		//Number of top-style alien rows
#define NUM_MIDDLE_ALIEN_ROWS 2		//Number of middle-style alien rows
#define NUM_BOTTOM_ALIEN_ROWS 2		//Number of bottom-style alien rows
#define NUM_ALIEN_ROWS (NUM_TOP_ALIEN_ROWS + NUM_MIDDLE_ALIEN_ROWS + NUM_BOTTOM_ALIEN_ROWS)
#define ALIEN_SPACE_HORIZ 8			//Vertical spacing between alien rows
#define ALIEN_SPACE_VERT 10			//Horizontal spacing between alien columns
#define MAX_ALIEN_COL_INDEX 10		//Largest index for alien col
#define MAX_ALIEN_ROW_INDEX 4		//Largest index for alien row

//Alien bullet defines
#define NUM_BULLET_TYPES 2
#define MAX_ALIEN_BULLETS 4

//Tank defines
#define TANK_START_X 99 				//Start x coord for the tank
#define TANK_START_Y 400				//Start y coord for the tank
#define TANK_WIDTH 15					//Width of tank
#define TANK_HEIGHT 8 					//Height of tank
#define TANK_MOVE_PIXELS (3 * MAGNIFY_MULT)	//Distance the tank moves on each press
#define TANK_SCREEN_EDGE_RIGHT (WIDTH_DISPLAY-(TANK_WIDTH+TANK_MOVE_PIXELS)*MAGNIFY_MULT) //How far the tank can go on the right
#define TANK_SCREEN_EDGE_LEFT TANK_MOVE_PIXELS //Bumper for the left side of the screen


//Bunker defines
#define NUM_BUNKER_BLOCKS 10

//Display defines
#define MAGNIFY_MULT 2 			//Multiplier for magnifying pixels on the display so we can see them
#define WIDTH_DISPLAY 640 		//Width of the display
#define HEIGHT_DISPLAY 480 		//Height of the display

//for draw function
#define FORCE_BLACK_BACKGROUND 1
#define LEAVE_BACKGROUND 0

///////////////////// TYPEDEFS AND ENUMS ////////////////////////
typedef enum {alien_guise_out, alien_guise_in} alien_guise_type;
typedef enum {aliens_move_right, aliens_move_left} alien_direction_type;
typedef enum {cross_bullet, ziggy_bullet} bullet_type;
typedef enum {bullet_guise_0, bullet_guise_1} bullet_guise_type;
typedef struct {int16_t x; int16_t y;} point_t;


//////////////////// FUNCTION PROTOTYPES ////////////////////////

//Getters and setters
void setTankPosition(uint16_t val);
uint16_t getTankPosition();
void setAlienBlockPosition(point_t val);
point_t getAlienBlockPosition();
void setAlienBulletPosition(uint8_t bulletNum, point_t val);
point_t getAlienBulletPosition(uint8_t bulletNum);
void setAlienBulletType(uint8_t bulletNum, bullet_type type);
bullet_type getAlienBulletType(uint8_t bulletNum);
void setAlienBulletGuise(uint8_t bulletNum, bullet_guise_type guise);
bullet_guise_type getAlienBulletGuise(uint8_t bulletNum);
uint8_t isBulletActive(uint8_t bulletNumber);
void setBulletStatus(uint8_t bulletNumber, uint8_t active);
uint16_t getCurrentScore();
void setScore(uint16_t score);

//UI functions
void fireTankBullet();
void moveTankLeft();
void moveTankRight();
void moveAliens();
void killAlien(uint8_t alien);
void advanceAllBullets();
void eraseAllAliens();


#endif /* GLOBALS_H_ */
