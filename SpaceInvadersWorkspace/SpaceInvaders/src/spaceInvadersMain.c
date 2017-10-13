/*
 * spaceInvadersMain.c
 *
 *  Created on: Oct 13, 2017
 *      Author: superman
 */

#include "xgpio.h"          // Provides access to PB GPIO driver.
#include <stdio.h>          // xil_printf and so forth.
#include "platform.h"       // Enables caching and other system stuff.
#include "mb_interface.h"   // provides the microblaze interrupt enables, etc.
#include "xintc_l.h"        // Provides handy macros for the interrupt controller.
#include "renderTest.h"
#include "render.h"
#include "globals.h"
#include "saucer.h"

#define MOVE_ALIENS_COUNTER_MAX 90 //One second at one interrupt every 10ms
#define PB_BTNC_MASK 0x0001 //Mask for identifying the center button
#define PB_BTNR_MASK 0x0002 //Mask for identifying the right button
#define PB_BTND_MASK 0x0004 //Mask for identifying the down button
#define PB_BTNL_MASK 0x0008 //Mask for identifying the left button
#define PB_BTNU_MASK 0x0010 //Mask for identifying the up button

XGpio gpLED;  // This is a handle for the LED GPIO block.
XGpio gpPB;   // This is a handle for the push-button GPIO block.

u32 currentButtonState = 0; //the state of the button register
u32 previousButtonState = 0; //for debouncing: checking if button state has changed

u32 moveAliensTickCtr = 0; //Counter for the FIT

// This is invoked in response to a timer interrupt.
void timer_interrupt_handler() {
	moveAliensTickCtr++;
	if (moveAliensTickCtr > MOVE_ALIENS_COUNTER_MAX)
	{
		moveAliensTickCtr = 0;
		moveAliens();
	}
}

// This is invoked each time there is a change in the button state (result of a push or a bounce).
void pb_interrupt_handler() {
  // Clear the GPIO interrupt.
  XGpio_InterruptGlobalDisable(&gpPB);                // Turn off all PB interrupts for now
  currentButtonState = XGpio_DiscreteRead(&gpPB, 1);  // Get the current state of the buttons.
  // You need to do something here.
  //xil_printf("Button pressed\n\r");

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
	// Check the FIT interrupt first.
	if (intc_status & XPAR_FIT_TIMER_0_INTERRUPT_MASK){
		XIntc_AckIntr(XPAR_INTC_0_BASEADDR, XPAR_FIT_TIMER_0_INTERRUPT_MASK);
		timer_interrupt_handler();
	}
	// Check the push buttons.
	if (intc_status & XPAR_PUSH_BUTTONS_5BITS_IP2INTC_IRPT_MASK){
		pb_interrupt_handler();
		XIntc_AckIntr(XPAR_INTC_0_BASEADDR, XPAR_PUSH_BUTTONS_5BITS_IP2INTC_IRPT_MASK);
	}
}


int main()
{
	init_platform(); // Necessary for all programs.

    int success;

    success = XGpio_Initialize(&gpPB, XPAR_PUSH_BUTTONS_5BITS_DEVICE_ID);
    // Set the push button peripheral to be inputs.
    XGpio_SetDataDirection(&gpPB, 1, 0x0000001F);
    // Enable the global GPIO interrupt for push buttons.
    XGpio_InterruptGlobalEnable(&gpPB);
    // Enable all interrupts in the push button peripheral.
    XGpio_InterruptEnable(&gpPB, 0xFFFFFFFF);

    microblaze_register_handler(interrupt_handler_dispatcher, NULL);
    XIntc_EnableIntr(XPAR_INTC_0_BASEADDR,
    		(XPAR_FIT_TIMER_0_INTERRUPT_MASK | XPAR_PUSH_BUTTONS_5BITS_IP2INTC_IRPT_MASK));
    XIntc_MasterEnable(XPAR_INTC_0_BASEADDR);


    //init the display
    disp_init();

    microblaze_enable_interrupts();

    drawSaucer();

    while(1);  // Program never ends.


	cleanup_platform();
	return 0;
}
