/*
 * fibbonaci.c
 *
 *  Created on: Sep 8, 2017
 *      Author: superman
 */

#include <stdio.h>
#include <stdint.h>
#include "platform.h"

#define MAX_LENGTH 15

uint16_t fibo (uint16_t val)
{
	if (val == 0 || val == 1)
		return val;
	else
		return (fibo(val-1) + fibo(val-2));
}

int main()
{
    init_platform();
    uint16_t i;
    for (i = 1; i < MAX_LENGTH; i++)
    {
    	xil_printf("%d\n\r", fibo(i));
    }

    cleanup_platform();

	return 0;
}


