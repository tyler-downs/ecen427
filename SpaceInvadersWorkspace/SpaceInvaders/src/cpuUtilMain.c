/*
 * cpuUtilMain.c
 *
 *  Created on: Oct 19, 2017
 *      Author: superman
 */

#include "stdint.h"


int main()
{
	uint32_t bigNumber = 0;
	xil_printf("Starting...\n\r");
	while (bigNumber < 5000000)
	{
		bigNumber++;
	}
	xil_printf("END\n\r");

	return 0;
}