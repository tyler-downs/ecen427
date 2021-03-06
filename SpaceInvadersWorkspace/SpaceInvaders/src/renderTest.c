/*
 * renderTest.c
 *
 *  Created on: Sep 22, 2017
 *      Author: superman
 */

#include "renderTest.h"
#include "aliens.h"
#include <stdio.h>

void renderTest()
{
	render_disp_init(); //draw the game screen with all of the necessary things on it.
	while(1)
	{
		//Get a char from the keyboard
		char input;
		input = getchar();
		switch(input)
		{
		case '8':
			aliens_moveAliens();		//Moves the aliens
			break;
		case '4':
			globals_moveTankLeft();		//Moves the tank left
			break;
		case '6':
			globals_moveTankRight();	//Moves the tank right
			break;
		case '2':
			printf("Enter an alien index to kill:\n\r");
			int alienToKill;
			scanf("%d", &alienToKill);
			aliens_killAlien(alienToKill);	//Kills an alien
			break;
		case '5':
			bullets_fireTankBullet();	//Fires the tank bullet
			break;
		case '3':
			bullets_fireRandomAlienBullet(); //Fires a bullet from a random alien
			break;
		case '9':
			globals_advanceAllBullets();	//Advances all the bullets
			break;
		case '7':
			printf("Enter bunker to erode (0-3): \n\r");
			int bunkerToErode;
			scanf("%d", &bunkerToErode);
			bunkers_erodeEntireBunker(bunkerToErode); //Erodes the bunker chosen
			break;
		case 'a':
			saucer_moveSaucerLeft();
			break;
		case 'd':
			saucer_moveSaucerRight();
			break;
		case 's':
			globals_incrementScore(10);
			render_updateScoreDisplay(globals_getCurrentScore());
			break;
		case 'l':
			render_updateLivesDisplay(RENDER_INC);
			globals_updateLives(RENDER_INC); //update the global variable tracking number of lives
			break;
		case ',':
			render_updateLivesDisplay(RENDER_DEC);
			globals_updateLives(RENDER_DEC); //update the global variable tracking number of lives
			break;
		}
	}
}
