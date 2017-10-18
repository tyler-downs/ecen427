/*
 * counters.c
 *
 *  Created on: Oct 13, 2017
 *      Author: superman
 */

#include "counters.h"
#include "bitmaps.h"
#include "aliens.h"
#include "bullets.h"

//There is one interrupt every 10ms
#define MOVE_ALIENS_COUNTER_MAX 90 //how much time passes between alien movements
#define MOVE_BULLETS_COUNTER_MAX 1 //how much time passes between moving the bullets (controls bullet speed)
#define ALIEN_EXPLODE_COUNTER_MAX 5 //how long the alien explosion stays on screen after an alien is shot
#define TANK_DEAD_COUNTER_MAX 100 //how long the tank stays dead
#define TANK_DEAD_GUISE_COUNTER_MAX 25 //time between switching between the two dead tank guises
#define TANK_MOVE_COUNTER_MAX 2 //time between moving the tank if the button is pressed (controls tank movement speed)
#define INITIAL_BULLET_WAIT_TIME 500 //how long until the first alien bullet is fired
#define SPACESHIP_WAIT_TIME 2000 //how long until the spaceship crosses the screen again
#define SPACESHIP_MOVE_COUNTER_MAX 30 //how long to wait until moving the spaceship again (controls spaceship movement speed)

u32 moveAliensTickCtr = 0; //Counter for when to move the aliens
u32 bulletMoveTickCtr = 0; //counter for when to advance the bullets that are on the screen
u32 alienExplodeCtr = 0; //counter for when to erase the alien explosion
u32 tankDeadCtr = 0; //counter for when to revive tank
u32 tankDeadGuiseCtr = 0; //counter for when to switch dead tank guises
u32 tankMoveCtr = 0; //counter for when to move the tank again
u32 fireNewAlienBulletMaxTime = INITIAL_BULLET_WAIT_TIME;  //The time between bullets coming out will be randomized
u32 fireNewAlienBulletCtr = 0; //counter for when to move the tank again
u32 spaceShipLaunchCtr = 0; //counter for when to launch the spaceship again
u32 moveSpaceShipCtr = 0; //counter for when to move spaceship (controls movement speed)

point_t alienExplosionLocation; //the top-left pixel of where to draw the alien explosion, and later erase it
uint8_t alienExplosionExists = FALSE; //signifies if the explosion is currently on the screen

//flags
u8 tankDead = 0; //flag to signal if the tank is dead
u8 spaceShipLaunched = 0; //flag to signal if spaceship is launched

void updateAlienTickCounter()
{
	moveAliensTickCtr++;
	if (moveAliensTickCtr > MOVE_ALIENS_COUNTER_MAX) //if it's time to move the aliens
	{
		moveAliensTickCtr = 0;
		moveAliens();
		//erode bunker blocks if necessary

		//if they've reached the bottom of the screen //ADDED TO moveAliens(), moveDownOneRow();
			//game over
	}
}

//if the center button is pressed, the tank bullet will fire
void onFireTankBulletButtonPress()
{
	//if the center button is pressed
	if (centerButtonPressed())
	{
		fireTankBullet();
	}
}

void updateBulletMoveCounter()
{
	bulletMoveTickCtr++;
	if (bulletMoveTickCtr > MOVE_BULLETS_COUNTER_MAX)//if the timer is expired
	{
		bulletMoveTickCtr = 0;//reset bullet move timer
		if (tankBulletOnScreen())
		{
			int8_t alienHit = tankBulletWillHitAlien(); //check if an alien will get hit
			int8_t bunkerHit = tankBulletWillHitBunker(); //check if a bunker will get hit

			if (alienHit > NO_HIT)//if tank bullet will hit an alien on next move (there is white in the rectangle ahead)
			{
				xil_printf("ALIEN HIT!");//TEST
				killAlien(alienHit); //kill the alien in the array
				//draw the alien explosion (and save its location)
				alienExplosionLocation = getAlienLocation((uint8_t) alienHit);
				drawObject(alien_explosion_12x10, ALIEN_EXPLOSION_WIDTH, ALIEN_EXPLOSION_HEIGHT, alienExplosionLocation, WHITE, FORCE_BLACK_BACKGROUND);
				alienExplosionExists = TRUE; //set global
				alienExplodeCtr = 0;//reset explosion timer

				eraseEntireTankBullet();//erase the bullet
				disableTankBullet(); //reset global

				incrementScore(alienPoints(alienHit));//increment the score
				//if that was the last alien, LEVEL CLEARED! //ADDED TO killAlien()
			}
			/*else if (tankBulletWillHitSpaceship())//else if the bullet will hit the spaceship
			{
				//erase the space ship
				//set the spaceship location off the screen
				//erase the bullet
				//flash random score
				//increment score
				//disable spaceshipLaunched global
			}
			else if (bunkerHit > NO_HIT)//else if the bullet will hit a bunker
			{
				xil_printf("BUNKER HIT!");//TEST
				//erode the bunker
				//erase the bullet
			}
			else
			{
				//advance the tank bullet
				//advanceTankBullet();
			}*/
			advanceTankBullet(); //TEST
		}
		advanceAllAlienBullets(); //TEST
		//for each alien bullet on screen
			//if alien bullet will hit tank(and it's not dead already)
				//draw the dead tank
				//reset the dead tank timer and dead tank guise timer
				//disable tank movement, firing bullets (both tank bullets and alien bullets), or dying again(by setting dead variable)
				//remove a life
					//if there are no 0 lives, it's game over
				//erase alien bullet

			//else if alien bullet will hit dead tank
				//erase bullet

			//else if alien bullet will hit bunker
				//erode bunker
				//erase bullet

			//else
				//advance alien bullet
	}

}

