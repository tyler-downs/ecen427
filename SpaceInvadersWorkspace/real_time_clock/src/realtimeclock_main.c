/*
 * realtimeclock_main.c
 *
 *  Created on: Sep 15, 2017
 *      Author: superman
 */

#include "xgpio.h"          // Provides access to PB GPIO driver.
#include <stdio.h>          // xil_printf and so forth.
#include "platform.h"       // Enables caching and other system stuff.
#include "mb_interface.h"   // provides the microblaze interrupt enables, etc.
#include "xintc_l.h"        // Provides handy macros for the interrupt controller.
#include "setTimeSM.h"		// state machine for setting the clock
#include "sharedGlobals.h"	//globals to share with setTime state machine
#include "PITDriver.h" 		//provides functions to control the Programmable Interval Timer

#define FIT_TIMER_COUNTER_MAX 100 //One second at one interrupt every 10ms
#define DEBOUNCE_COUNT_MAX 5 //5 10ms ticks gives us 50ms of debounce time
#define PIT_DEBOUNCE_COUNT 0 //how many PIT interrupts to wait for debouncing

#define PB_BTNC_MASK 0x0001 //Mask for identifying the center button
#define PB_BTNR_MASK 0x0002 //Mask for identifying the right button
#define PB_BTND_MASK 0x0004 //Mask for identifying the down button
#define PB_BTNL_MASK 0x0008 //Mask for identifying the left button
#define PB_BTNU_MASK 0x0010 //Mask for identifying the up button

XGpio gpLED;  // This is a handle for the LED GPIO block.
XGpio gpPB;   // This is a handle for the push-button GPIO block.

u32 currentButtonState = 0; //the state of the button register
u32 previousButtonState = 0; //for debouncing: checking if button state has changed

u8 fitTimerCounter = 0; //Counter for the FIT to react every one second
u32 debounceCounter = 0; //Counter used in debouncing the buttons




void incrementTime() //increment the time and update the clock.
{
	if (incSec())
	{
		if (incMin())
			incHour();
	}
	printClock(); //print the updated time to the clock
}

//// This is invoked in response to a timer interrupt.
//// It does 2 things: 1) debounce switches, and 2) advances the time.
//void timer_interrupt_handler() {
//	fitTimerCounter++;
//	if (fitTimerCounter > FIT_TIMER_COUNTER_MAX)
//	{
//		fitTimerCounter = 0;
//		if (tickingEnabled)
//			incrementTime(); //update the time and clock.
//
//	}
//
//
//	//increment debounce counter
//	debounceCounter++;
//	if (debounceCounter >= DEBOUNCE_COUNT_MAX && previousButtonState != currentButtonState)
//	{
//		previousButtonState = currentButtonState;
//
//		//update button values
//		hour_btn = currentButtonState & PB_BTNL_MASK; //hour is left, bit 3
//		min_btn = currentButtonState & PB_BTNC_MASK; //min is center, bit 0
//		sec_btn = currentButtonState & PB_BTNR_MASK; //sec is right, bit 1
//		up_btn = currentButtonState & PB_BTNU_MASK; //up is bit 4
//		down_btn = currentButtonState & PB_BTND_MASK; //down is bit 2
//	}
//
//	setTime_tick(); //call tick function
//}

//this is invoked each time there is an interrupt from the PIT
void pit_interrupt_handler()
{
	//xil_printf("\nPIT interrupt!\n\r");
	if (tickingEnabled)
		incrementTime(); //update the time and clock

	//increment debounce counter
	debounceCounter++;
	if (debounceCounter >= PIT_DEBOUNCE_COUNT && previousButtonState != currentButtonState)
	{
		previousButtonState = currentButtonState;

		//update button values
		hour_btn = currentButtonState & PB_BTNL_MASK; //hour is left, bit 3
		min_btn = currentButtonState & PB_BTNC_MASK; //min is center, bit 0
		sec_btn = currentButtonState & PB_BTNR_MASK; //sec is right, bit 1
		up_btn = currentButtonState & PB_BTNU_MASK; //up is bit 4
		down_btn = currentButtonState & PB_BTND_MASK; //down is bit 2
	}

	setTime_tick(); //call tick function
}

