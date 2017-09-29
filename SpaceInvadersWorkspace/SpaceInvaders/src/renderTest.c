/*
 * renderTest.c
 *
 *  Created on: Sep 22, 2017
 *      Author: superman
 */

#include "renderTest.h"
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
		else if (input == '1')
		{
			eraseAllAliens();
		}
	}
}
