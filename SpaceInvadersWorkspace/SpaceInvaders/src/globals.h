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

typedef struct {uint16_t x; uint16_t y;} point_t;
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

//UI functions
void fireTankBullet();
void moveTankLeft();
void moveTankRight();
void moveAliens();
void killAlien(uint8_t alien);
void fireRandomAlienMissile();
void updateBulletPositions();


#endif /* GLOBALS_H_ */