// This is invoked each time there is a change in the button state (result of a push or a bounce).
void pb_interrupt_handler() {
  //set debounce counter to 0
  debounceCounter = 0;
  //xil_printf("pb interrupt\n\r");


  // Clear the GPIO interrupt.
  XGpio_InterruptGlobalDisable(&gpPB);                // Turn off all PB interrupts for now
  currentButtonState = XGpio_DiscreteRead(&gpPB, 1);  // Get the current state of the buttons.
  // You need to do something here.

  XGpio_InterruptClear(&gpPB, 0xFFFFFFFF);            // Ack the PB interrupt.
  XGpio_InterruptGlobalEnable(&gpPB);                 // Re-enable PB interrupts.
}

// Main interrupt handler, queries the interrupt controller to see what peripheral
// fired the interrupt and then dispatches the corresponding interrupt handler.
// This routine acks the interrupt at the controller level but the peripheral
// interrupt must be ack'd by the dispatched interrupt handler.
// Question: Why is the timer_interrupt_handler() called after ack'ing the interrupt controller
// but pb_interrupt_handler() is called before ack'ing the interrupt controller?
void interrupt_handler_dispatcher(void* ptr) {
	int intc_status = XIntc_GetIntrStatus(XPAR_INTC_0_BASEADDR);
//	// Check the FIT interrupt first.
//	if (intc_status & XPAR_FIT_TIMER_0_INTERRUPT_MASK){
//		XIntc_AckIntr(XPAR_INTC_0_BASEADDR, XPAR_FIT_TIMER_0_INTERRUPT_MASK);
//		timer_interrupt_handler();
//	}

	//check the pit interrupt
	if (intc_status & XPAR_PIT_0_PITINTERRUPT_MASK)
	{
		XIntc_AckIntr(XPAR_INTC_0_BASEADDR, XPAR_PIT_0_PITINTERRUPT_MASK);
		pit_interrupt_handler();
	}

	// Check the push buttons.
	if (intc_status & XPAR_PUSH_BUTTONS_5BITS_IP2INTC_IRPT_MASK){
		pb_interrupt_handler();
		XIntc_AckIntr(XPAR_INTC_0_BASEADDR, XPAR_PUSH_BUTTONS_5BITS_IP2INTC_IRPT_MASK);
	}


}
#define BASE_TEN 10

int main (void) {
    init_platform();
    // Initialize the GPIO peripherals.

    int success;

    success = XGpio_Initialize(&gpPB, XPAR_PUSH_BUTTONS_5BITS_DEVICE_ID);
    // Set the push button peripheral to be inputs.
    XGpio_SetDataDirection(&gpPB, 1, 0x0000001F);
    // Enable the global GPIO interrupt for push buttons.
    XGpio_InterruptGlobalEnable(&gpPB);
    // Enable all interrupts in the push button peripheral.
    XGpio_InterruptEnable(&gpPB, 0xFFFFFFFF);

    //init PIT
    pit_init();
    //xil_printf("interval is: %d\n\r", pit_getInterval());

    microblaze_register_handler(interrupt_handler_dispatcher, NULL);
    XIntc_EnableIntr(XPAR_INTC_0_BASEADDR,
    		(XPAR_PUSH_BUTTONS_5BITS_IP2INTC_IRPT_MASK | XPAR_PIT_0_PITINTERRUPT_MASK));
    XIntc_MasterEnable(XPAR_INTC_0_BASEADDR);
    microblaze_enable_interrupts();

    //start the PIT timer
    pit_startTimer();

    while(1)  // Program never ends.
    {
    	//Get a new interval from the keyboard
    	uint32_t temp_val = 0;
    	char temp_char = getchar();
    	while(temp_char != '\r')
    	{
    		temp_val *= BASE_TEN;
    		temp_val += temp_char - '0';
    		temp_char = getchar();

    	}
    	pit_setInterval(temp_val);
    	//xil_printf("interval is: %d\n\r", pit_getInterval());
    }


    cleanup_platform();

    return 0;
}
