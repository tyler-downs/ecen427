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


///////////////////////// DEFINES //////////////////////////////
//There is one interrupt every 10ms
#define MOVE_ALIENS_COUNTER_MAX 90 //how much time passes between alien movements
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
#define RAND_MOD_SAUCER_SCORE 4 //used to mod the rand for the saucer score
#define RAND_MULT_SAUCER_SCORE 50 //multiply the modded rand by this to get the score
#define RAND_SCORE_OFFSET 1 //used in calculating the rand score for the saucer
#define MAX_TIME_BETWEEN_ALIEN_BULLETS 300 //at least one alien bullet should fire every 3 seconds
#define NEGATIVE_WIDTH_OF_SAUCER (-1 * SAUCER_WIDTH*GLOBALS_MAGNIFY_MULT) //used in calculating movement of saucer

#define DEATH_BUZZ_DURATION 100000000 //1 second

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
	moveAliensTickCtr++; //increment the counter
	if (moveAliensTickCtr > MOVE_ALIENS_COUNTER_MAX) //if it's time to move the aliens
	{
		//reset the counter
		moveAliensTickCtr = 0;
		//move the aliens
		aliens_moveAliens();
		//play the alien move sound
		sounds_playAlienMoveSound();
		//if they've reached the bottom of the screen //ADDED TO moveAliens(), moveDownOneRow();
		if (aliens_getBottomOfAliens() >= BUNKERS_BUNKER_START_Y + BUNKERS_BUNKER_HEIGHT)
		{
			globals_gameOver();	//game over time, baby
		}
	}
}

//If the center button is pressed, the tank bullet will fire
void onFireTankBulletButtonPress()
{
	//if the center button is pressed
	if (centerButtonPressed())
	{
		bullets_fireTankBullet(); //fire a bullet

	}
}

//Decrements lives and removes the tank on the top of the display
void removeLife()
{
	//decrement global lives
	globals_updateLives(RENDER_DEC);
	//remove the tank from the lives display
	render_updateLivesDisplay(RENDER_DEC);
	//if there are zero lives, gameOver()
	if (globals_getNumLives() == 0)
	{
		globals_gameOver(); //game over time, baby
	}
}


//adds a life to the player's lives. Not that the player has a life.
void addLife()
{
	//increment global lives
	globals_updateLives(RENDER_INC);
	//add the tank from the lives display
	render_updateLivesDisplay(RENDER_INC);
}

