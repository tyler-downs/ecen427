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

typedef enum {alien_guise_out, alien_guise_in} alien_guise_type;
typedef enum {aliens_move_right, aliens_move_left} alien_direction_type;

typedef struct {int16_t x; int16_t y;} point_t;
typedef enum {cross_bullet, ziggy_bullet} bullet_type;

void setTankPosition(uint16_t val);
uint16_t getTankPosition();

void setTankBulletPosition(point_t val);
point_t getTankBulletPosition();

void setAlienBlockPosition(point_t val);
point_t getAlienBlockPosition();

void setAlienBulletPosition0(point_t val, bullet_type bul);
point_t getAlienBulletPosition0();

void setAlienBulletPosition1(point_t val, bullet_type bul);
point_t getAlienBulletPosition1();

void setAlienBulletPosition2(point_t val, bullet_type bul);
point_t getAlienBulletPosition2();

void setAlienBulletPosition3(point_t val, bullet_type bul);
point_t getAlienBulletPosition3();

void erodeBunker(uint8_t bunkerIndex, uint8_t blockIndex);
uint8_t getBunkerErosionState(uint8_t bunkerIndex, uint8_t blockIndex);

uint16_t getCurrentScore();
void setScore(uint16_t score);

//UI functions
void fireTankBullet();
void moveTankLeft();
void moveTankRight();
void moveAliens();
void killAlien(uint8_t alien);
void fireRandomAlienMissile();
void updateBulletPositions();
void eraseAllAliens();


#endif /* GLOBALS_H_ */
