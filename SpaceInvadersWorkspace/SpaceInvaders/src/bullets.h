/*
 * bullets.h
 *
 *  Created on: Oct 3, 2017
 *      Author: superman
 */

#ifndef BULLETS_H_
#define BULLETS_H_
#include "globals.h"
#include "bitmaps.h"
#include "render.h"
#include "aliens.h"

//Defines

//Variables
uint8_t tankBulletExists = FALSE;

//Function Prototypes
void fireTankBullet();
void advanceTankBullet();
void setTankBulletPosition(point_t val);
point_t getTankBulletPosition();
void eraseEntireTankBullet();
void fireRandomAlienBullet();
void advanceAllAlienBullets();

#endif /* BULLETS_H_ */