//Counter for handling updating the bullets, collisions, etc.
void updateBulletMoveCounter()
{
	bulletMoveTickCtr++; //inc the counter
	if (bulletMoveTickCtr > MOVE_BULLETS_COUNTER_MAX)//if the timer is expired
	{
		bulletMoveTickCtr = 0;//reset bullet move timer
		if (bullets_tankBulletOnScreen())
		{
			int8_t alienHit = bullets_tankBulletWillHitAlien(); //check if an alien will get hit
			int8_t bunkerHit = bullets_tankBulletWillHitBunker(); //check if a bunker will get hit

			if (alienHit > BULLETS_NO_HIT && !alienExplosionExists)//if tank bullet will hit an alien on next move (there is white in the rectangle ahead)
			{
				aliens_killAlien(alienHit); //kill the alien in the array
				//draw the alien explosion (and save its location)
				alienExplosionLocation = aliens_getAlienLocation((uint8_t) alienHit);
				render_drawObject(alien_explosion_12x10, ALIEN_EXPLOSION_WIDTH, ALIEN_EXPLOSION_HEIGHT, alienExplosionLocation, GLOBALS_WHITE, GLOBALS_LEAVE_BACKGROUND);

				sounds_playAlienKilledSound(); //play the alien killed explosion sound

				alienExplosionExists = TRUE; //set global
				alienExplodeCtr = 0;//reset explosion timer

				bullets_eraseEntireTankBullet();//erase the bullet
				bullets_disableTankBullet(); //reset global

				globals_incrementScore(aliens_alienPoints(alienHit));//increment the score, and update the screen
				//if that was the last alien, LEVEL CLEARED! //ADDED TO killAlien()
			}
			else if (bullets_tankBulletWillHitSaucer())//else if the bullet will hit the saucer
			{
				//erase the space ship
				saucer_eraseSaucer();
				//xil_printf("when saucer is killed, position = %d\n\r", getSaucerPosition());
				//erase and disable the bullet
				bullets_eraseEntireTankBullet();
				bullets_disableTankBullet();
				//flash random score
				randScore = rand() % RAND_MOD_SAUCER_SCORE;
				randScore = (randScore + RAND_SCORE_OFFSET) * RAND_MULT_SAUCER_SCORE;
				//increment score
				saucer_printScoreOnSaucerDeath(randScore, GLOBALS_GREEN);
				globals_incrementScore(randScore);
				//set flag to true
				saucerScoreOnScreen = TRUE;
				//disable saucerLaunched global
				saucerLaunched = FALSE;
				sounds_playAlienKilledSound(); //play the alien killed sound
			}
			else if (bunkerHit > BULLETS_NO_HIT)//else if the bullet will hit a bunker
			{
				erodeBunkerBlockByNum(bunkerHit);//erode the bunker
				bullets_eraseEntireTankBullet();//erase the bullet
				bullets_disableTankBullet(); //reset global
			}
			else
			{
				//advance the tank bullet
				bullets_advanceTankBullet();
			}

		}
		//for each alien bullet on screen
		uint8_t i;
		for (i = 0; i < GLOBALS_MAX_ALIEN_BULLETS; i++)
		{
			if (!globals_isBulletActive(i)) {continue;} //skip this iteration if the alien bullet in question is not active

			int8_t bunkerHit = bullets_alienBulletWillHitBunkerBlock(i); //check to see if it will hit the bunkers

			//if alien bullet will hit tank(and it's not dead already)
			if (bullets_alienBulletWillHitTank(i))
			{
				//draw the dead tank
				render_drawObject(tank_dead_guise0_15x8, GLOBALS_TANK_WIDTH, GLOBALS_TANK_HEIGHT, (point_t){globals_getTankPosition(), GLOBALS_TANK_START_Y}, GLOBALS_GREEN, GLOBALS_FORCE_BLACK_BACKGROUND);
				//reset the dead tank timer and dead tank guise timer
				tankDeadCtr = 0;
				tankDeadGuiseCtr = 0;
				//erase alien bullet
				eraseAlienBullet(globals_getAlienBulletType(i), globals_getAlienBulletGuise(i), globals_getAlienBulletPosition(i));
				//deactivate the bullet
				globals_setBulletStatus(i, FALSE);
				//disable tank movement, firing bullets (both tank bullets and alien bullets), or dying again(by setting dead variable)
				tankDead = TRUE;
				//remove a life
				removeLife();
				//play the tank death sound
				sounds_playTankDeathSound();
				buzzer_setDelay(DEATH_BUZZ_DURATION); //set buzz length
				buzzer_buzz(); //buzz
			}
			//else if alien bullet will hit bunker
			else if (bunkerHit != BULLETS_NO_HIT)
			{
				//erode bunker
				erodeBunkerBlockByNum(bunkerHit);
				//erase bullet
				eraseAlienBullet(globals_getAlienBulletType(i), globals_getAlienBulletGuise(i), globals_getAlienBulletPosition(i));
				//deactivate the bullet
				globals_setBulletStatus(i, FALSE);
			}
			else  //advance alien bullet
			{
				advanceOneAlienBullet(i);
			}

		} //end for loop through 4 alien bullets
	}
}

//Counter updater for the alien explosion on the screen
void updateAlienExplodeCounter()
{
	alienExplodeCtr++; //inc the counter
	if(alienExplosionExists && (alienExplodeCtr > ALIEN_EXPLODE_COUNTER_MAX))//if the timer has expired, and there is an explosion on the screen
	{
		//erase the alien explosion
		render_drawObject(alien_explosion_12x10, ALIEN_EXPLOSION_WIDTH, ALIEN_EXPLOSION_HEIGHT, alienExplosionLocation, GLOBALS_BLACK, GLOBALS_FORCE_BLACK_BACKGROUND);
		alienExplosionExists = FALSE; //disable the global
	}
}

