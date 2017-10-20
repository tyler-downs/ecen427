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
#include "saucer.h"
#include "render.h"


//There is one interrupt every 10ms
#define MOVE_ALIENS_COUNTER_MAX 45 //how much time passes between alien movements //TODO: this should be 90
#define MOVE_BULLETS_COUNTER_MAX 2 //how much time passes between moving the bullets (controls bullet speed)
#define ALIEN_EXPLODE_COUNTER_MAX 10 //how long the alien explosion stays on screen after an alien is shot
#define TANK_DEAD_COUNTER_MAX 100 //how long the tank stays dead
#define TANK_DEAD_GUISE_COUNTER_MAX 25 //time between switching between the two dead tank guises
#define TANK_MOVE_COUNTER_MAX 1 //time between moving the tank if the button is pressed (controls tank movement speed)
#define INITIAL_BULLET_WAIT_TIME 500 //how long until the first alien bullet is fired
#define SAUCER_WAIT_TIME 1000 //how long until the SAUCER crosses the screen again
#define SAUCER_MOVE_COUNTER_MAX 3 //how long to wait until moving the SAUCER again (controls SAUCER movement speed)
#define SAUCER_SCORE_COUNTER_MAX 50 //how long the saucer score will remain on the screen
#define GAME_OVER_COUNTER_MAX 300 //how long before you can restart the game

u32 moveAliensTickCtr = 0; //Counter for when to move the aliens
u32 bulletMoveTickCtr = 0; //counter for when to advance the bullets that are on the screen
u32 alienExplodeCtr = 0; //counter for when to erase the alien explosion
u32 tankDeadCtr = 0; //counter for when to revive tank
u32 tankDeadGuiseCtr = 0; //counter for when to switch dead tank guises
u32 tankMoveCtr = 0; //counter for when to move the tank again
u32 fireNewAlienBulletMaxTime = INITIAL_BULLET_WAIT_TIME;  //The time between bullets coming out will be randomized
u32 fireNewAlienBulletCtr = 0; //counter for when to move the tank again
u32 saucerLaunchCtr = 0; //counter for when to launch the saucer again
u32 moveSaucerCtr = 0; //counter for when to move saucer (controls movement speed)
u32 saucerScoreCtr = 0; //counter for the saucer score remaining on the screen
uint8_t randScore; //the random score used by the saucer when it DIES
u32 gameOverCtr = 0; //the counter for the delay between game over and restart

point_t alienExplosionLocation; //the top-left pixel of where to draw the alien explosion, and later erase it
uint8_t alienExplosionExists = FALSE; //signifies if the explosion is currently on the screen
uint8_t saucerScoreOnScreen = FALSE; //true when the saucer score is on the screen
uint8_t levelClearedState = FALSE;
uint8_t gameOverState = FALSE;

//flags
u8 tankDead = FALSE; //flag to signal if the tank is dead
u8 saucerLaunched = FALSE; //flag to signal if saucer is launched

