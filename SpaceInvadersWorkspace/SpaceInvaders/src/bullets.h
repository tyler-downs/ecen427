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

//////////////////// DEFINES ///////////////////////////
#define BULLETS_ALIEN_BULLET_TRAVEL_DISTANCE (GLOBALS_TANK_BULLET_TRAVEL_DISTANCE/2) //Distance the alien bullet travels on each step
#define BULLETS_ALIEN_BULLET_DEACTIVATE_BUFFER (BULLETS_ALIEN_BULLET_TRAVEL_DISTANCE/2 - 1)	//Distance from the bottom line the alien bullets will disappear
#define BULLETS_NO_HIT -1

//////////////// FUNCTION PROTOTYPES ///////////////////
//reset tankBulletExists global
void bullets_disableTankBullet();

//returns true if the tank bullet is on the screen
uint8_t bullets_tankBulletOnScreen();

//Fires a bullet from the tank
void bullets_fireTankBullet();

//Advance the tank bullet one step on the display
void bullets_advanceTankBullet();

//Setter for the tank position global variable
void bullets_setTankBulletPosition(point_t val);

//Getter for the tank position global variable
point_t bullets_getTankBulletPosition();

//Erases a tank bullet
void bullets_eraseEntireTankBullet();

//Fires a bullet from a random alien
void bullets_fireRandomAlienBullet();

//Advances all bullets on the screen
void bullets_advanceAllAlienBullets();

//if the tank bullet will hit an alien on its next move, this will return the alien number. Otherwise it will return -1.
int8_t bullets_tankBulletWillHitAlien();

//returns true if the tank bullet will hit the spaceship on its next move
uint8_t bullets_tankBulletWillHitSaucer();

//if the tank bullet will hit a bunker on its next move, this will return the bunker number. Otherwise it will return -1.
int8_t bullets_tankBulletWillHitBunker();

//returns true if the specified alien bullet will hit the tank on its next move
uint8_t bullets_alienBulletWillHitTank(uint8_t bulletNum);

//if the specified alien bullet will hit a bunker on its next move, this will return the bunker number. Otherwise it will return -1.
int8_t bullets_alienBulletWillHitBunkerBlock(uint8_t bulletNum);

#endif /* BULLETS_H_ */