//Counter updater for the dead tank counter
void updateTankDeadCounter()
{
	tankDeadCtr++; //inc the counter
	//if the timer has expired
	if (tankDeadCtr >= TANK_DEAD_COUNTER_MAX)
	{
		tankDeadCtr = 0;
		if (tankDead) //if the tank is actually dead
		{
			//redraw the live tank
			render_drawObject(tank_15x8, GLOBALS_TANK_WIDTH, GLOBALS_TANK_HEIGHT, (point_t){globals_getTankPosition(), GLOBALS_TANK_START_Y}, GLOBALS_GREEN, GLOBALS_FORCE_BLACK_BACKGROUND);
			//reenable tank movement, bullet firing, and dying again (by disabling dead variable)
			tankDead = FALSE;
		}
	}
}

//switches the guise of the dead tank
void switchDeadTankGuises()
{
	//if it's 0, make it 1
	if (globals_getDeadTankGuise() == dead_tank_guise_0)
	{
		globals_setDeadTankGuise(dead_tank_guise_1);
	}
	//if it's 1, make it 0
	else
	{
		globals_setDeadTankGuise(dead_tank_guise_0);
	}
}

//Draws the dead tank in its correct guise
void drawDeadTank()
{
	//if it's guise 0, draw that one
	if (globals_getDeadTankGuise() == dead_tank_guise_0)
	{
		render_drawObject(tank_dead_guise0_15x8, GLOBALS_TANK_WIDTH, GLOBALS_TANK_HEIGHT, (point_t){globals_getTankPosition(), GLOBALS_TANK_START_Y}, GLOBALS_GREEN, GLOBALS_FORCE_BLACK_BACKGROUND);
	}
	else //if it's guise 1, draw that one
	{
		render_drawObject(tank_dead_guise1_15x8, GLOBALS_TANK_WIDTH, GLOBALS_TANK_HEIGHT, (point_t){globals_getTankPosition(), GLOBALS_TANK_START_Y}, GLOBALS_GREEN, GLOBALS_FORCE_BLACK_BACKGROUND);
	}
}

//Counter updater for the dead tank guise counter
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

//Counter updater for the tank move counter
void updateTankMoveCounter()
{
	if(tankMoveCtr <= TANK_MOVE_COUNTER_MAX) //if the button is not pressed, be ready to move as soon as it is. Don't want to roll over or go out of bounds
		tankMoveCtr++;
	if (tankMoveCtr > TANK_MOVE_COUNTER_MAX)
	{
		if (leftButtonPressed() && !rightButtonPressed())//if left button pressed (and only left)
		{
			globals_moveTankLeft(); //move the tank left
			tankMoveCtr = 0; //reset tankMoveCtr
		}
		else if (rightButtonPressed() && !leftButtonPressed()) //if the right button is pressed (and only right)
		{
			globals_moveTankRight(); //move the tank right
			tankMoveCtr = 0; //reset tankMoveCtr
		}
	}
}

//Facilitates the firing of alien bullets, including timing of them
void updateFireNewAlienBulletCtr()
{
	fireNewAlienBulletCtr++;
	if (fireNewAlienBulletCtr > fireNewAlienBulletMaxTime) // if we're at the max time
	{
		bullets_fireRandomAlienBullet(); //fire a random alien bullet
		fireNewAlienBulletMaxTime = rand() % MAX_TIME_BETWEEN_ALIEN_BULLETS; //set fireNewAlienBulletMaxTime to a new random number
		fireNewAlienBulletCtr = 0;//reset fireNewAlienBulletCtr
	}
}

