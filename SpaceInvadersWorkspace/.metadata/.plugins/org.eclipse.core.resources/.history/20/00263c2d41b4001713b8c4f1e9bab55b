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
#define HALF_ALIEN (ALIEN_WIDTH / 2)	//Half the width of an alien
#define ALIEN_BULLET_TRAVEL_DISTANCE TANK_BULLET_TRAVEL_DISTANCE //Distance the alien bullet travels on each step
#define ALIEN_BULLET_DEACTIVATE_BUFFER (ALIEN_BULLET_TRAVEL_DISTANCE/2 - 1)	//Distance from the bottom line the alien bullets will disappear

//////////////// FUNCTION PROTOTYPES ///////////////////
//Fires a bullet from the tank
void fireTankBullet();

//Advance the tank bullet one step on the display
void advanceTankBullet();

//Setter for the tank position global variable
void setTankBulletPosition(point_t val);

//Getter for the tank position global variable
point_t getTankBulletPosition();

//Erases a tank bullet
void eraseEntireTankBullet();

//Fires a bullet from a random alien
void fireRandomAlienBullet();

//Advances all bullets on the screen
void advanceAllAlienBullets();

//if the tank bullet will hit an alien on its next move, this will return the alien number. Otherwise it will return -1.
int8_t tankBulletWillHitAlien();

//returns true if the tank bullet will hit the spaceship on its next move
uint8_t tankBulletWillHitSpaceship();

//if the tank bullet will hit a bunker on its next move, this will return the bunker number. Otherwise it will return -1.
int8_t tankBulletWillHitBunker();

//returns true if the specified alien bullet will hit the tank on its next move
uint8_t alienBulletWillHitTank(uint8_t bulletNum);

//if the specified alien bullet will hit a bunker on its next move, this will return the bunker number. Otherwise it will return -1.
int8_t alienBulletWillHitBunkerBlock(uint8_t bulletNum);

#endif /* BULLETS_H_ */
