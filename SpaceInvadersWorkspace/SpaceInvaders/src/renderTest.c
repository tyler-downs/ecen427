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
		if (input == '8')
		{
			moveAliens();
		}
		else if (input == '4')
		{
			moveTankLeft();
		}
		else if (input == '6')
		{
			moveTankRight();
		}
		else if (input == '2')
		{
			printf("Enter an alien index to kill:\n\r");
			int alienToKill;
			scanf("%d", &alienToKill);
			killAlien(alienToKill);
		}
		else if (input == '5')
		{
			printf("Leftmost living alien column = %d\n\r", getLeftmostLivingAlienColumn());
		}
		else if (input == '3')
		{
			printf("Rightmost living alien column = %d\n\r", getRightmostLivingAlienColumn());
		}
	}
}
