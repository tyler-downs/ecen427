/*
 * PITDriver.c
 *
 *  Created on: Nov 8, 2017
 *      Author: superman
 */

#include "PITDriver.h"
#include "xil_io.h"
#include "xparameters.h"

#define PIT_DEFAULT_INTERVAL 1000000 //10 ms(tick frequency is 100 MHz = 10 ns period)
#define INTERVAL_REGISTER_OFFSET 4 //offset to reach the 2nd register, which is for the delay value

#define INTERRUPT_ENABLE_MASK 0x00000002 //bit 1 controls interrupts.
#define INTERRUPT_DISABLE_MASK 0xFFFFFFFD //turn off bit 1
#define DECREMENT_ENABLE_MASK 0x00000001 //bit 0 enables countdown
#define DECREMENT_DISABLE_MASK 0xFFFFFFFE //turn off bit 0
#define TIMER_RELOAD_ENABLE_MASK 0x00000004//bit 2 enables the timer to reload
#define TIMER_RELOAD_DISABLE_MASK 0xFFFFFFFB //turn off bit 3

void pit_init() //initialize the PIT by enabling reloading and interrupts
{
	//xil_printf("initializing PIT\n\r");
	pit_setInterval(PIT_DEFAULT_INTERVAL); //set the interval
	pit_interruptEnable(TRUE); //enable interrupts
	pit_timerReloadEnable(TRUE); //enable timer reloading
}

void pit_setInterval(uint32_t clockInterval) //set the interrupt interval (number of clock ticks)
{
	Xil_Out32(XPAR_PIT_0_BASEADDR + INTERVAL_REGISTER_OFFSET, clockInterval); //write the new clock interval value to the register
	//xil_printf("just set interval to: %d\n\r", Xil_In32(XPAR_PIT_0_BASEADDR + INTERVAL_REGISTER_OFFSET));
}

uint32_t pit_getInterval() //returns the interval that the interrupts are being fired at
{
	return Xil_In32(XPAR_PIT_0_BASEADDR + INTERVAL_REGISTER_OFFSET); //get the interval level in the register
}


void pit_interruptEnable(uint8_t enable) //enables the PIT interrupt if enable is true; disables it if false
{
	uint32_t currentRegValue = Xil_In32(XPAR_PIT_0_BASEADDR); //read the current value on the control register
	//xil_printf("PIT interrupt enable. Cur reg value: %d\n\r", currentRegValue);
	if (enable) //if we are enabling interrupts
	{
		Xil_Out32(XPAR_PIT_0_BASEADDR, currentRegValue | INTERRUPT_ENABLE_MASK); //set bit 1 (interrupt enable) to 1
	}
	else //if we are disabling interrupts
	{
		Xil_Out32(XPAR_PIT_0_BASEADDR, currentRegValue & INTERRUPT_DISABLE_MASK); //set bit 1 to 0
	}
}

void pit_startTimer() //allows the timer to count down
{
	uint32_t currentRegValue = Xil_In32(XPAR_PIT_0_BASEADDR); //read the current value on the control register
	//xil_printf("PIT start timer. Cur reg value: %d\n\r", currentRegValue);

	Xil_Out32(XPAR_PIT_0_BASEADDR, currentRegValue | DECREMENT_ENABLE_MASK); //set bit 0 to 1 to enable countdown
	//xil_printf("After: %d", Xil_In32(XPAR_PIT_0_BASEADDR));
}

void pit_pauseTimer() //pauses the timer
{
	uint32_t currentRegValue = Xil_In32(XPAR_PIT_0_BASEADDR); //read the current value on the control register
	//xil_printf("PIT pause timer. Cur reg value: %d\n\r", currentRegValue);

	Xil_Out32(XPAR_PIT_0_BASEADDR, currentRegValue & DECREMENT_DISABLE_MASK); //set bit 0 to 0 to disable countdown
}

void pit_timerReloadEnable(uint8_t enable) //if enable is true, allows the timer to restart after reaching 0. if false, stays at 0.
{
	uint32_t currentRegValue = Xil_In32(XPAR_PIT_0_BASEADDR); //read the current value on the control register
	//xil_printf("PIT reload enable. Cur reg value: %d\n\r", currentRegValue);

	if (enable) //if we are enabling timer reload
	{
		Xil_Out32(XPAR_PIT_0_BASEADDR, currentRegValue | TIMER_RELOAD_ENABLE_MASK); //set bit 2 to 1 to enable timer reload
	}
	else //if we are disabling timer reload
	{
		Xil_Out32(XPAR_PIT_0_BASEADDR, currentRegValue & TIMER_RELOAD_DISABLE_MASK); //set bit 2 to 0
	}
}
