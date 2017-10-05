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
	disp_init(); //draw the original screen
	while(1)
	{
		char input;
		input = getchar();
		switch(input)
		{
		case '8':
			moveAliens();
			break;
		case '4':
			moveTankLeft();
			break;
		case '6':
			moveTankRight();
			break;
		case '2':
			printf("Enter an alien index to kill:\n\r");
			int alienToKill;
			scanf("%d", &alienToKill);
			killAlien(alienToKill);
			break;
		case '5':
			fireTankBullet();
			break;
		case '3':
			fireRandomAlienBullet();
			break;
		case '9':
			advanceAllBullets();
			break;
		case '7':
			printf("Enter bunker to erode (0-3): \n\r");
			int bunkerToErode;
			scanf("%d", &bunkerToErode);
			erodeEntireBunker(bunkerToErode);
			break;
		}
	}
}
