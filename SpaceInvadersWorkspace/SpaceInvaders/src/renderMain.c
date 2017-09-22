/*
 * renderMain.c
 *
 *  Created on: Sep 22, 2017
 *      Author: superman
 */

#include "platform.h"
#include "renderTest.h"

int main()
{
	init_platform(); // Necessary for all programs.
	renderTest();
	cleanup_platform();
	return 0;
}
