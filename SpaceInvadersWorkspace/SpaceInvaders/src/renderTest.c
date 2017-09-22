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
			render();
		}
	}
}
