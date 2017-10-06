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
	renderTest();	 //Run the lab3 main
	cleanup_platform();
	return 0;
}
