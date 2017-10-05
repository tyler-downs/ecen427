/*
 * globals.h
 *
 *  Created on: Sep 22, 2017
 *      Author: superman
 */

#ifndef GLOBALS_H_
#define GLOBALS_H_

#include <stdint.h>

#define BLACK 0x00000000
#define GREEN 0x0000FF00
#define WHITE 0x00FFFFFF
#define RED	  0x00FF0000

#define TRUE 1
#define FALSE 0

//defines for line at bottom of screen
#define BOTTOMLINE_TOP 438
#define BOTTOMLINE_WIDTH 3

//#defines for aliens
#define ALIENS_START_X 145
#define ALIENS_START_Y 125
#define ALIEN_WIDTH 12
#define ALIEN_HEIGHT 8
#define NUM_ALIEN_COLUMNS 11
#define NUM_TOP_ALIEN_ROWS 1
#define NUM_MIDDLE_ALIEN_ROWS 2
#define NUM_BOTTOM_ALIEN_ROWS 2
#define NUM_ALIEN_ROWS (NUM_TOP_ALIEN_ROWS + NUM_MIDDLE_ALIEN_ROWS + NUM_BOTTOM_ALIEN_ROWS)
#define ALIEN_SPACE_HORIZ 8
#define ALIEN_SPACE_VERT 10
#define MAX_ALIEN_COL_INDEX 10
#define MAX_ALIEN_ROW_INDEX 4

//Tank defines
#define TANK_START_X 99
#define TANK_START_Y 400
#define TANK_WIDTH 15
#define TANK_HEIGHT 8
#define TANK_MOVE_PIXELS (3 * MAGNIFY_MULT)
#define TANK_SCREEN_EDGE_RIGHT (WIDTH_DISPLAY-(TANK_WIDTH+TANK_MOVE_PIXELS)*MAGNIFY_MULT)

//Display defines
#define MAGNIFY_MULT 2
#define WIDTH_DISPLAY 640
#define HEIGHT_DISPLAY 480
//for draw function
#define FORCE_BLACK_BACKGROUND 1
#define LEAVE_BACKGROUND 0

typedef enum {alien_guise_out, alien_guise_in} alien_guise_type;
typedef enum {aliens_move_right, aliens_move_left} alien_direction_type;

typedef struct {int16_t x; int16_t y;} point_t;
#define NUM_BULLET_TYPES 2
typedef enum {cross_bullet, ziggy_bullet} bullet_type;
typedef enum {bullet_guise_0, bullet_guise_1} bullet_guise_type;

void setTankPosition(uint16_t val);
uint16_t getTankPosition();

void setAlienBlockPosition(point_t val);
point_t getAlienBlockPosition();

#define MAX_ALIEN_BULLETS 4

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