void updateAlienTickCounter()
{
	moveAliensTickCtr++;
	if (moveAliensTickCtr > MOVE_ALIENS_COUNTER_MAX) //if it's time to move the aliens
	{
		moveAliensTickCtr = 0;
		aliens_moveAliens();
		//erode bunker blocks if necessary
		//if the aliens are about to hit the bunkers
			//figure out what bunker to erode
			//erode the bunker block to 0
		//if they've reached the bottom of the screen //ADDED TO moveAliens(), moveDownOneRow();
		if (aliens_getBottomOfAliens() >= BUNKER_START_Y + BUNKER_HEIGHT)
		{
			//game over
			gameOver();
		}


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

//decrements lives and removes the tank on the top of the display
void removeLife()
{
	//decrement global lives
	updateLives(DEC);
	//remove the tank from the lives display
	updateLivesDisplay(DEC);
	//if there are zero lives, gameOver()
	if (getNumLives() == 0)
	{
		gameOver();
	}
}



void addLife()
{
	//increment global lives
	updateLives(INC);
	//add the tank from the lives display
	updateLivesDisplay(INC);
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

			if (alienHit > NO_HIT && !alienExplosionExists)//if tank bullet will hit an alien on next move (there is white in the rectangle ahead)
			{
				aliens_killAlien(alienHit); //kill the alien in the array
				//draw the alien explosion (and save its location)
				alienExplosionLocation = aliens_getAlienLocation((uint8_t) alienHit);
				drawObject(alien_explosion_12x10, ALIEN_EXPLOSION_WIDTH, ALIEN_EXPLOSION_HEIGHT, alienExplosionLocation, WHITE, LEAVE_BACKGROUND);
				alienExplosionExists = TRUE; //set global
				alienExplodeCtr = 0;//reset explosion timer

				eraseEntireTankBullet();//erase the bullet
				disableTankBullet(); //reset global

				incrementScore(aliens_alienPoints(alienHit));//increment the score, and update the screen
				//if that was the last alien, LEVEL CLEARED! //ADDED TO killAlien()
			}
			else if (tankBulletWillHitSaucer())//else if the bullet will hit the saucer
			{
				//erase the space ship
				eraseSaucer();
				//xil_printf("when saucer is killed, position = %d\n\r", getSaucerPosition());
				//erase and disable the bullet
				eraseEntireTankBullet();
				disableTankBullet();
				//flash random score
				randScore = rand() % 4;
				randScore = (randScore + 1) * 50;
				xil_printf("randScore = %d\n\r", randScore);
				//increment score
				printScoreOnSaucerDeath(randScore, GREEN);
				incrementScore(randScore);
				//set flag to true
				saucerScoreOnScreen = TRUE;

				//disable saucerLaunched global
				saucerLaunched = FALSE;
			}
			else if (bunkerHit > NO_HIT)//else if the bullet will hit a bunker
			{
				erodeBunkerBlockByNum(bunkerHit);//erode the bunker
				eraseEntireTankBullet();//erase the bullet
				disableTankBullet(); //reset global
			}
			else
			{
				//advance the tank bullet
				advanceTankBullet();
			}

		}
		//advanceAllAlienBullets(); //TEST
		/*//returns true if the specified alien bullet will hit the tank on its next move
		uint8_t alienBulletWillHitTank(uint8_t bulletNum)*/
		//for each alien bullet on screen
		uint8_t i;
		for (i = 0; i < MAX_ALIEN_BULLETS; i++)
		{
			if (!isBulletActive(i)) {continue;}

			int8_t bunkerHit = alienBulletWillHitBunkerBlock(i);

			//if alien bullet will hit tank(and it's not dead already)
			if (alienBulletWillHitTank(i))
			{
				//draw the dead tank
				drawObject(tank_dead_guise0_15x8, TANK_WIDTH, TANK_HEIGHT, (point_t){getTankPosition(), TANK_START_Y}, GREEN, FORCE_BLACK_BACKGROUND);
				//reset the dead tank timer and dead tank guise timer
				tankDeadCtr = 0;
				tankDeadGuiseCtr = 0;
				//erase alien bullet
				eraseAlienBullet(getAlienBulletType(i), getAlienBulletGuise(i), getAlienBulletPosition(i));
				//deactivate the bullet
				setBulletStatus(i, FALSE);
				//disable tank movement, firing bullets (both tank bullets and alien bullets), or dying again(by setting dead variable)
				tankDead = TRUE;
				//remove a life
				removeLife();
				xil_printf("Removed life. Lives: %d  Bullet: %d\n\r", getNumLives(), i);
			}

			//else if alien bullet will hit dead tank
				//erase bullet

			//else if alien bullet will hit bunker

			else if (bunkerHit != NO_HIT)
			{
				//erode bunker
				erodeBunkerBlockByNum(bunkerHit);
				//erase bullet
				eraseAlienBullet(getAlienBulletType(i), getAlienBulletGuise(i), getAlienBulletPosition(i));
				//deactivate the bullet
				setBulletStatus(i, FALSE);
			}

			else  //advance alien bullet
			{
				advanceOneAlienBullet(i);
			}

		} //end for loop through 4 alien bullets

	}

}