void updateAlienExplodeCounter()
{
	alienExplodeCtr++;
	if(alienExplodeCtr > ALIEN_EXPLODE_COUNTER_MAX)//if the timer has expired
	{
		drawObject(alien_explosion_12x10, ALIEN_EXPLOSION_WIDTH, ALIEN_EXPLOSION_HEIGHT, alienExplosionLocation, BLACK, FORCE_BLACK_BACKGROUND);//erase the alien explosion
		alienExplosionExists = FALSE; //disable the global
	}
}

void updateTankDeadCounter()
{
	tankDeadCtr++;
	//if the timer has expired
		//redraw the live tank
		//reenable tank movement, bullet firing, and dying again (by disabling dead variable)
}

void updateTankDeadGuiseCounter()
{
	tankDeadGuiseCtr++;
	//if the tank is still dead and the timer has expired //need "dead" global variable
		//switch tank guises
		//reset the tankDeadGuiseCtr.
}

void updateTankMoveCounter()
{
	if(tankMoveCtr <= TANK_MOVE_COUNTER_MAX) //if the button is not pressed, be ready to move as soon as it is. Don't want to roll over or go out of bounds
		tankMoveCtr++;
	if (tankMoveCtr > TANK_MOVE_COUNTER_MAX)
	{
		if (leftButtonPressed() && !rightButtonPressed())//if left button pressed (and only left)
		{
			moveTankLeft(); //move the tank left
			tankMoveCtr = 0; //reset tankMoveCtr
		}
		else if (rightButtonPressed() && !leftButtonPressed()) //if the right button is pressed (and only right)
		{
			moveTankRight(); //move the tank right
			tankMoveCtr = 0; //reset tankMoveCtr
		}
	}
}

#define MAX_TIME_BETWEEN_ALIEN_BULLETS 300 //at least one alien bullet should fire every 3 seconds
void updateFireNewAlienBulletCtr()
{
	fireNewAlienBulletCtr++;
	if (fireNewAlienBulletCtr > fireNewAlienBulletMaxTime)
	{
		fireRandomAlienBullet(); //fire a random alien bullet
		fireNewAlienBulletMaxTime = rand() % MAX_TIME_BETWEEN_ALIEN_BULLETS; //set fireNewAlienBulletMaxTime to a new random number
		fireNewAlienBulletCtr = 0;//reset fireNewAlienBulletCtr
	}
}

void updateSpaceShipLaunchCtr()
{
	spaceShipLaunchCtr++;
	if (spaceShipLaunchCtr > SPACESHIP_WAIT_TIME)
	{
		//set spaceship launched global variable //it's our responsibility to make sure the ship is off the screen before launching again
		//move space ship
		//reset MoveSpaceShipCtr
	}
}

void updateMoveSpaceShipCtr()
{
	//if the spaceship has been launched (check global variable)
		//increment MoveSpaceShipCtr
		//if (moveSpaceShipCtr > SPACESHIP_MOVE_COUNTER_MAX)
			//move spaceship in direction specified by global enum variable
			//reset moveSpaceShipCtr
			//if the spaceship is completely off the screen
				//disable "launched" global variable
				//switch direction in global enum variable

}

void updateAllCounters()
{
	//MIGHT NEED TO CHANGE ORDER
	updateBulletMoveCounter();
	updateAlienExplodeCounter();
	updateAlienTickCounter();
	updateTankMoveCounter();
	onFireTankBulletButtonPress();
	updateMoveSpaceShipCtr();
	updateTankDeadCounter();
	updateTankDeadGuiseCounter();
	updateFireNewAlienBulletCtr();
	updateSpaceShipLaunchCtr();


}