//Handles the saucer launch counter
void updateSaucerLaunchCtr()
{
	saucerLaunchCtr++;
	if (saucerLaunchCtr > SAUCER_WAIT_TIME)
	{
		saucerLaunchCtr = 0;
		if (saucerLaunched == FALSE) //if the saucer hasnt been launched
		{
			//set saucer launched global variable //it's our responsibility to make sure the ship is off the screen before launching again
			saucerLaunched = TRUE;
			//init ship depending on direction
			if (saucer_getSaucerDirection() == saucer_moves_left)
			{
				saucer_initSaucerMovingLeft();
			}
			else
			{
				saucer_initSaucerMovingRight();
			}
			//reset moveSaucerCtr
			moveSaucerCtr = 0;
		}
	}
}

//Returns TRUE if the saucer is off screen, else returns FALSE
uint8_t isSaucerOffScreen()
{
	if ((globals_getSaucerPosition() < NEGATIVE_WIDTH_OF_SAUCER) || (globals_getSaucerPosition() > (GLOBALS_WIDTH_DISPLAY + SAUCER_WIDTH)))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

//Sets the global game over state to true
void counters_setGameOverState()
{
	gameOverState = TRUE;
}

//Updates the moving of the saucer
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
			if (saucer_getSaucerDirection() == saucer_moves_left)
			{
				saucer_moveSaucerLeft();
				//printf("Moving saucer left\n\r");
			}
			else
			{
				saucer_moveSaucerRight();
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
				saucer_switchSaucerMoveDirection();
			}
		}
	}
}

//Updates the saucer score counter
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
			saucer_printScoreOnSaucerDeath(randScore, GLOBALS_BLACK);
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
	render_drawGameOverScreen(GLOBALS_BLACK);
	//erase all remaining aliens
	aliens_eraseAllAliens();
	//revive the aliens
	aliens_reviveAllAliens();
	//revive the bunkers
	bunkers_reviveAllBunkers();
	//init the display again
	globals_setScore(0); //initialize the score
	render_updateScoreDisplay(0); //draw the score

	//draw tank lives
	int n;
	for(n = 0; n < RENDER_NUM_LIVES_INIT; n++) //Just draw a tank three times at the top of the screen
	{
		render_updateLivesDisplay(RENDER_INC);
		globals_updateLives(RENDER_INC); //update the global variable tracking number of lives
	}

	//redraw the live tank
	render_drawObject(tank_15x8, GLOBALS_TANK_WIDTH, GLOBALS_TANK_HEIGHT, (point_t){globals_getTankPosition(), GLOBALS_TANK_START_Y}, GLOBALS_GREEN, GLOBALS_FORCE_BLACK_BACKGROUND);
	//reenable tank movement, bullet firing, and dying again (by disabling dead variable)
	tankDead = FALSE;
	bunkers_drawBunkersInit(); //draw the bunkers
	render_drawAliensInit(); //draw the block of aliens
}

void changeVolume()
{
	if(upButtonPressed() && !downButtonPressed()) //if the up button is pressed
		sounds_volumeUp(); //increase volume
	if (downButtonPressed() && !upButtonPressed()) //if the down button is pressed
		sounds_volumeDown(); //decrease volume
}


//updates all counters, depending on the game state
void counters_updateAllCounters()
{
	if (gameOverState) //if we're in the game over state
	{
		gameOverCtr++; //inc the counter
		//if any of the buttons are pressed after the timer runs out
		if((centerButtonPressed() || leftButtonPressed() || rightButtonPressed()) && gameOverCtr >= GAME_OVER_COUNTER_MAX)
		{
			gameOverCtr = 0; 			//reset the ctr
			restartGameOnGameOver(); 	//restarts the game
			return;
		}
		else return; //dont inc the other counters if the game is over
	}
	if (tankDead) //if the tank is dead
	{
		//only inc these two counters
		updateTankDeadCounter();
		updateTankDeadGuiseCounter();
	}
	else
	{
		//inc all of the gameplay counters
		updateTankMoveCounter();
		onFireTankBulletButtonPress();
		updateBulletMoveCounter();
		updateAlienExplodeCounter();
		updateSaucerScoreCounter();
		updateAlienTickCounter();
		updateMoveSaucerCtr();
		updateFireNewAlienBulletCtr();
		updateSaucerLaunchCtr();
		changeVolume();
	}
}
