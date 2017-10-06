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
	disp_init(); //draw the game screen with all of the necessary things on it.
	while(1)
	{
		//Get a char from the keyboard
		char input;
		input = getchar();
		switch(input)
		{
		case '8':
			moveAliens();		//Moves the aliens
			break;
		case '4':
			moveTankLeft();		//Moves the tank left
			break;
		case '6':
			moveTankRight();	//Moves the tank right
			break;
		case '2':
			printf("Enter an alien index to kill:\n\r");
			int alienToKill;
			scanf("%d", &alienToKill);
			killAlien(alienToKill);	//Kills an alien
			break;
		case '5':
			fireTankBullet();	//Fires the tank bullet
			break;
		case '3':
			fireRandomAlienBullet(); //Fires a bullet from a random alien
			break;
		case '9':
			advanceAllBullets();	//Advances all the bullets
			break;
		case '7':
			printf("Enter bunker to erode (0-3): \n\r");
			int bunkerToErode;
			scanf("%d", &bunkerToErode);
			erodeEntireBunker(bunkerToErode); //Erodes the bunker chosen
			break;
		}
	}
}