void updateAlienExplodeCounter()
{
	alienExplodeCtr++;
	if(alienExplosionExists && (alienExplodeCtr > ALIEN_EXPLODE_COUNTER_MAX))//if the timer has expired, and there is an explosion on the screen
	{
		drawObject(alien_explosion_12x10, ALIEN_EXPLOSION_WIDTH, ALIEN_EXPLOSION_HEIGHT, alienExplosionLocation, BLACK, FORCE_BLACK_BACKGROUND);//erase the alien explosion
		alienExplosionExists = FALSE; //disable the global
	}
}

void updateTankDeadCounter()
{
	tankDeadCtr++;
	//if the timer has expired
	if (tankDeadCtr >= TANK_DEAD_COUNTER_MAX)
	{
		tankDeadCtr = 0;
		if (tankDead)
		{
			//redraw the live tank
			drawObject(tank_15x8, TANK_WIDTH, TANK_HEIGHT, (point_t){getTankPosition(), TANK_START_Y}, GREEN, FORCE_BLACK_BACKGROUND);
			//reenable tank movement, bullet firing, and dying again (by disabling dead variable)
			tankDead = FALSE;
			xil_printf("tankDead = FALSE in updateTankDeadCounter()\n\r");
		}

	}

}


//switches the guise of the dead tank
void switchDeadTankGuises()
{
	//if it's 0, make it 1
	if (getDeadTankGuise() == dead_tank_guise_0)
	{
		setDeadTankGuise(dead_tank_guise_1);
	}
	//if it's 1, make it 0
	else
	{
		setDeadTankGuise(dead_tank_guise_0);
	}
}

void drawDeadTank()
{
	//if it's guise 0, draw that one
	if (getDeadTankGuise() == dead_tank_guise_0)
	{
		drawObject(tank_dead_guise0_15x8, TANK_WIDTH, TANK_HEIGHT, (point_t){getTankPosition(), TANK_START_Y}, GREEN, FORCE_BLACK_BACKGROUND);
	}
	else //if it's guise 1, draw that one
	{
		drawObject(tank_dead_guise1_15x8, TANK_WIDTH, TANK_HEIGHT, (point_t){getTankPosition(), TANK_START_Y}, GREEN, FORCE_BLACK_BACKGROUND);
	}
}

void updateTankDeadGuiseCounter()
{
	tankDeadGuiseCtr++;
	//if the tank is still dead and the timer has expired //need "dead" global variable
	if (tankDead && tankDeadGuiseCtr >= TANK_DEAD_GUISE_COUNTER_MAX)
	{
		//switch tank guises
		switchDeadTankGuises();
		//draw the dead tank in that guise
		drawDeadTank();
		//reset the tankDeadGuiseCtr.
		tankDeadGuiseCtr = 0;
	}

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

void updateSaucerLaunchCtr()
{
	saucerLaunchCtr++;
	if (saucerLaunchCtr > SAUCER_WAIT_TIME)
	{
		saucerLaunchCtr = 0;
		if (saucerLaunched == FALSE)
		{
			//set saucer launched global variable //it's our responsibility to make sure the ship is off the screen before launching again
			saucerLaunched = TRUE;
			//init ship depending on direction
			if (getSaucerDirection() == saucer_moves_left)
			{
				initSaucerMovingLeft();
			}
			else
			{
				initSaucerMovingRight();
			}
			//reset moveSaucerCtr
			moveSaucerCtr = 0;
		}
	}
}

#define NEGATIVE_WIDTH_OF_SAUCER (-1 * SAUCER_WIDTH*MAGNIFY_MULT)
//Returns TRUE if the saucer is off screen, else returns FALSE
uint8_t isSaucerOffScreen()
{
	if ((getSaucerPosition() < NEGATIVE_WIDTH_OF_SAUCER) || (getSaucerPosition() > (WIDTH_DISPLAY + SAUCER_WIDTH)))
	{
		xil_printf("Saucer position in isSaucerOffScreen: %d\n\r", getSaucerPosition());
		return TRUE;
	}
	else return FALSE;
}

void setGameOverState()
{
	gameOverState = TRUE;
}


void updateMoveSaucerCtr()
{
	//if the Saucer has been launched (check global variable)
	if (saucerLaunched)
	{
		//increment MoveSaucerCtr
		moveSaucerCtr++;
		//xil_printf("moveSaucerCounter = %d\n\r", moveSaucerCtr);
		if (moveSaucerCtr > SAUCER_MOVE_COUNTER_MAX)
		{
			//move Saucer in direction specified by global enum variable
			if (getSaucerDirection() == saucer_moves_left)
			{
				moveSaucerLeft();
				//printf("Moving saucer left\n\r");
			}
			else
			{
				moveSaucerRight();
				//printf("Moving saucer right\n\r");
			}
			//reset moveSaucerCtr
			moveSaucerCtr = 0;
			saucerLaunchCtr = 0;
			//if the Saucer is completely off the screen
			if (isSaucerOffScreen())
			{
				//disable "launched" global variable
				saucerLaunched = FALSE;
				//switch direction in global enum variable
				switchSaucerMoveDirection();
			}

		}

	}


}

void updateSaucerScoreCounter()
{
	if (saucerScoreOnScreen)
	{
		//increment the saucer score counter
		saucerScoreCtr++;
		//if the score counter is above the max
		if (saucerScoreCtr > SAUCER_SCORE_COUNTER_MAX)
		{
			//reset the counter
			saucerScoreCtr = 0;
			//erase the score
			printScoreOnSaucerDeath(randScore, BLACK);
			//set the flag to false
			saucerScoreOnScreen = FALSE;
		}
	}
}

//Handles the starting over of the game
void restartGameOnGameOver()
{
	gameOverState = FALSE;
	//erase the game over stuff
	drawGameOverScreen(BLACK);
	//erase all remaining aliens
	aliens_eraseAllAliens();
	//revive the aliens
	aliens_reviveAllAliens();
	//revive the bunkers
	reviveAllBunkers();
	//init the display again
	setScore(0); //initialize the score
	updateScoreDisplay(0); //draw the score

	//draw tank lives
	int n;
	for(n = 0; n < NUM_LIVES_INIT; n++) //Just draw a tank three times at the top of the screen
	{
		updateLivesDisplay(INC);
		updateLives(INC); //update the global variable tracking number of lives
	}

	//redraw the live tank
	drawObject(tank_15x8, TANK_WIDTH, TANK_HEIGHT, (point_t){getTankPosition(), TANK_START_Y}, GREEN, FORCE_BLACK_BACKGROUND);
	//reenable tank movement, bullet firing, and dying again (by disabling dead variable)
	tankDead = FALSE;

	//drawTankInit(); //draw the tank
	drawBunkersInit(); //draw the bunkers
	drawAliensInit(); //draw the block of aliens
}

void updateAllCounters()
{
	//MIGHT NEED TO CHANGE ORDER
	if (gameOverState)
	{
		gameOverCtr++;
		if((centerButtonPressed() || leftButtonPressed() || rightButtonPressed()) && gameOverCtr >= GAME_OVER_COUNTER_MAX)
		{
			gameOverCtr = 0;
			restartGameOnGameOver();
			return;
		}
		else return;
	}
	if (tankDead)
	{
		updateTankDeadCounter();
		updateTankDeadGuiseCounter();
	}
	else
	{
		updateTankMoveCounter();
		onFireTankBulletButtonPress();
		updateBulletMoveCounter();
		updateAlienExplodeCounter();
		updateSaucerScoreCounter();
		updateAlienTickCounter();
		updateMoveSaucerCtr();
		updateFireNewAlienBulletCtr();
		updateSaucerLaunchCtr();
	}
}
